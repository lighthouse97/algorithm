// 3584.cpp
// ���� ����� ���� ����
// LCA(Lowest Common Ancestor)�� ã�� �����̴�.
// �Ϲ����� LCS ������� Ǯ �� �������� root�� �־����� �ʱ� ������ root�� ã�ƾ� �Ѵ�.
// root�� ã�� ���� indereee�� ����Ͽ� indegree�� 0�� ��带 ã���� �ȴ�.
// ICPC > Regionals > Asia Pacific > Korea > Asia Regional - Taejon 2002 A��
// ���ѽð� 1�� �� 16ms(4144KB)�� �ҿ�Ǿ���.
// ������� 156/239�� ���� 65.27%�� rank�Ǿ���.

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue

using namespace std;

int g_N;
vector<vector<int>> g_graph; // ����� �׷���
vector<bool> g_visited; // �湮 ���� check
vector<int> g_depth; // �� ��庰 ���� level
vector<vector<int>> g_parent; // �� ��庰 2^20������ parent ����
vector<int> g_indegree;

void lca_dfs(int current, int level)
{
	g_depth[current] = level;
	g_visited[current] = true;
	for (int next : g_graph[current]) {
		if (g_visited[next]) continue;
		g_parent[next][0] = current;
		lca_dfs(next, level + 1);
	}
}

void find_parent()
{
	for (int i = 1; i <= 20; i++) {
		for (int j = 1; j <= g_N; j++)
			g_parent[j][i] = g_parent[g_parent[j][i - 1]][i - 1];
	}
}

int lca(int x, int y)
{
	if (g_depth[x] > g_depth[y])
		swap(x, y);
	// adjust the y depth level to x
	for (int i = 20; i >= 0; i--) {
		if (g_depth[y] - g_depth[x] >= (1 << i))
			y = g_parent[y][i];
	}
	if (y == x) return y; // y�� ������ x�� ���
	// find the lca (x, y�� 2^i��° ������ �ٸ��� �� ��ġ�� �ø���, LCA���� �ø���)
	for (int i = 20; i >= 0; i--) {
		if (g_parent[x][i] != g_parent[y][i]) {
			x = g_parent[x][i];
			y = g_parent[y][i];
		}
	}
	return g_parent[x][0];
}

void do_test()
{
	int a, b, x, y, root;
	cin >> g_N;
	g_graph.resize(g_N + 1);
	g_visited.resize(g_N + 1, false);
	g_depth.resize(g_N + 1, 0);
	g_parent.resize(g_N + 1, vector<int>(21, 0));
	g_indegree.resize(g_N + 1, 0);
	for (int i = 0; i < g_N - 1; i++) {
		cin >> a >> b;
		g_graph[a].push_back(b);
		g_graph[b].push_back(a);
		g_indegree[b]++;
	}
	for (int i = 1; i <= g_N; i++) {
		if (g_indegree[i] == 0) {
			root = i;
			break;
		}
	}
	lca_dfs(root, 0);
	find_parent();
	cin >> x >> y;
	cout << lca(x, y) << "\n";
	g_graph.clear();
	g_visited.clear();
	g_depth.clear();
	g_parent.clear();
	g_indegree.clear();
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
		do_test();
}