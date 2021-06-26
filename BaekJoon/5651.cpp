// 5651.cpp
// 완전 중요한 간선
// ICPC > Regionals > Asia Pacific > Thailand > 2011 ACM-ICPC Asia Phuket Regional Programming Contest P4번
// Network Flow 응용 문제. source -> sink까지 경로가 만들어 졌을 때, minFlow에 해당되는 간선이
// 모두 몇 개인지 count하면 된다.
// --> 이렇게 하면 틀린다!!!
//     최대 유량을 기존대로 구하고 잔여 용량이 0인 간선들을 대상으로 우회할 수 있는 경로가 없으면 카운트 +1하고
//     우회할 수 있는 경로가 있으면 완전 중요한 간선이 아니므로 카운트하지 않는다.
//     이는 간선의 출발점, 도작점을 받아서 bfs로 탐색해본다.
// Dinic 알고리즘으로 풀어 보자.
// 제한시간 1초 중 56ms(3,128KB)가 소요되었다.
// 맞은사람 54/298로 상위 18.12%에 rank되었다.

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
	int capa, flow; // capacity, flow 
	edge() : capa(0), flow(0) {}
	edge(int c, int f) : capa(c), flow(f) {}
	bool space() { return capa > flow; }
};
vector<vector<int>> g_graph;
vector<vector<edge>> g_flow;
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
			if (g_level[next] == -1 && g_flow[cur][next].space()) {
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
		if (g_level[next] == g_level[cur] + 1 && g_flow[cur][next].space()) {
			ret = dfs(next, min(flow, g_flow[cur][next].capa - g_flow[cur][next].flow));
			if (ret > 0) {
				g_flow[cur][next].flow += ret;
				g_flow[next][cur].flow -= ret; // 유량의 대칭성				
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

bool checkEdge(int s, int e) // 잔여 용량이 0인 간선 중 우회 경로가 없는 것을 찾는다.
{
	queue<int> myq;
	vector<bool> visited(g_N + 1, false);
	myq.push(s);
	visited[s] = true;
	while (!myq.empty()) {
		int cur = myq.front(); myq.pop();
		if (cur == e) break;
		for (int next : g_graph[cur]) {
			if (!visited[next] && g_flow[cur][next].space()) {
				myq.push(next);
				visited[next] = true;
			}
		}
	}
	if (visited[e]) return true;
	return false;
}

void doTest()
{
	int N, M;
	cin >> N >> M;
	g_S = 1; g_T = N; g_N = N;
	g_graph.assign(g_N + 1, {});
	g_flow.assign(g_N + 1, vector<edge>(g_N + 1, { 0, 0 }));
	g_maxFlow = 0;
	vector<vector<int>> candidate(M, vector<int>(2, 0));
	int f, t, b;
	for (int i = 0; i < M; i++) {
		cin >> f >> t >> b;
		g_flow[f][t].capa += b;
		g_graph[f].push_back(t);
		g_graph[t].push_back(f);
		candidate[i] = { f, t };
	}
	dinic();
	int answer = 0;
	int s, e;
	for (int i = 0; i < M; i++) {
		s = candidate[i][0];
		e = candidate[i][1];
		if (!g_flow[s][e].space())
			if (!checkEdge(s, e)) answer++;
	}
	cout << answer << "\n";
}

int main()
{
	FAST;
	int T;
	cin >> T;
	for (int i = 0; i < T; i++) doTest();
}