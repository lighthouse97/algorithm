// 7154.cpp
// Job Postings
// University > North American Invitational Programming Contest > UCIPC 2013 G번
// MCMF(Minumum Cost Maximum Flow)
// 문제 그대로 그래프 모델링하여 MCMF로 풀면 되지 않나 싶다...
// 문제 그대로 모델링하면 TLE가 발생한다. 함정이 있으니 잘 따져보자...
// 너무 쉽게 생각했다. 생각보다 난해하다.
// --->
// 그게 아니라 문제 이해를 엉터리로 해 놓고 모델링이 잘못됬다고 이 지랄....
// 쓸데없이 시간만 엄청 잡아먹었다!!!
// 학생 한명당 5개의 입력인데, 1개의 입력과 n개의 입력(값은 우선순위)로
// 거꾸로 해석했다!!!(m개의 학생마다 5개가 아닌 1 + n개의 입력을 읽어들이니 m*5가 정상인데 m*(1+n)으로 코딩하여 당연히
// TLE가 발생했다!!!!!!!!!!!!
// 제발 정신차리자!!!
// 제한시간 5초 중 876ms(2,160KB)가 소요되었다.
// 맞은사람 27/121로 상위 22.31%에 rank되었다.

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
	int table[3][4] = { {4, 3, 2, 1}, {8, 7, 6, 5}, {12, 11, 10, 9} };
	while (true) {
		int n, m;
		cin >> n >> m;
		if (!n && !m) break;
		g_S = n + m + 1; g_T = g_S + 1; g_N = g_T;
		g_graph.assign(g_N + 1, {});
		int p;
		for (int i = 1; i < n + 1; i++) { // 소스 -> job
			cin >> p;
			addEdge(g_S, i, 0, p, 0);
		}
		int y, c1, c2, c3, c4;
		for (int i = 1; i < m + 1; i++) { // job -> 학생
			cin >> y >> c1 >> c2 >> c3 >> c4;
			addEdge(c1 + 1, n + i, 0, 1, -table[y - 1][0]);
			addEdge(c2 + 1, n + i, 0, 1, -table[y - 1][1]);
			addEdge(c3 + 1, n + i, 0, 1, -table[y - 1][2]);
			addEdge(c4 + 1, n + i, 0, 1, -table[y - 1][3]);
			addEdge(n + i, g_T, 0, 1, 0); // 학생 -> g_T
		}
		g_maxFlow = g_minCost = 0;
		SPFA();
		cout << -g_minCost << "\n";
	}
}