// 2191.cpp
// ������ Ż��
// �̺� ��Ī �����ε� �ణ�� ������ �߰��Ǿ� dfs�� ��Ī�� �����Ӿƴ϶� ������ �ð����� ����ؾ� �Ѵ�.
// ������ ���� �ð��� ������ '�Ÿ� / �ӵ�'�� ���ϴµ� �� x, y ��ǥ���� �Ÿ��� hypot() �Լ��� �̿��Ѵ�.
// ������ �� �о�� ��Ƴ��� �㰡 �ƴ϶� ��� ������ �㸦 ���Ѵ�. �̰� ����� ���о WA 2�� �߻��ߴ�!!!
// '1348 ������'���� Ǯ�� ���� ���� Ǯ����� �� �����̴�.
// �Ǽ��� �־���. ���� - ���� �ð� �Է� �κп��� i, j loop�� ������ �Ǵµ� �Ǽ��� i loop �ۿ� i loop�� �ϳ� �� �ְ� ���ȴ�.
// �쿬���� AC�� ������ �������� loop�� ���� ���� ���� �ð��� �� �ɷ� ������ ���� ����� ���Դ�!!!
// �̸� �ٽ� �ٷ� ������ �ð��� 16ms(2,176KB) -> 0ms(2,176KB) ���� �پ�����.
// ���ѽð� 2�� �� 16ms(2,176KB)�� �ҿ�Ǿ���.
// ������� 291/314�� ���� 92.67%�� rank�Ǿ���.
// ---> �ٽ�!!
// ���ѽð� 2�� �� 0ms(2,176KB)�� �ҿ�Ǿ���.
// ������� 244/316�� ���� 77.21%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
#include <cmath> // pow, sqrt, fabs. ceil, hypot
#include <vector>
//#include <list>
//#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_graph;
vector<bool> g_visited;
vector<int> g_matched;
vector<vector<double>> g_time; // ��ǥ�� �����ϴ� �ð�

bool dfs(int from)
{
	for (int to : g_graph[from]) {
		if (g_visited[to]) continue;
		else g_visited[to] = true;
		if (g_matched[to] == 0 || dfs(g_matched[to])) {
			g_matched[to] = from;
			return true;
		}
	}
	return false;
}

struct loc {
	double x, y;
	loc() : x(0.0), y(0.0) {}
	loc(double x, double y) : x(x), y(y) {}
};

int main()
{
	FAST;
	int N, M, S, V;
	cin >> N >> M >> S >> V;
	g_graph.resize(N + 1);
	g_visited.resize(M + 1, false);
	g_matched.resize(M + 1, 0);
	g_time.resize(N + 1, vector<double>(M + 1, 0.0));
	vector<loc> rat(N + 1, { 0.0, 0.0 });
	vector<loc> hole(M + 1, { 0.0, 0.0 });
	double x, y;
	for (int i = 1; i < N + 1; i++) { cin >> x >> y; rat[i] = { x, y }; }// ���� ��ǥ �Է�
	for (int i = 1; i < M + 1; i++) { cin >> x >> y; hole[i] = { x, y }; }; // ���� ��ǥ �Է�	
	for (int i = 1; i < N + 1; i++) { // ���� - ���� �ð� �Է�
		for (int j = 1; j < M + 1; j++)
			g_time[i][j] = hypot(hole[j].x - rat[i].x, hole[j].y - rat[i].y) / V;
	}
	for (int i = 1; i < N + 1; i++) { // graph �����
		for (int j = 1; j < M + 1; j++)
			if (g_time[i][j] <= S) g_graph[i].push_back(j); // �ð����� �����ϴ� ���۳����� ��Ī�Ѵ�.
	}
	int answer = 0;
	for (int i = 1; i < N + 1; i++) {
		g_visited = vector<bool>(M + 1, false);
		if (dfs(i)) answer++;
	}
	cout << N - answer << "\n"; // ��Ƹ����� �Ǵ� ���� ���Ѵ�.
}