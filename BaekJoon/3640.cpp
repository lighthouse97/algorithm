// 3640.cpp
// 제독
// ICPC > Regionals > Europe > Northwestern European Regional Contest > NWERC 2012 A번
// MCMF(Minimum Cost Maximum Flow) 문제이다.
// 소스와 출발지, 도착지와 싱크의 용량을 2로 해 주고 나머지는 용량 1로 해서 그래프 연결하면 된다.
// 추가! 문제에서 정점을 중복 방문할 수 없는 조건이 주어지기 때문에 정점 분할을 해야 한다!!!
//       (결국 간단한 문제는 아니다!)
// source -> 출발점, 도착점 -> sink의 용량만 2가 되어야 하는 것뿐만 아니라, 출발점 - 출발점', 도착점 - 도착점' 사이의
// 용량도 2가 되어야 하는데 이걸 빠뜨렸다!!
// 정점 분리할 때 i < v + 1인데, i < v로 잘 못 했다.
// 제한시간 1초 중 100ms(52,320KB)가 소요되었다.
// 맞은사람 254/358로 상위 70.94%에 rank되었다.

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

		int minFlow = INF;
		for (int i = g_T; i != g_S; i = g_prev[i])
			minFlow = min(minFlow, g_flow[g_prev[i]][i].cap - g_flow[g_prev[i]][i].flo);
		for (int i = g_T; i != g_S; i = g_prev[i]) {
			g_flow[g_prev[i]][i].flo += minFlow;
			g_flow[i][g_prev[i]].flo -= minFlow;
			g_minCost += minFlow * g_flow[g_prev[i]][i].cos;
		}
		g_maxFlow += minFlow;
	}
}

int main()
{
	FAST;
	int v, e;
	while (cin >> v) {
		cin >> e;
		g_S = v * 2 + 1;
		g_T = g_S + 1;
		g_N = g_T;
		g_graph.assign(g_N + 1, {});
		g_flow.assign(g_N + 1, vector<vertex>(g_N + 1, { 0, 0, 0 }));
		g_prev.assign(g_N + 1, -1);
		g_maxFlow = g_minCost = 0;

		g_flow[g_S][1].cap = 2; // source -> 출발지
		g_graph[g_S].push_back(1);
		g_graph[1].push_back(g_S);
		g_flow[v * 2][g_T].cap = 2; // 도착지 -> sink
		g_graph[v * 2].push_back(g_T);
		g_graph[g_T].push_back(v * 2);
		for (int i = 1; i < v + 1; i++) { // 정점 분리
			int cap = (i == 1 || i == v) ? 2 : 1;
			g_flow[i * 2 - 1][i * 2].cap = cap;
			g_graph[i * 2 - 1].push_back(i * 2);
			g_graph[i * 2].push_back(i * 2 - 1);
		}
		int a, b, c;
		for (int i = 0; i < e; i++) {
			cin >> a >> b >> c;
			g_flow[a * 2][b * 2 - 1].cap = 1;
			g_flow[a * 2][b * 2 - 1].cos = c;
			g_flow[b * 2 - 1][a * 2].cos = -c;
			g_graph[a * 2].push_back(b * 2 - 1);
			g_graph[b * 2 - 1].push_back(a * 2);
		}
		SPFA();
		cout << g_minCost << "\n";
	}
}