// 9413.cpp
// 제주도 관광
// ICPC > Regionals > Asia Pacific > Thailand > Asia Thailand National Programming Contest > 2010 ACM-ICPC Thailand National Programming Contest F번
// MCMF(Minimum Cost Maximum Flow) 문제이다.
// 1) 정점 분리(소스, 싱크 포함)
// 2) 소스 -> 모든 정점, 싱크 -> 모든 정점 연결, 모든 정점 끼리 연결
// 3) 소스 -> 소스' : capacity = 2, 비용 = 0 (반드시 경로 2개가 나와야 해서 cap = 2)
// 4) 싱크 -> 싱크' : capacity = 2, 비용 = 0 (반드시 경로 2개가 나와야 해서 cap = 2)
// 5) i번째 정점 -> i번째 정점' : capacity = 1, 비용 = -1 (중복방문이 아니라서 cap = 1, 최대값을 구해서 음수로 비용 설정)
// 6) 소스' -> 모든 정점 : capacity = INF, 비용 = 0
// 7) 모든 정점' -> 싱크 : capacity = INF, 비용 = 0
// 8) 모든 정점' -> 모든 정점 : capacity = INF, 비용 = 0
// 이렇게 그래프 모델링한다.
// 제한시간 1초 중 8ms(2,540KB)가 소요되었다.
// 맞은사람 33/116로 상위 28.44%에 rank되었다.

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
#include <string> // string, stoi
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

struct edge {
	int to, flow, capa, cost, revi; // to 정점, flow, capacity, cost, reverse index(to 에서 from의 index)
	edge() : to(-1), flow(0), capa(0), cost(0), revi(-1) {}
	edge(int t, int f, int c, int co, int r) : to(t), flow(f), capa(c), cost(co), revi(r) {}
	bool space() { return capa > flow; }
};

vector<vector<edge>> g_graph;
int g_N, g_S, g_T; // N, source, sink
int g_maxFlow = 0, g_minCost = 0;

void addEdge(int from, int to, int flow, int capa, int cost)
{
	g_graph[from].push_back({ to, flow, capa, cost, (int)g_graph[to].size() }); // 정방향
	g_graph[to].push_back({ from, 0, 0, -cost, (int)g_graph[from].size() - 1 }); // 역방향
}

// Shortest Path Faster Algorithm
// Edmond-Karp 알고리즘과 매우 유사
void SPFA()
{
	struct vt {
		int name, index;
		vt(int n, int i) : name(n), index(i) {} // 정점, 정점에서의 인덱스
	}; // local struct
	vector<bool> checkQ; // queue에 있는지 검사.정점 중복 방문할 수 있어 필요함
	vector<int> dist; // distance(최단거리, 최소비용)
	vector<vt> prev;
	while (true) {
		queue<int> myq;
		prev.assign(g_N + 1, { -1, -1 });
		checkQ.assign(g_N + 1, false);
		dist.assign(g_N + 1, INF);
		myq.push(g_S); checkQ[g_S] = true;
		prev[g_S].name = g_S;
		dist[g_S] = 0;
		int cur;
		while (!myq.empty()) {
			cur = myq.front();
			myq.pop(); checkQ[cur] = false;
			for (int i = 0; i < g_graph[cur].size(); i++) {
				edge& next = g_graph[cur][i];
				if (next.space() && dist[cur] + next.cost < dist[next.to]) { // flow & 최단거리 만족
					prev[next.to].name = cur; // 이전 정점 저장
					prev[next.to].index = i; // 이전 정점에서의 인덱스 저장
					dist[next.to] = dist[cur] + next.cost;
					if (!checkQ[next.to]) { myq.push(next.to); checkQ[next.to] = true; }
				}
			}
			// source -> sink 경로 찾더라도 최단경로를 찾아야 하기 때문에 멈추지 않고 계속 탐색			
		}
		if (prev[g_T].name == -1) break; // 더이상 sourcce -> sink 경로 없음

		int minFlow = INF;
		for (int i = g_T; i != g_S; i = prev[i].name) {
			edge& link = g_graph[prev[i].name][prev[i].index];
			minFlow = min(minFlow, link.capa - link.flow);
		}
		for (int i = g_T; i != g_S; i = prev[i].name) {
			edge& link = g_graph[prev[i].name][prev[i].index];
			link.flow += minFlow;
			g_graph[link.to][link.revi].flow -= minFlow;
			g_minCost += minFlow * link.cost;
		}
		g_maxFlow += minFlow;
	}
}

void doTest()
{
	int N, M;
	cin >> N >> M;
	g_S = 2 * N + 1; g_T = g_S + 1 + 2; g_N = g_T;
	g_graph.assign(g_N + 1, {});
	for (int i = 1; i < N + 1; i++) addEdge(i, i + N, 0, 1, -1); // 1 ~ N 정점분리
	addEdge(g_S, g_S + 1, 0, 2, 0); // 소스 정점 분리
	addEdge(g_T - 1, g_T, 0, 2, 0); // sink 정점 분리
	int from, to;
	for (int i = 0; i < M; i++) {
		cin >> from >> to;
		addEdge(from + N, to, 0, INF, 0); // 정점들끼리 연결
	}
	for (int i = 1; i < N + 1; i++) // src -> 정점들끼리 연결
		addEdge(g_S + 1, i, 0, INF, 0);
	for (int i = 1; i < N + 1; i++) // 정점들 -> sink 끼리 연결
		addEdge(i + N, g_T - 1, 0, INF, 0);
	g_maxFlow = g_minCost = 0;
	SPFA();
	cout << -g_minCost << "\n";
}

int main()
{
	FAST;
	int T;
	cin >> T;
	while (T--) doTest();
}