// 1657.cpp
// 두부장수 장홍준
// '11111 두부장수 장홍준 2'와 동일한 문제이다.
// 단 N, M의 크기가 max 50에서 max 14로 작아졌다.
// 정점의 갯수가 적어서 동적계획법 또는 비트필드를 이용해서 푸는 취지이나 두부장수 장홍준 2와 동일하게
// MCMF(Minimum Cost Maximum Flow)로 풀어보았다.
// 제한시간 2초 중 0ms(2,168KB)가 소요되었다.
// 맞은사람 61/323로 상위 18.88%에 rank되었다.

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

int main()
{
	FAST;
	int N, M;
	cin >> N >> M;

	g_S = N * M + 1; g_T = g_S + 1; g_N = g_T;
	g_graph.resize(g_N + 1);
	vector<vector<int>> cost_tbl = // 비용 테이블
	{ { 0, 0, 0, 0, 0, 0},
		 { 0, 10, 8, 7, 5, 1},
		 { 0, 8, 6, 4 ,3, 1},
		 { 0, 7, 4, 3, 2, 1},
		 { 0, 5, 3 ,2, 2, 1},
		 { 0, 1, 1, 1, 1, 0} };
	vector<vector<int>> tofu_tbl(N + 1, vector<int>(M + 1, 0)); // 두부판
	struct info { int r, c, id; };
	vector<info> aa; vector<info> bb; // 그룹 A, 그룹 B
	string ss;
	for (int i = 1; i < N + 1; i++) {
		cin >> ss;
		for (int j = 1; j < ss.length() + 1; j++) {
			tofu_tbl[i][j] = (ss[j - 1] != 'F') ? ss[j - 1] - 'A' + 1 : 5;
			if ((i + j) % 2 == 0) aa.push_back({ i, j, (i - 1) * M + j }); // 그룹 a 입력
			else bb.push_back({ i, j, (i - 1) * M + j }); // 그룹 b 입력 			
		}
	}
	for (info& x : aa) {
		addEdge(g_S, x.id, 0, 1, 0); // src -> group a
		addEdge(x.id, g_T, 0, 1, 0); // group a -> sink
	}
	for (info& x : bb)
		addEdge(x.id, g_T, 0, 1, 0); // groub b -> sink
	int dr[4] = { -1, 0, 1, 0 };
	int dc[4] = { 0, -1, 0, 1 };
	for (info x : aa) {
		for (int i = 0; i < 4; i++) {
			int nr = x.r + dr[i];
			int nc = x.c + dc[i];
			if (nr < 1 || nc < 1 || nr > N || nc > M) continue;
			int t1 = tofu_tbl[x.r][x.c];
			int t2 = tofu_tbl[nr][nc];
			addEdge(x.id, (nr - 1) * M + nc, 0, 1, -cost_tbl[t1][t2]);
		}
	}
	SPFA();
	cout << -g_minCost << "\n";
}