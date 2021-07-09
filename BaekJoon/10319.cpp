// 10319.cpp
// 좀비 아포칼립스
// ICPC > Regionals > Europe > Northwestern European Regional Contest > Benelux Algorithm Programming Contest > BAPC 2014 A번
// Network Flow
// 응용 문제인데 아주 어려운 문제이다. 직접 풀지는 못했고 풀이 참고했다.(도대체 이런 아이디어는 어떻게 생각해 낼까?)
// 시간제약이란 변수가 있으므로 각 간선마다 시간에 따른 간선을 여러 개 만든다.
// 예를 들어 바로 전송, 1초후 전송, 2초후 전송,... 지연시간 + 단위시간 <= 제약시간이 될때까지 만든다.
// 그러면 간선에서 나갈 때의 시간이 다음 간선에서 시작하는 시간이 되고 간선을 거칠 때마다 누적 시간 간선을 타게 된다.
// 이렇게 구성해서 sink까지 도달하면 이 때의 max flow가 제약 시간내에 갈 수 있는 최대 사람수가 된다.
// 1) source -> start 지점은, 지연시간없이 start의 첫번째 간선에 바로 연결되고 capacity는 일행의 사람 수 g이다.
// 2) 병원 -> sink는 병원의 모든 간선과 sink를 연결하는데 capacity는 INF이다.
// 3) 정점 -> 정점은 정점의 간선 중 지연 시간 + 단위시간 <= 제약시간 인 것만 연결한다. capacity는 p이다.
// 4) 마지막으로 각 정점에서 지연 출발 정점들을 연결시킨다. 이 때 capacity는 INF이다.
// 그리고 network flow 알고리즘으로 최대 유량을 구한다.
// 여기서는 dinic 알고리즘을 사용하였다.
// 제한시간 5초 중 328ms(20,108KB)가 소요되었다.
// 맞은사람 29/131로 상위 22.13%에 rank되었다.

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
	int to, flow, capa, revi;
	edge() : to(-1), flow(0), capa(0), revi(-1) {}
	edge(int t, int f, int c, int r) : to(t), flow(f), capa(c), revi(r) {}
	bool space() { return capa > flow; }
};

vector<vector<edge>> g_graph;
vector<int> g_level; // level graph
vector<int> g_edge; // store next edge
int g_S, g_T, g_N;
int g_maxFlow = 0;

void addEdge(int from, int to, int flow, int capa)
{
	g_graph[from].push_back({ to, flow, capa, (int)g_graph[to].size() });
	g_graph[to].push_back({ from, 0, 0, (int)g_graph[from].size() - 1 });
}

bool bfs() // dinic bfs
{
	int cur;
	queue<int> myq;
	g_level.assign(g_N + 1, -1);
	g_level[g_S] = 0; // 0 level 부터 시작
	myq.push(g_S);
	while (!myq.empty()) {
		cur = myq.front();
		myq.pop();
		for (edge& next : g_graph[cur]) { // 다음 정점이 비어 있고, 잔여용량 > 0 이면,
			if (g_level[next.to] == -1 && next.space()) {
				g_level[next.to] = g_level[cur] + 1;
				myq.push(next.to);
			}
		}
	}
	return (g_level[g_T] > -1); // sink까지 경로 만들어지면 return
}

int dfs(int cur, int flow) // dinic dfs
{
	int ret;
	if (cur == g_T) return flow;
	for (int& i = g_edge[cur]; i < g_graph[cur].size(); i++) {
		edge& next = g_graph[cur][i];
		if (g_level[next.to] == g_level[cur] + 1 && next.space()) {
			ret = dfs(next.to, min(flow, next.capa - next.flow));
			if (ret > 0) {
				next.flow += ret;
				g_graph[next.to][next.revi].flow -= ret; // 유량의 대칭성
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
			flow = dfs(g_S, INF);
			if (flow == 0) break; // 증가경로를 더 찾지 못하면...
			g_maxFlow += flow;
		}
	}
}

const int UNITN = 101; // unit time
void doTest()
{
	int n;
	cin >> n;
	g_S = (n + 1) * UNITN; g_T = g_S + 1; g_N = (n + 1) * UNITN + 2;
	g_graph.assign(g_N, {});
	int start, g, s;
	cin >> start >> g >> s; // start, people, time limit
	addEdge(g_S, start * UNITN, 0, g); // source -> start
	int m, ho;
	cin >> m;
	for (int i = 0; i < m; i++) { // 병원 -> sink
		cin >> ho;
		for (int j = 0; j <= s; j++)
			addEdge(ho * UNITN + j, g_T, 0, INF);
	}
	int r, a, b, p, t;
	cin >> r;
	for (int i = 0; i < r; i++) { // 정점 -> 정점
		cin >> a >> b >> p >> t;
		for (int j = 0; j + t <= s; j++)
			addEdge(a * UNITN + j, b * UNITN + j + t, 0, p); // t 만큼 지연되어 나간다
	}
	for (int i = 1; i < n + 1; i++) { // 각 정점에서 다음 정점으로 기다렸다 가는 시간 처리 
		for (int j = 0; j < s; j++)
			addEdge(i * UNITN + j, i * UNITN + j + 1, 0, INF);
	}
	g_maxFlow = 0;
	dinic();
	cout << g_maxFlow << "\n";
}

int main()
{
	FAST;
	int T;
	cin >> T;
	while (T--) doTest();
}