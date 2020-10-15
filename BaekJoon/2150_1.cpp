// 2150_1.cpp
// Strongly Connected Component
// SCC 알고리즘 구현 문제이다.
// Kosaraju algorithm과 Tarjan algorithm 중 이번에는
// Tarjan algorithm을 이용해서 푼다.
// 이해하기에는 Kosaraju algorithm이 더 쉽지만
// 대회에서는 DFS 한번만 돌리는 Tarjan algorithm을 더 많이 사용한다.
// Tarjan algorithm이 dfs를 한번만 돌려서 그런지 수행시간이 더 적게 걸렸다.(28ms -> 24ms)
// 메모리 사용량도 더 적었다. (4332KB -> 3548KB)
// 제한시간 2초 중 24ms(3548KB)가 소요되었다.
// 맞은사람 39/1160로 상위 3.36%에 rank되었다.

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
vector<int> g_visited_seq; // 방문순서
vector<bool> g_finished; // 역방향 판단
stack<int> g_st;
vector<vector<int>> g_scc; // scc component
int g_cnt = 0;

bool mycompare(const vector<int>& a, const vector<int>& b) { return (a[0] < b[0]); }

int dfs(int current)
{
	int result, n;
	g_visited_seq[current] = ++g_cnt;
	g_st.push(current);
	result = g_visited_seq[current];
	for (int next : g_graph[current]) {
		if (g_visited_seq[next] == 0) {
			result = min(result, dfs(next));
		}
		else if (g_finished[next] == false) {
			result = min(result, g_visited_seq[next]);
		}
	}
	// make scc
	if (result == g_visited_seq[current]) {
		vector<int> scc;
		while (1) {
			n = g_st.top();
			g_st.pop();
			scc.push_back(n);
			g_finished[n] = true;
			if (n == current) break;
		}
		sort(scc.begin(), scc.end());
		g_scc.push_back(scc);
	}
	return result;
}

int main()
{
	FAST

	int v, e, a, b;
	cin >> v >> e;
	g_graph.resize(v + 1);
	g_visited_seq.resize(v + 1, 0);
	g_finished.resize(v + 1, false);
	
	for (int i = 0; i < e; i++) {
		cin >> a >> b;
		g_graph[a].push_back(b);
	}
	// do dfs with the graph
	for (int i = 1; i <= v; i++) {
		if (g_visited_seq[i] == 0) {
			dfs(i);
		}
	}
	// print scc
	sort(g_scc.begin(), g_scc.end(), mycompare);
	cout << g_scc.size() << "\n";
	for (vector<int> x : g_scc) { // faster than using index in for loop
		for (int n : x)
			cout << n << " ";
		cout << -1 << "\n";
	}
}