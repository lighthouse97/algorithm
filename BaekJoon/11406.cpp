// 11406.cpp
// 책 구매하기 2
// '11407 책 구매하기 3'에서 최소 비용(최단 거리) 조건만 빠진 것이다.
// 최단 거리 조건이 빠지면 이 문제는 그냥 단순한 Network Flow 문제이다.
// Network Flow 알고리즘 Edmond-Karp와 Dinic 알고리즘 중 Dinic 알고리즘을 사용하였다.
// 제한시간 1초 중 0ms(2,556KB)가 소요되었다.
// 맞은사람 36/246로 상위 14.63%에 rank되었다.

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
	int N, M;
	cin >> N >> M;
	g_S = N + M + 1;
	g_T = g_S + 1;
	g_N = g_T;
	g_graph.resize(g_N + 1);
	g_flow.resize(g_N + 1, vector<vertex>(g_N + 1, { 0, 0 }));

	for (int i = M + 1; i < M + N + 1; i++) { // 사람 <-> sink
		cin >> g_flow[i][g_T].cap;
		g_graph[i].push_back(g_T);
		g_graph[g_T].push_back(i);
	}
	for (int i = 1; i < M + 1; i++) { // source <-> 서점
		cin >> g_flow[g_S][i].cap;
		g_graph[g_S].push_back(i);
		g_graph[i].push_back(g_S);
	}
	for (int i = 1; i < M + 1; i++) { // 서점 <-> 사람(용량)
		for (int j = M + 1; j < M + N + 1; j++) {
			cin >> g_flow[i][j].cap;
			g_graph[i].push_back(j);
			g_graph[j].push_back(i);
		}
	}
	dinic();
	cout << g_maxFlow << "\n";
}