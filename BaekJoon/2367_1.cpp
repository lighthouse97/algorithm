// 2367.cpp
// 파티
// Network Flow 문제이다.
// Edmond-Karp로 풀 수도 있지만 Dinic 알고리즘으로도 풀 수 있기에
// Dinic 알고리즘으로 한번 풀어보겠다.
// source - 사람 으로 경로를 잡고 용량은 K로 둔다,
// 푸드 - sink 경로를 잡고 용량은 각 푸드별 용량을 준다.
// 사람 - 푸드 경로를 잡고 용량은 1로 준다.
// 그리고 Dinic 알고리즘으로 최대 유량을 구하면 된다.
// 제한시간 2초 중 0ms(3,084KB)가 소요되었다.
// 맞은사람 17/231로 상위 7.35%에 rank되었다.

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
#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const int MAXVAL = 987654321;
struct vertex {
	int cap, flo; // capacity, Flow
	vertex() : cap(0), flo(0) {}
	vertex(int c, int f) : cap(c), flo(f) {}
};
vector<vector<int>> g_graph;
vector<vector<vertex>> g_flow;
vector<int> g_level; // level graph
vector<int> g_edge; // store next edge
int g_S, g_T, g_N;
int g_maxFlow = 0;

bool bfs()
{
	int cur;
	queue<int> myq;
	g_level.assign(g_N + 1, -1);
	g_level[g_S] = 0; // 0 level 부터 시작
	myq.push(g_S);
	while (!myq.empty()) {
		cur = myq.front();
		myq.pop();
		for (int next : g_graph[cur]) { // 다음 정점이 비어 있고, 잔여용량 > 0 이면,
			if (g_level[next] == -1 && g_flow[cur][next].cap - g_flow[cur][next].flo > 0) {
				g_level[next] = g_level[cur] + 1;
				myq.push(next);
			}
		}
	}
	return (g_level[g_T] > -1);
}

int dfs(int cur, int flow)
{
	int ret;
	if (cur == g_T) return flow;
	for (int& i = g_edge[cur]; i < g_graph[cur].size(); i++) {
		int next = g_graph[cur][i];
		if (g_level[next] == g_level[cur] + 1 && g_flow[cur][next].cap - g_flow[cur][next].flo > 0) {
			ret = dfs(next, min(flow, g_flow[cur][next].cap - g_flow[cur][next].flo));
			if (ret > 0) {
				g_flow[cur][next].flo += ret;
				g_flow[next][cur].flo -= ret; // 유량의 대칭성
				return ret;
			}
		}
	}
	return 0;
}

void dinic()
{
	int flow;
	while (bfs()) { // level graph를 만든다.
		g_edge.assign(g_N + 1, 0); // g_graph 정점의 간선 index는 0부터 시작
		while (true) {
			flow = dfs(g_S, MAXVAL);
			if (flow == 0) break; // 증가경로를 더 찾지 못하면...
			g_maxFlow += flow;
		}
	}
}

int main()
{
	FAST;
	int N, K, D;
	cin >> N >> K >> D;
	g_S = 0;
	g_T = N + D + 1;
	g_N = g_T + 1; // g_T + source
	g_graph.resize(g_N + 1);
	g_flow.resize(g_N + 1, vector<vertex>(g_N + 1, { 0, 0 }));

	for (int i = 1; i < N + 1; i++) { // source - man(cap = K)
		g_graph[g_S].push_back(i);
		g_graph[i].push_back(g_S);
		g_flow[g_S][i].cap = K;
	}
	int fc, fs = N; // food start = N
	for (int i = 1; i < D + 1; i++) { // food - sink(cap = each D)
		cin >> fc;
		g_graph[i + fs].push_back(g_T);
		g_graph[g_T].push_back(i + fs);
		g_flow[i + fs][g_T].cap = fc;
	}
	int fcnt, food;
	for (int i = 1; i < N + 1; i++) { // man - food (cap = 1)
		cin >> fcnt;
		for (int j = 1; j < fcnt + 1; j++) {
			cin >> food;
			g_graph[i].push_back(food + fs);
			g_graph[food + fs].push_back(i);
			g_flow[i][food + fs].cap = 1;
		}
	}
	dinic();
	cout << g_maxFlow << "\n";
}