// 11493.cpp
// 동전 교환
// ICPC > Regionals > Asia Pacific > Korea > Asia Regional - Daejeon 2015 A번
// MCMF문제이다.
// 동전과 정점이 서로 다른 색끼리 모아서 동전이 흰 것은 소스, 동전이 검은 것은 싱크
// (혹은 그 반대)로 연결한 다음 MCMF를 돌린다. 소스와 싱크에 연결되는 정점의 간선은 비용이 0, 
// 용량은 1, 정점끼리는 비용이 1, 용량은 INF로 한다.
// -->
// 정점끼리 용량을 1로 잡아서 WA가 나왔다. 정점끼리는 용량을 INF로 잡아야 한다.
// 이를 입증하는 예제는 다음과 같다.
// 1
// 6 5
// 1 3
// 2 3
// 3 4
// 4 5
// 4 6
// 0 0 1 0 1 1
// 1 1 1 0 0 0
// 이 때 정점끼리의 간선의 용량이 1이면 모든 동전의 색을 맞출 수 없고 3이라는 오답이 나온다.
// 정점끼리의 간선의 용량이 INF가 되어야 정답 6이 나온다.
// 제한시간 8초 중 1,680ms(13,080KB)가 소요되었다.
// 맞은사람 98/199로 상위 49.24%에 rank되었다.

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

void doTest()
{
	int n, m;
	cin >> n >> m;
	g_S = n + 1; g_T = g_S + 1; g_N = g_T;
	g_graph.assign(g_N + 1, {});
	int x, y;
	for (int i = 0; i < m; i++) { // 정점끼리 연결
		cin >> x >> y;
		addEdge(x, y, 0, INF, 1);
		addEdge(y, x, 0, INF, 1); // 양방향
	}
	vector<int> vt(n + 1, 0);
	vector<int> co(n + 1, 0);
	for (int i = 1; i < n + 1; i++) cin >> vt[i];
	for (int i = 1; i < n + 1; i++) cin >> co[i];
	for (int i = 1; i < n + 1; i++) {
		if (vt[i] ^ co[i]) { // 서로 색이 다른 경우
			if (co[i]) addEdge(g_S, i, 0, 1, 0); // 동전이 흰색일 경우(src->i)
			else addEdge(i, g_T, 0, 1, 0); // 동전이 검은색인 경우(i->g_T)
		}
	}
	g_maxFlow = g_minCost = 0;
	SPFA();
	cout << g_minCost << "\n";
}

int main()
{
	FAST;
	int T;
	cin >> T;
	while (T--) doTest();
}