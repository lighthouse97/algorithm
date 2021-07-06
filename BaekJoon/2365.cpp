// 2365.cpp
// 숫자판 만들기
// 1) 1 ~ N(row)을 source에 연결, capacity는 row합
// 2) N + 1 ~ 2N(col)을 sink에 연결, capacity는 col합
// 3) 정점끼리 연결. 이 때 capacity를 INF로 고정했다가 연속 WA나왔음!
//    이 때의 capacity는 row합, col합 중 가장 큰 값을 max로 해서 이진 탐색으로 계속 바꿔줘야 한다.
// 4) dinic돌려서 maxFlow가 row합(또는 col합, 둘 다 같은 값)보다 같은지 작은지를 보고 이진 탐색의 범위를 조정한다.
// 5) 이진 탐색이 끝나면 이 때 maxFlow를 보고 dinic을 한번 더 돌릴지를 결정한다.
// 6) 이진 탐색 끝났을 때의 left값(lo값)이 문제의 조건을 만족하는 값이고 이 때의 row-col 간선에 흐르면 flow를 차례로 출력한다.
// 반성할 점!!
// 처음 문제 조건의 제한 시간에서 5초로 주어질 때부터 network flow 함수를 여러 번 호출하는 거구나...라고 눈치를 챘어야 한다!
// 이진 탐색에서 dinic 돌리기 전에 간선의 capacity값을 조정해줘야 하는데, 이 때 flow값도 0으로 같이 초기화시켜야 하는데 그것을 빠뜨렸다!!!
// 이거 때문에 연속으로 WA가 나왔다!!!
// 제한시간 2초 중 0ms(2,156KB)가 소요되었다.
// 맞은사람 23/158로 상위 14.55%에 rank되었다.

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

int main()
{
	FAST;
	int N;
	cin >> N;
	g_S = N * 2 + 1; g_T = g_S + 1; g_N = g_T;
	g_graph.resize(g_N + 1);
	int c, maxcap = 0, sum = 0;
	for (int i = 1; i < N + 1; i++) { // 행의 합(src -> 행)
		cin >> c;
		maxcap = max(maxcap, c);
		sum += c;
		addEdge(g_S, i, 0, c);
	}
	for (int i = 1 + N; i < 2 * N + 1; i++) { // 열의 합(열 -> sink)
		cin >> c;
		maxcap = max(maxcap, c);
		addEdge(i, g_T, 0, c);
	}
	for (int i = 1; i < N + 1; i++) { // 행 -> 열
		for (int j = 1 + N; j < 2 * N + 1; j++)
			addEdge(i, j, 0, INF);
	}

	int left = 0, right = maxcap, mid = 0; // 이진 탐색(lower_bound)
	while (left < right) {
		mid = (left + right) >> 1;
		for (int i = 1; i < g_N + 1; i++) {
			for (edge& link : g_graph[i]) {
				link.flow = 0; // flow는 모두 초기화
				if (i <= N && link.to < g_S) link.capa = mid;
			}
		}
		g_maxFlow = 0;
		dinic();
		if (g_maxFlow < sum) left = mid + 1;
		else right = mid;
	}

	if (g_maxFlow != sum) {
		for (int i = 1; i < g_N + 1; i++) { // 이분 탐색에서 찾은 left로 dinic한번 더 돌린다!
			for (edge& link : g_graph[i]) {
				link.flow = 0; // flow는 모두 초기화
				if (i <= N && link.to < g_S) link.capa = left;
			}
		}
	}
	g_maxFlow = 0;
	dinic();

	cout << left << "\n";
	for (int i = 1; i < N + 1; i++) {
		for (edge& link : g_graph[i])
			if (link.to < g_S) cout << link.flow << " ";
		cout << "\n";
	}
}