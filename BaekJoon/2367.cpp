// 2367.cpp
// 파티
// Network Flow 문제이다.
// Edmond-Karp로 풀 수도 있지만 Dinic 알고리즘으로도 풀 수 있기에
// Dinic 알고리즘으로 한번 풀어보겠다.
// source - 사람 으로 경로를 잡고 용량은 K로 둔다,
// 푸드 - sink 경로를 잡고 용량은 각 푸드별 용량을 준다.
// 사람 - 푸드 경로를 잡고 용량은 1로 준다.
// 그리고 Dinic 알고리즘으로 최대 유량을 구하면 된다.
// --> 추가
// 기존(legacy) 코드에서 정점 사이에 간선이 양방향 
// 또는 여러 개 있는 경우까지 고려한 표준 코드를 적용하였다.
// g_graph에 간선 정보 및 flow, capacity 모두 다 때려넣고 구현한 방식이다.
// 0ms(3,084KB) --> 4ms(2,948KB) 소요되었다.

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

struct edge {
	int to, flow, capa, revi;
	edge() : to(-1), flow(0), capa(0), revi(-1) {}
	edge(int t, int f, int c, int r) : to(t), flow(f), capa(c), revi(r) {}
	bool space() { return capa > flow; }
};

vector<vector<edge>> g_graph;
vector<int> g_level; // level graph
vector<int> g_edge; // store next edge
int g_S, g_T, g_N;
int g_maxFlow = 0;

void addEdge(int from, int to, int flow, int capa)
{
	g_graph[from].push_back({ to, flow, capa, (int)g_graph[to].size() });
	g_graph[to].push_back({ from, 0, 0, (int)g_graph[from].size() - 1 });
}

bool bfs() // dinic bfs
{
	int cur;
	queue<int> myq;
	g_level.assign(g_N + 1, -1);
	g_level[g_S] = 0; // 0 level 부터 시작
	myq.push(g_S);
	while (!myq.empty()) {
		cur = myq.front();
		myq.pop();
		for (edge& next : g_graph[cur]) { // 다음 정점이 비어 있고, 잔여용량 > 0 이면,
			if (g_level[next.to] == -1 && next.space()) {
				g_level[next.to] = g_level[cur] + 1;
				myq.push(next.to);
			}
		}
	}
	return (g_level[g_T] > -1); // sink까지 경로 만들어지면 return
}

int dfs(int cur, int flow) // dinic dfs
{
	int ret;
	if (cur == g_T) return flow;
	for (int& i = g_edge[cur]; i < g_graph[cur].size(); i++) {
		edge& next = g_graph[cur][i];
		if (g_level[next.to] == g_level[cur] + 1 && next.space()) {
			ret = dfs(next.to, min(flow, next.capa - next.flow));
			if (ret > 0) {
				next.flow += ret;
				g_graph[next.to][next.revi].flow -= ret; // 유량의 대칭성
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

	for (int i = 1; i < N + 1; i++) // source - man(cap = K)
		addEdge(g_S, i, 0, K);
	int fc, fs = N; // food start = N
	for (int i = 1; i < D + 1; i++) { // food - sink(cap = each D)
		cin >> fc;
		addEdge(i + fs, g_T, 0, fc);
	}
	int fcnt, food;
	for (int i = 1; i < N + 1; i++) { // man - food (cap = 1)
		cin >> fcnt;
		for (int j = 1; j < fcnt + 1; j++) {
			cin >> food;
			addEdge(i, food + fs, 0, 1);
		}
	}
	dinic();
	cout << g_maxFlow << "\n";
}