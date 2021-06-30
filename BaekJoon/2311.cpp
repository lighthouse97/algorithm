// 2311.cpp
// 왕복 여행
// MCMF(Minimum Cost Maximum Flow) 문제인데, 왕복이라 SPFA(Shortest Path Faster Algorithm)를 2번 쓰야 한다.
// 단, 처음 1 -> N으로 갔다가 다시 N -> 1로 올 때 정방향/역방향의 용량 및 유량이 뒤바뀌어야 한다.
// -> 이렇게 풀면 틀린다!!! 처음에 무조건 최단 경로로만 가면 나중에 N에서 1로 못 오는 경우가
//    발생한다.
// -> 따라서 생각을 조금만 더 하면(나는 이 생각을 못했다!!!) 양방향이라 1 -> N으로 최단 경로로 두번 갈 수 있으면 된다!
//    그래서 source - 1, N - sink로 추가 연결하고 이 연결의 용량은 2로 하고 나머지는 용량을 1로 한다.
//    그리고 최대 유량을 구하면 된다.
// -> 그런데 이렇게만 해도 또 WA다!!
//    문제의 조건이 a - b 경로가 양방향이라 a -> b, b -> a 모두 각각의 간선을 만들어야 한다.(각각에 대해 역방향 간선도 물론 포함!!!)
//    양방형 연결까지 고려해서 구현을 좀 바꾸어야 한다.
// 제한시간 2초 중 0ms(2,692KB)가 소요되었다.
// 맞은사람 40/212로 상위 18.86%에 rank되었다.

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

const int INF = 1999999999;

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
		for (int i = g_T; i != g_S; i = prev[i].name)
			minFlow = min(minFlow, g_graph[prev[i].name][prev[i].index].capa - g_graph[prev[i].name][prev[i].index].flow);
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
	int N, M;
	cin >> N >> M;
	g_S = N + 1;
	g_T = g_S + 1;
	g_N = g_T;
	g_graph.resize(g_N + 1, {});

	addEdge(g_S, 1, 0, 2, 0); // source -> 1
	addEdge(N, g_T, 0, 2, 0); // N -> g_T	
	int a, b, c;
	for (int i = 0; i < M; i++) { // 도시 - 도시
		cin >> a >> b >> c;
		addEdge(a, b, 0, 1, c); // a -> b
		addEdge(b, a, 0, 1, c); // b -> a , 양방향처리
	}
	SPFA();
	cout << g_minCost << "\n";
}