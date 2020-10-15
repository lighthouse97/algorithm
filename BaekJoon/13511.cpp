// 13511.cpp
// 트리와 쿼리 2
// LCA를 응용하는 문제이다.
// 1) 첫번째 query는 root에서 정점 x까지의 누적 cost를 cost(x)라 하면, cost(u) + cost(v) - 2cost(lca)
// 2) 두번째 query는 k가 u에서 lca 사이에 있느냐 밖에 있느냐로 구분해서,
// 2-1) k가 u에서 lca 사이에 있는 경우, k의 depth를 계산해서 u의 depth와의 차이가 0이 되도록 u를 계속 올린다.
// 2-2) k가 u와 lca 밖에 있는 경우, 마찬가지로 k의 depth를 계산해서 v(u가 아님)의 depth와의 차이가 0이 되도록 v를 계속 올린다.  
// 다른 사람 푼 것 찾아보니 내가 푼것과 기본 아이디어는 같았다. u 또는 v를 올릴 때 구현 측면에서 다소 차이는 있었다.
// 제한시간 2초 중 228ms(25332KB)가 소요되었다.
// 맞은사람 117/202로 상위 57.92%에 rank되었다.

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
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct node {
	int name;
	int cost;
	node() {}
	node(int n, int c) : name(n), cost(c) {}
};

const int g_max_i = 17;
int g_N;
vector<vector<node>> g_graph; // 양방향 그래프
vector<bool> g_visited; // 방문 여부 check
vector<int> g_depth; // 각 노드별 깊이 level
vector<vector<int>> g_parent; // 각 노드별 2^20까지의 parent 정보
vector<int> g_indegree; // root를 찾기 위함
vector<long long> g_cost; // root에서 자신의 정점까지의 누적 cost

void lca_dfs(const node& current, const int& level)
{
	g_depth[current.name] = level;
	g_visited[current.name] = true;
	for (node next : g_graph[current.name]) {
		if (g_visited[next.name]) continue;
		g_parent[next.name][0] = current.name;
		g_cost[next.name] = g_cost[current.name] + next.cost;
		lca_dfs(next, level + 1);
	}
}

void find_parent()
{
	for (int i = 1; i <= g_max_i; i++) {
		for (int j = 1; j <= g_N; j++)
			g_parent[j][i] = g_parent[g_parent[j][i - 1]][i - 1];
	}
}

int lca(int x, int y)
{
	if (g_depth[x] > g_depth[y])
		swap(x, y);
	// adjust the y depth level to x
	for (int i = g_max_i; i >= 0; i--) {
		if (g_depth[y] - g_depth[x] >= (1 << i))
			y = g_parent[y][i];
	}
	if (y == x) return y; // y의 조상이 x일 경우
	// find the lca (x, y의 2^i번째 조상이 다르면 그 위치로 올린다, LCA까지 올린다)
	for (int i = g_max_i; i >= 0; i--) {
		if (g_parent[x][i] != g_parent[y][i]) {
			x = g_parent[x][i];
			y = g_parent[y][i];
		}
	}
	return g_parent[x][0];
}

long long find_query1(int u, int v)
{
	int lca_val = lca(u, v);
	return g_cost[u] + g_cost[v] - 2 * g_cost[lca_val];
}

int find_query2(int u, int v, int k)
{
	int depth_k, n;
	int lca_val = lca(u, v);
	if (g_depth[u] - g_depth[lca_val] + 1 >= k) {
		depth_k = g_depth[u] - (k - 1);
		n = u;
	}
	else {
		// orig : {k - (g_depth[u]-g_depth[lca_val]+1)} + g_depth[lca_val]
		depth_k = k - g_depth[u] + 2 * g_depth[lca_val] - 1;
		n = v;
	}
	// raise up to depth k
	for (int i = g_max_i; i >= 0; i--) {
		if (g_depth[n] - depth_k >= (1 << i))
			n = g_parent[n][i];
	}
	return n;
}

int main()
{
	FAST

	int u, v, k, w, m, root, type;
	cin >> g_N;
	g_graph.resize(g_N + 1);
	g_visited.resize(g_N + 1, 0);
	g_depth.resize(g_N + 1);
	g_parent.resize(g_N + 1, vector<int>(g_max_i + 1, 0));
	g_indegree.resize(g_N + 1, 0);
	g_cost.resize(g_N + 1, 0);
	// make tree
	for (int i = 0; i < g_N - 1; i++) {
		cin >> u >> v >> w;
		g_graph[u].push_back(node(v, w));
		g_graph[v].push_back(node(u, w));
		g_indegree[v]++;
	}
	// find root node
	for (int i = 1; i <= g_N; i++) {
		if (g_indegree[i] == 0) {
			root = i;
			break;
		}
	}
	// find lca initialization
	lca_dfs(node(root, 0), 0);
	find_parent();
	// do query
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> type;
		if (type == 1) {
			cin >> u >> v;
			cout << find_query1(u, v) << "\n";
		}
		else if (type == 2) {
			cin >> u >> v >> k;
			cout << find_query2(u, v, k) << "\n";
		}
	}
}