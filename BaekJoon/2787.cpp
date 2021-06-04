// 2787.cpp
// ���� ���� ����
// �̺� ��Ī�ε� �̺� �׷��� �����ϴ� ����� ���� ��� Ǯ������ �����Ͽ���.
// �˰� ���� �����ѵ� �̰� �˱Ⱑ �ʹ� ��ƴ�.
// N���� ������ ������ N*N���� check[i][j]�迭�� �����.
// i��° ���� j�� �� j�� �� �� ������ true, �� �� ���� ���� false�� ����Ѵ�
// ���� ���, 2,3��° �ִ밪�� 3�̰� 4,5��° �ּҰ��� 4��� �Ѵٸ�,
// 2, 3��° ���� 4�̻��� �� �� �����Ƿ� check[2][4~5], check[3][4~5]�� false�� �ȴ�
// 4, 5��° ���� 3���ϴ� �� �� �����Ƿ� check[4][1~3], check[5][1~3]�� false�� �ȴ�
// �׸��� �������� 3�� 2~3��°���� 4�� 4~5��°���� �� �� �����Ƿ� 1��°���� 3, 4�� �� �� ����
// ���� check[1][3], check[1][4]�� false�̴�.
// �̷��� ǥ���� ���� check���� �� �� �ִ� ��θ� �̺� �׷����� �����
// �ִ� ��Ī�� ���Ѵ�. �ִ� ��Ī�� ���� N�̸� �ش� ������ ����Ѵ�.
// N�� �ƴϸ� -1�� ����Ѵ�.
// ���ѽð� 1�� �� 148ms(2,292KB)�� �ҿ�Ǿ���.
// ������� 95/169�� ���� 56.21%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil, hypot
#include <vector>
//#include <list>
#include <algorithm> // sort, max, min, copy, swap, unique, fill
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

const int MAXN = 201;
vector<vector<int>> g_graph;
bool g_visited[MAXN] = { false, };
int g_matched[MAXN] = { 0, };
int g_num[MAXN] = { 0, };

bool dfs(int from)
{
	for (int to : g_graph[from]) {
		if (g_visited[to]) continue;
		else g_visited[to] = true;
		if (g_matched[to] == 0 || dfs(g_matched[to])) {
			g_matched[to] = from;
			g_num[from] = to;
			return true;
		}
	}
	return false;
}

int main()
{
	FAST;
	int N, M;
	cin >> N >> M;
	g_graph.resize(N + 1);

	bool check[MAXN][MAXN]; // MSVC������ VLA(Variable Length Array)�� �������� �ʾƼ� N -> MAXN���� ���ƴ�!
	fill(&check[0][0], &check[N][N + 1], true); // check �迭 �ʱ�ȭ
	int t, x, y, v;
	for (int i = 0; i < M; i++) { // ������ ���� ���� �Է�
		cin >> t >> x >> y >> v;
		if (t == 1) { // v�� �ִ밪
			for (int j = x; j <= y; j++) {
				for (int k = v + 1; k <= N; k++) check[j][k] = false;
			}
		}
		else { // v�� �ּҰ�
			for (int j = x; j <= y; j++) {
				for (int k = 1; k <= v - 1; k++) check[j][k] = false;
			}
		}
		for (int i = 1; i <= x - 1; i++) check[i][v] = false; // ����, x~y��°���� v�� �� �� �ִ�.
		for (int i = y + 1; i <= N; i++) check[i][v] = false;
	}

	for (int i = 1; i < N + 1; i++) { // check[][] �迭�� ������� �̺� �׷��� ����
		for (int j = 1; j < N + 1; j++)
			if (check[i][j]) g_graph[i].push_back(j);
	}

	int count = 0; // �̺� ��Ī
	for (int i = 1; i < N + 1; i++) {
		fill(g_visited, g_visited + MAXN, false);
		if (dfs(i)) count++;
	}
	if (count == N) {
		for (int i = 1; i < N + 1; i++) cout << g_num[i] << " ";
		cout << "\n";
	}
	else cout << -1 << "\n";
}