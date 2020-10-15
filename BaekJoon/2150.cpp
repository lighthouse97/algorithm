// 2150.cpp
// Strongly Connected Component
// SCC 알고리즘 구현 문제이다.
// Kosaraju algorithm과 Tarjan algorithm 중 보편적인
// Kosaraju algorithm을 이용해서 푼다.
// 제한시간 2초 중 28ms(4332KB)가 소요되었다.
// 맞은사람 135/1158로 상위 11.65%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <functional> // less, greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_graph;
vector<vector<int>> g_igraph; // 역방향 그래프
vector<bool> g_visited; // 방문 여부
stack<int> g_st;
vector<vector<int>> g_scc; // scc component

bool mycompare(const vector<int>& a, const vector<int>& b) { return (a[0] < b[0]); }

void dfs(int current)
{
	g_visited[current] = true;
	for (int next : g_graph[current]) {
		if (g_visited[next]) continue;
		dfs(next);
	}
	g_st.push(current);
}

void i_dfs(int current)
{
	g_visited[current] = true;
	g_scc.back().push_back(current);
	for (int next : g_igraph[current]) {
		if (g_visited[next]) continue;
		i_dfs(next);
	}
}

int main()
{
	FAST

	int v, e, a, b;
	cin >> v >> e;
	g_graph.resize(v + 1);
	g_igraph.resize(v + 1);
	g_visited.resize(v + 1, false);
	for (int i = 0; i < e; i++) {
		cin >> a >> b;
		g_graph[a].push_back(b); // graph
		g_igraph[b].push_back(a); // inverse graph
	}
	// do dfs with the graph
	for (int i = 1; i <= v; i++) {
		if (g_visited[i]) continue;
		dfs(i);
	}
	// initialise visited array
	g_visited = vector<bool>(v + 1, false);
	// do inverse-dfs with the inverse graph
	while (!g_st.empty()) {
		int current = g_st.top();
		g_st.pop();
		if (g_visited[current]) continue;
		g_scc.push_back(vector<int>());
		i_dfs(current);
	}
	// print scc
	for (int i = 0; i < (int)g_scc.size(); i++)
		sort(g_scc[i].begin(), g_scc[i].end());
	sort(g_scc.begin(), g_scc.end(), mycompare);
	cout << g_scc.size() << "\n";
	for (vector<int> x : g_scc) { // faster than using index in for loop
		for (int n : x)
			cout << n << " ";
		cout << -1 << "\n";
	}
}