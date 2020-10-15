// 3977.cpp
// 축구 전술
// SCC를 직접 활용하는 문제이다.
// SCC를 만들고 SCC끼리 위상정렬해서 root에 해당되는 SCC를 구하면 된다.
// SCC끼리 연결되지 않는 것이 단 한개라도 있으면 Confused 처리하면 된다.
// 좀 더 고민해보니 굳이 SCC끼리 따로 위상정렬할 필요없이 SCC를 vector에 추가할 때
// 가장 마지막에 추가되는 SCC가 root에 해당되는 SCC이다.(SCC 끼리 모두 연결될 경우)
// 즉 이미 위상 정렬이 된 상태로 SCC들이 추가되는 것이다.
// 따라서 마지막에 추가된 SCC의 임의의 한 원소를 가지고 dfs돌려서 전부 순회하면 해당 SCC가 답이되고
// dfs에서 전부 순회하지 못하면 Confused인 경우인 것이다.
// ICPC > Regionals > Europe > Northwestern European Regional Contest > German Collegiate Programming Contest > GCPC 2010 D번
// 제한시간 1초 중 216ms(12928KB)가 소요되었다.
// 맞은사람 21/229로 상위 9.17%에 rank되었다.

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
vector<int> g_visited;

int scc_dfs(int current)
{
	int result, n;
	g_visited_seq[current] = ++g_cnt;
	g_st.push(current);
	result = g_visited_seq[current];
	for (int next : g_graph[current]) {
		if (g_visited_seq[next] == 0) {
			result = min(result, scc_dfs(next));
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

void dfs(int current)
{
	g_visited[current] = true;
	for (int next : g_graph[current]) {
		if(!g_visited[next])
			dfs(next);
	}
}

void do_test()
{
	int v, e, a, b;
	int root;
	bool result = true;
	cin >> v >> e;
	g_graph.resize(v);
	g_visited_seq.resize(v, 0);
	g_finished.resize(v, false);
	g_visited.resize(v, false);

	for (int i = 0; i < e; i++) {
		cin >> a >> b;
		g_graph[a].push_back(b);
	}
	// do dfs with the graph
	for (int i = 0; i < v; i++) {
		if (g_visited_seq[i] == 0) {
			scc_dfs(i);
		}
	}
	// 마지막에 추가된 SCC로 전체 연결가능한지 검사
	root = g_scc.back()[0];
	dfs(root);
	for (int i = 0; i < v; i++) {
		if (!g_visited[i]) {
			result = false;
			break;
		}
	}
	if (result) {
		for (int x : g_scc.back())
			cout << x << "\n";
	}
	else
		cout << "Confused" << "\n";

	g_graph.clear();
	g_visited_seq.clear();
	g_finished.clear();
	g_scc.clear();
	g_visited.clear();
	g_cnt = 0;
}

int main()
{
	FAST;

	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		do_test();
		cout << "\n";
	}
}