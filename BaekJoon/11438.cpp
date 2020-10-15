// 11438.cpp
// LCA 2
// ���ѽð� 1.5�� �� 156ms(24172KB)�� �ҿ�Ǿ���.
// ������� 1105/1683�� ���� 65.65%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
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
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int g_N;
vector<vector<int>> g_graph; // ����� �׷���
vector<bool> g_visited; // �湮 ���� check
vector<int> g_depth; // �� ��庰 ���� level
vector<vector<int>> g_parent; // �� ��庰 2^20������ parent ����
const int g_max_level = 20;

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
	for (int i = 1; i <= g_max_level; i++) {
		for (int j = 1; j <= g_N; j++)
			g_parent[j][i] = g_parent[g_parent[j][i - 1]][i - 1];
	}
}

int lca(int x, int y)
{
	if (g_depth[x] > g_depth[y])
		swap(x, y);
	// adjust the y depth level to x
	for (int i = g_max_level; i >= 0; i--) {
		if (g_depth[y] - g_depth[x] >= (1 << i))
			y = g_parent[y][i];
	}
	if (y == x) return y; // y�� ������ x�� ���
	// find the lca (x, y�� 2^i��° ������ �ٸ��� �� ��ġ�� �ø���, LCA���� �ø���)
	for (int i = g_max_level; i >= 0; i--) {
		if (g_parent[x][i] != g_parent[y][i]) {
			x = g_parent[x][i];
			y = g_parent[y][i];
		}
	}
	return g_parent[x][0];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int a, b, m, x, y;
	cin >> g_N;
	g_graph.resize(g_N + 1);
	g_visited.resize(g_N + 1, false);
	g_depth.resize(g_N + 1, 0);
	g_parent.resize(g_N + 1, vector<int>(g_max_level + 1, 0));
	for (int i = 0; i < g_N - 1; i++) {
		cin >> a >> b;
		g_graph[a].push_back(b);
		g_graph[b].push_back(a);
	}
	lca_dfs(1, 0);
	find_parent();
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		cout << lca(x, y) << "\n";
	}
}