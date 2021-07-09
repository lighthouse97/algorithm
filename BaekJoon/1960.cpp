// 1960.cpp
// 행렬만들기
// '2365 숫자판 만들기' 문제와 아주 유사하다.
// 아주 사소한 부분에서 틀렸다.
// 행의 합의 합과 열의 합의 합이 같아야 한다. 이부분 체크하지 못하고
// 그냥 당연하다고 생각하고 넘어갔다!!!
// 3
// 2 3 2
// 99 99 99
// 이 반례는 -1인데 각각의 합을 체크하지 않으면 만들 수 있는 행렬로 출력해 버린다.
// 제한시간 2초 중 4ms(3,740KB)가 소요되었다.
// 맞은사람 45/99로 상위 45.45%에 rank되었다.

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
	g_S = N + N + 1; g_T = g_S + 1; g_N = g_T;
	g_graph.resize(g_N + 1);
	int rs, cs, sum1 = 0, sum2 = 0;
	for (int i = 1; i < N + 1; i++) { // source -> row
		cin >> rs;
		sum1 += rs;
		addEdge(g_S, i, 0, rs);
	}
	for (int i = 1; i < N + 1; i++) { // col -> sink
		cin >> cs;
		sum2 += cs;
		addEdge(i + N, g_T, 0, cs);
	}
	if (sum1 != sum2) { // 행의 합의 합과 열의 합의 합의 같아야 한다! 다르면 구할 수 없다!
		cout << -1 << "\n";
		return 0;
	}
	for (int i = 1; i < N + 1; i++) {
		for (int j = 1 + N; j < N + N + 1; j++)
			addEdge(i, j, 0, 1); // row -> col
	}
	dinic();
	if (g_maxFlow != sum1) cout << -1 << "\n";
	else {
		cout << 1 << "\n";
		for (int i = 1; i < N + 1; i++) {
			for (edge& link : g_graph[i])
				if (link.to < g_S) cout << link.flow;
			cout << "\n";
		}
	}
}