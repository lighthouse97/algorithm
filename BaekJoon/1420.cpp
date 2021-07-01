// 1420.cpp
// 학교 가지마!
// 문제 해결 방법에 접근하기가 매우 어렵다.
// 모든 정점에서 벽을 제외하고 갈 수 있는 정점끼리 양방향 간선으로 연결한다.
// 그리고 source -> sink 까지 최대 유량을 구한다.
// 1) 정점에서 벽을 한번만 세우면 중복해서 벽을 또 세울수는 없다.
//    그래서 정점을 분리시키고 간선의 용량을 1로 잡아준다.
// 2) 정점끼리는 여러 정점으로 갈 수도 또 올수도 있으므로 간선의 용량을 INF로 잡는다.
// Network Flow 알고리즘은 Dinic을 사용하였다.
// 이 아이디어를 생각해 내지 못했다!!!
// 12ms(5,868KB) -> 4ms(4,264KB) 소요되었다.

#include "pch.h"
//#include <cstdio> // NULL
#include <cstdlib> // abs
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

bool makeGraph(int n, int m, vector<string>& rd)
{
	auto makeV = [&](int i, int j) { return (i - 1) * m + j; };
	auto leftV = [](int v) { return v * 2 - 1; };
	auto rightV = [](int v) { return v * 2; };
	auto canGo = [&](int i, int j) { return (i < 1 || j < 1 || i > n || j > m || rd[i][j] == '#') ? false : true; };
	int sr = 0, sc = 0, tr = 0, tc = 0;
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < m + 1; j++) {
			if (rd[i][j] == 'K') {
				g_S = rightV(makeV(i, j)); // source 저장
				sr = i; sc = j;
			}
			else if (rd[i][j] == 'H') {
				g_T = leftV(makeV(i, j)); // sink 저장
				tr = i; tc = j;
			}
			else if (rd[i][j] == '#') continue;
			// 각 정점 분할
			int v = makeV(i, j);
			int left = leftV(v), right = rightV(v);
			addEdge(left, right, 0, 1);
			// 정점들 끼리 연결
			int dr[] = { 0, 1, 0, -1 };
			int dc[] = { -1, 0, 1, 0 };
			for (int k = 0; k < 4; k++) {
				int adr = i + dr[k], adc = j + dc[k];
				if (canGo(adr, adc))
					addEdge(right, leftV(makeV(adr, adc)), 0, INF);
			}
		}
	}
	if (abs(tr - sr) + abs(tc - sc) <= 1) return false; // src, sink가 인접한 경우
	return true;
}

int main()
{
	FAST;
	int n, m;
	cin >> n >> m;
	vector<string> road(n + 1);
	for (int i = 1; i < n + 1; i++) {
		cin >> road[i];
		road[i] = " " + road[i]; // start from index 1
	}
	g_N = n * m * 2; // bacause of 정점분리	
	g_graph.resize(g_N + 1);
	if (!makeGraph(n, m, road)) {
		cout << -1 << "\n";
		return 0;
	}
	dinic();
	cout << g_maxFlow << "\n";
}