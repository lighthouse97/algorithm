// 13511.cpp
// Ʈ���� ���� 2
// LCA�� �����ϴ� �����̴�.
// 1) ù��° query�� root���� ���� x������ ���� cost�� cost(x)�� �ϸ�, cost(u) + cost(v) - 2cost(lca)
// 2) �ι�° query�� k�� u���� lca ���̿� �ִ��� �ۿ� �ִ��ķ� �����ؼ�,
// 2-1) k�� u���� lca ���̿� �ִ� ���, k�� depth�� ����ؼ� u�� depth���� ���̰� 0�� �ǵ��� u�� ��� �ø���.
// 2-2) k�� u�� lca �ۿ� �ִ� ���, ���������� k�� depth�� ����ؼ� v(u�� �ƴ�)�� depth���� ���̰� 0�� �ǵ��� v�� ��� �ø���.  
// �ٸ� ��� Ǭ �� ã�ƺ��� ���� Ǭ�Ͱ� �⺻ ���̵��� ���Ҵ�. u �Ǵ� v�� �ø� �� ���� ���鿡�� �ټ� ���̴� �־���.
// ���ѽð� 2�� �� 228ms(25332KB)�� �ҿ�Ǿ���.
// ������� 117/202�� ���� 57.92%�� rank�Ǿ���.

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
vector<vector<node>> g_graph; // ����� �׷���
vector<bool> g_visited; // �湮 ���� check
vector<int> g_depth; // �� ��庰 ���� level
vector<vector<int>> g_parent; // �� ��庰 2^20������ parent ����
vector<int> g_indegree; // root�� ã�� ����
vector<long long> g_cost; // root���� �ڽ��� ���������� ���� cost

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
	if (y == x) return y; // y�� ������ x�� ���
	// find the lca (x, y�� 2^i��° ������ �ٸ��� �� ��ġ�� �ø���, LCA���� �ø���)
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