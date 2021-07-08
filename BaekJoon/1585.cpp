// 1585.cpp
// 경찰
// MCMF(Minimum Cost Maximum Flow)
// MCMF, SPFA를 2번 돌려 최소, 최대값을 구한다는 것 말고는 다른 문제들에 비해 상대적으로 쉬운 문제이다.
// src -> in, out -> sink, in -> out 이렇게 매칭한다.
// src -> in, out -> sink 은 capacity = 1, cost = 0,
// in -> out 은 capacity = 1, cost는 문제에서 주어진 조건에 맞게 계산된 값 으로 한다.
// cost의 부호만 바꾸고 flow 0으로 초기화 시켜 SPFA를 두번 돌려주면 된다. 
// 제한시간 2초 중 4ms(2,160KB)가 소요되었다.
// 맞은사람 37/137로 상위 27.00%에 rank되었다.

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

int main()
{
	FAST;
	int N, T, F;
	cin >> N;
	g_S = 2 * N + 1; g_T = g_S + 1; g_N = g_T;
	g_graph.resize(g_N + 1);
	vector<int> in_t(N + 1, 0), out_t(N + 1, 0);
	for (int i = 1; i < N + 1; i++) cin >> in_t[i];
	for (int i = 1; i < N + 1; i++) cin >> out_t[i];
	cin >> T >> F;
	for (int i = 1; i < N + 1; i++)// src -> in
		addEdge(g_S, i, 0, 1, 0);
	for (int i = N + 1; i < 2 * N + 1; i++) // out -> sink
		addEdge(i, g_T, 0, 1, 0);
	for (int i = 1; i < N + 1; i++) { // in -> out
		for (int j = 1; j < N + 1; j++) {
			int cost = 0, dur = out_t[j] - in_t[i];
			if (dur < 1) continue; // '들어가는 시간 < 나오는 시간' 조건이 있다.
			cost = (dur < T) ? (T - dur) * (T - dur) : 0;
			cost = min(cost, F); // cost는 F를 넘지 않는다.
			addEdge(i, j + N, 0, 1, -cost); // 최대값 구함!
		}
	}
	SPFA(); // get max cost
	int resultMin, resultMax;
	if (g_maxFlow != N) resultMax = -1;
	else resultMax = -g_minCost;

	for (int i = 1; i < g_N + 1; i++) { // Now get min cost
		for (edge& link : g_graph[i]) {
			link.flow = 0; // initialize flow
			if (i < g_S && link.to < g_S) link.cost = -link.cost; // inverse cost
		}
	}
	g_maxFlow = g_minCost = 0;
	SPFA();
	if (g_maxFlow != N) resultMin = -1;
	else resultMin = g_minCost;

	if (resultMin < 0 || resultMax < 0) cout << -1 << "\n";
	else cout << resultMin << " " << resultMax << "\n";
}