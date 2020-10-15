// 3584.cpp
// 가장 가까운 공통 조상
// LCA(Lowest Common Ancestor)를 찾는 문제이다.
// 일반적인 LCS 방법으로 풀 되 문제에서 root가 주어지지 않기 때문에 root를 찾아야 한다.
// root를 찾는 것은 indereee를 사용하여 indegree가 0인 노드를 찾으면 된다.
// ICPC > Regionals > Asia Pacific > Korea > Asia Regional - Taejon 2002 A번
// 제한시간 1초 중 16ms(4144KB)가 소요되었다.
// 맞은사람 156/239로 상위 65.27%에 rank되었다.

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
vector<vector<int>> g_graph; // 양방향 그래프
vector<bool> g_visited; // 방문 여부 check
vector<int> g_depth; // 각 노드별 깊이 level
vector<vector<int>> g_parent; // 각 노드별 2^20까지의 parent 정보
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
	if (y == x) return y; // y의 조상이 x일 경우
	// find the lca (x, y의 2^i번째 조상이 다르면 그 위치로 올린다, LCA까지 올린다)
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