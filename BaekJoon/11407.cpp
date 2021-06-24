// 11407.cpp
// 책 구매하기 3
// '11405 책 구매하기 1'과 같은 문제인데, 서점 <-> 사람간에 용량에 제약이 있다는 점만 다르다.
// 제한시간 1초 중 396ms(2,692KB)가 소요되었다.
// 맞은사람 124/307로 상위 40.39%에 rank되었다.

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

const int INF = 987654321;
struct vertex {
	int flo, cap, cos; // flow, capacity, cost
	vertex() : flo(0), cap(0), cos(0) {}
	vertex(int f, int ca, int co) : flo(f), cap(ca), cos(co) {}
};

vector<vector<int>> g_graph;
vector<vector<vertex>> g_flow;
vector<int> g_prev;
int g_N, g_S, g_T; // N, source, sink
int g_maxFlow = 0, g_minCost = 0;

// Shortest Path Faster Algorithm
// Edmond-Karp 알고리즘과 매우 유사
void SPFA()
{
	vector<bool> checkQ; // queue에 있는지 검사.정점 중복 방문할 수 있어 필요함
	vector<int> dist; // distance(최단거리, 최소비용)
	while (true) {
		queue<int> myq;
		g_prev.assign(g_N + 1, -1);
		checkQ.assign(g_N + 1, false);
		dist.assign(g_N + 1, INF);
		myq.push(g_S); checkQ[g_S] = true;
		g_prev[g_S] = g_S;
		dist[g_S] = 0;
		int cur;
		while (!myq.empty()) {
			cur = myq.front();
			myq.pop(); checkQ[cur] = false;
			for (int next : g_graph[cur]) {
				if (g_flow[cur][next].cap - g_flow[cur][next].flo > 0 && // flow & 최단거리 만족
						dist[cur] + g_flow[cur][next].cos < dist[next]) {
					g_prev[next] = cur;
					dist[next] = dist[cur] + g_flow[cur][next].cos;
					if (!checkQ[next]) { myq.push(next); checkQ[next] = true; }
				}
			}
			// source -> sink 경로 찾더라도 최단경로를 찾아야 하기 때문에 멈추지 않고 계속 탐색			
		}
		if (g_prev[g_T] == -1) break; // 더이상 sourcce -> sink 경로 없음

		int minFlow = INF, minCost = 0;
		for (int i = g_T; i != g_S; i = g_prev[i])
			minFlow = min(minFlow, g_flow[g_prev[i]][i].cap - g_flow[g_prev[i]][i].flo);
		for (int i = g_T; i != g_S; i = g_prev[i]) {
			g_flow[g_prev[i]][i].flo += minFlow;
			g_flow[i][g_prev[i]].flo -= minFlow;
			minCost += minFlow * g_flow[g_prev[i]][i].cos;
		}
		g_maxFlow += minFlow;
		g_minCost += minCost;
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
	g_flow.resize(g_N + 1, vector<vertex>(g_N + 1, { 0, 0, 0 }));
	g_prev.resize(g_N + 1, -1);
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
		for (int j = M + 1; j < M + N + 1; j++)
			cin >> g_flow[i][j].cap;
	}
	int cost;
	for (int i = 1; i < M + 1; i++) { // 서점 <-> 사람(비용)
		for (int j = M + 1; j < M + N + 1; j++) {
			cin >> cost;
			g_flow[i][j].cos = cost;
			g_flow[j][i].cos = -cost; // 역방향으로 갈 경우 -cost	
			g_graph[i].push_back(j);
			g_graph[j].push_back(i);
		}
	}
	SPFA();
	cout << g_maxFlow << "\n";
	cout << g_minCost << "\n";
}