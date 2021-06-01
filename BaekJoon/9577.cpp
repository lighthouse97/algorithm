// 9577.cpp
// �䷻Ʈ
// ���� �̺� ��Ī�� �̺� �׷��� �����ϴ� ���� �ٽ��̶�� ���� �ٽ� �ѹ� �� ������. ������ ����ߴ�.
// ������ �ð�(��)�� �����ϸ� �ȴ�. �׸��� ���ε� �ð� �� ���� ū ���� ã���� �ȴ�.
// ��� ������ ���� ��Ī�� �ȵǸ� -1�� ����Ѵ�.
// PS ������ ��Ȯ�ѵ�, �������� ������ ���������� ������� ���ϰ� �����ؼ� ������ Ʋ�ȴ�!
// �����ߴ� ���� ������ ����.
// 1) ������ ��ȣ�� n�������� �ִ�. �̰��� n�� ����� �ߴٰ� �ƴ϶�� �ߴٰ� �����ؼ� ����� ���ؼ� ��û �ð� ��ƸԾ���.
// 2) �׷��� ������ �� '���� - �ð�'���� �̹� ���εȰ��� �� �������� �ʴ´�. �� �����ϸ� �̺� �׷��� ��ü�� �ȵǾ� �� �̻� ������
//    ���� �ǹ̰� ����. �翬�� ������ ���ø��� ����.
//    �� �κ� ������� ���ϰ� ������ �Ѿ�ٰ� �̰� ������ ���� �ð� �� 80%�� ��ƸԾ���!!!
// 3) �̺� �׷��� ������ �� �ð��� ������������ �����ؾ� �Ѵ�. �Է��� �� ��Ƽ� ������������ �ٽ� �����ؾ��� �Է��ϸ鼭
//    �ٷ� ���ν�Ű�� �ð� �������� ������ �ȵǾ� ���߿� �̺� ��Ī�Ŀ� ���� �����ϴ� �ּ� �ð��� ���� �� ���� �ȴ�.
//    ���� �̰� �����ؼ� ��ü ���� �ð��� 15% ��ƸԾ���.
// 4) g_matched�� ������ȣ(1���� ����)�� �Ҵ��� �Ǳ� ������ 0���� �ʱ�ȭ�ص� �ȴ�. �̰� -1�� �ϴ��� 0���� �ϴ���
//    �������� ����ϴٰ� �ð��� ���� �����ߴ�.
// 5) �̺� �׷����� �ð� ������ ��, (t1, t2]�̷��� �ص� �ȴ�. �����ڷ�� [t1, t2) �̷��� ���̵� ��Ҵµ�, ���̰� �ִ� ������ �ƴ���
//    ������ �ð� �����ϸ鼭 ����ߴµ� ���� �������� ���̾���.
// 6) �̺� �׷����� '���� - �ð�'���� ��� Ǯ���µ� �̷��� Ǯ� ���� ��������.
//    ���� �ڷ���� ��κ� '�ð� - ����'���� ������ �ؼ� �̰� �´� ���� �ް��� �� ���� �ð� �����ߴµ� ���� �������� ���̾���!!
// ���ѽð� 2�� �� 4ms(2,156KB)�� �ҿ�Ǿ���.
// ������� 89/310�� ���� 28.70%�� rank�Ǿ���.

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
#include <algorithm> // sort, max, min, copy, swap, unique
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

const int MAXN = 101;
vector<vector<int>> g_graph;
bool g_visited[MAXN] = { false, };
int g_matched[MAXN] = { 0, };
int g_maxtime = -1;

bool dfs(int from)
{
	for (int to : g_graph[from]) {
		if (g_visited[to]) continue;
		else g_visited[to] = true;
		if (g_matched[to] == 0 || dfs(g_matched[to])) {
			g_matched[to] = from;
			if (to > g_maxtime) g_maxtime = to;
			return true;
		}
	}
	return false;
}

void doTest()
{
	int n, m;
	cin >> n >> m;
	g_graph.resize(n + 1);
	int t1, t2, a, b;
	bool connected[MAXN][MAXN];
	fill(&connected[0][0], &connected[MAXN - 1][MAXN], false);
	for (int i = 0; i < m; i++) { // �� ���
		cin >> t1 >> t2; // ���� �ð�, Ŭ���� �ð�
		cin >> a; // ������
		for (int j = 0; j < a; j++) {
			cin >> b; // ���� �Է�						
			for (int k = t1 + 1; k <= t2; k++)
				connected[b][k] = true; // ���⼭ �ٷ� graph mapping�ϸ� ������������ �ð� mapping���� �ʾƼ� �����ϴ� �ּ� �ð��� ������ �ʴ´�.
		}
	}

	for (int i = 1; i < n + 1; i++) // ������ �ð��� ������������ mapping.
		for (int j = 0; j < MAXN; j++)
			if (connected[i][j]) g_graph[i].push_back(j); // '���� <-> �ð�' mapping(�ð� ��������)

	fill(g_matched, g_matched + MAXN, 0);
	g_maxtime = -1;
	int count = 0;
	for (int i = 1; i < n + 1; i++) {
		fill(g_visited, g_visited + MAXN, false);
		if (dfs(i)) count++;
	}
	cout << (count == n ? g_maxtime : -1) << "\n";
	g_graph.clear();
}

int main()
{
	FAST;
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
		doTest();
}