// 8229.cpp
// 집기 게임
// ICPC > Regionals > Asia Pacific > Korea > Nationwide Internet Competition > Daejeon Nationalwide Internet Competition 2013 I번
// 모델링만 하면 MCMF 그대로 풀면 된다!!!
// 교점만 구하는 것만 추가 응용이다.
// 좌표들이 항상 오름차순으로 오지 않는다는 것에 주의하자!!!
// 별로 어려운 문제도 아닌데 구현에 너무 시간 많이 걸려 무려 1시간 58분이 걸렸다.
// 제한시간 10초 중 724ms(2,952KB)가 소요되었다.
// 맞은사람 62/226로 상위 27.43%에 rank되었다.

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

void doTest()
{
	int n, m;
	cin >> n >> m;
	g_S = n + m + 1; g_T = g_S + 1; g_N = g_T;
	g_graph.assign(g_N + 1, {});
	vector<vector<int>> pts(n + m + 1, vector<int>(5, 0));
	for (int i = 1; i < n + m + 1; i++)
		cin >> pts[i][0] >> pts[i][1] >> pts[i][2] >> pts[i][3] >> pts[i][4];
	struct pt {
		int x, y;
	};
	pt pt1, pt2, pt3, pt4;
	int w1, w2;
	for (int i = 1; i < n + 1; i++) { // 교점의 y -> 교점의 x
		pt1 = { pts[i][0], pts[i][1] };
		pt2 = { pts[i][2], pts[i][3] };
		w1 = pts[i][4];
		if (pt1.x > pt2.x) swap(pt1.x, pt2.x);
		for (int j = 1; j < m + 1; j++) {
			pt3 = { pts[j + n][0], pts[j + n][1] };
			pt4 = { pts[j + n][2], pts[j + n][3] };
			w2 = pts[j + n][4];
			if (pt3.y > pt4.y) swap(pt3.y, pt4.y);
			if ((pt1.y > pt3.y && pt1.y < pt4.y) && (pt3.x > pt1.x && pt3.x < pt2.x))
				addEdge(i, j + n, 0, 1, -(w1 * w2));
		}
	}
	for (int i = 1; i < n + 1; i++) addEdge(g_S, i, 0, 1, 0); // src -> 교점 y
	for (int j = 1; j < m + 1; j++) addEdge(j + n, g_T, 0, 1, 0); // 교점 x -> sink
	g_maxFlow = g_minCost = 0;
	SPFA();
	cout << g_maxFlow << " " << -g_minCost << "\n";
}

int main()
{
	FAST;
	int T;
	cin >> T;
	while (T--) doTest();
}