// 1420_e.cpp
// 학교 가지마!
// Dinic algorithm을 사용하였다.
// 1420에서 flow와 graph를 하나로 합쳐서 edge란 구조체에 다 집어넣고
// 소스를 좀 더 최적화 시킨 버전. 동시에 수행시간에 대한 최적화도 하였다.
/// 결과는?
// 음... flow와 graph를 하나로 합쳐서 edge란 구조체에 다 집어넣고 소스를 간단히, 최적화시켜서 돌려보니,
// 0ms(3,896KB) 나왔다. 이는 기존 Dinic대비 (12ms(5,864KB) -> 0ms(3,896KB)) 현저히 최적화되었다.
// 제한시간 2초 중 0ms(3,896KB)가 소요되었다.
// 맞은사람 75/336로 상위 22.32%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs, hypot, round
#include <vector>
#include <algorithm> // sort, max, min, fill
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
#include <queue> // queue, priority_queue
//#include <map>
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct edge {
	int to;
	int capacity;
	int rev; // 상대편(to)에서 나(from)가 몇번째 vector 원소인지에 대한 index정보이다.
	int flow;	
	edge(int t, int c, int r) : to(t), capacity(c), rev(r), flow(0) {}
};

vector<vector<edge>> g_graph;
vector<int> g_level;
vector<int> g_work;
int g_S = 0, g_T = 0; // S(0), T(N+1)
int g_maxFlow = 0; // 최대 유량
const int g_INF = 987654321;

// Dinic bfs
bool bfs()
{
	queue<int> myq;
	int current;
	fill(g_level.begin(), g_level.end(), -1);
	g_level[g_S] = 0;
	myq.push(g_S);

	while (!myq.empty()) {
		current = myq.front();
		myq.pop();
		for (edge next : g_graph[current]) {
			if (g_level[next.to] == -1 && next.capacity - next.flow > 0) {
				g_level[next.to] = g_level[current] + 1;
				myq.push(next.to);
			}
		}
	}
	return g_level[g_T] != -1;
}

// Dinic dfs
int dfs(int current, int flow)
{
	int ret;
	if (current == g_T) return flow;

	for (int& i = g_work[current]; i < (int)g_graph[current].size(); i++) {
		edge& next = g_graph[current][i];
		if (g_level[next.to] == g_level[current] + 1 && next.capacity - next.flow > 0) {
			ret = dfs(next.to, min(flow, next.capacity - next.flow));
			if (ret > 0) {
				next.flow += ret;
				g_graph[next.to][next.rev].flow -= ret;				
				return ret;
			}
		}
	}
	return 0;
}

// Run Dinic algorithm
void dinic()
{
	int flow;
	while (bfs()) {
		fill(g_work.begin(), g_work.end(), 0);
		while (true) {
			flow = dfs(g_S, g_INF);
			if (flow == 0) break;
			g_maxFlow += flow;			
		}
	}
}

int g_m, g_n;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };
vector<string> g_road;

inline int makeV(int i, int j) { return (i - 1)*g_m + j; }
inline int leftV(int v) { return v * 2 - 1; }
inline int rightV(int v) { return v * 2; }
inline bool canGo(int i, int j) { return (i < 1 || j < 1 || i > g_n || j > g_m || g_road[i][j] == '#') ? false : true; }

int main()
{
	FAST;

	int n, m;
	int vsize;
	cin >> n >> m;
	g_m = m; g_n = n;
	g_road.resize(n + 1);
	for (int i = 1; i < n + 1; i++) {
		cin >> g_road[i];
		g_road[i] = " " + g_road[i]; // index 1부터 시작(앞에 ""(null)을 넣으면 스트링 insert가 안된다)
	}
	vsize = n * m * 2;
	g_graph.resize(vsize + 1);
	g_level.resize(vsize + 1, -1);
	g_work.resize(vsize + 1, 0);

	int sr = 0, sc = 0, tr = 0, tc = 0;
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < m + 1; j++) {
			if (g_road[i][j] == 'K') {
				g_S = rightV(makeV(i, j));
				sr = i; sc = j;
			}
			else if (g_road[i][j] == 'H') {
				g_T = leftV(makeV(i, j));
				tr = i; tc = j;
			}
		}
	}
	// S와 T가 인접해 있으면 S 또는 T를 벽으로 바꿀 수 없으므로 S와 T사이에 벽을 둘 수가 없다. 이때는 막을 수 없는 경우이다.
	if ((n == 1 && m == 1) || g_S == 0 || g_T == 0 || abs(tr - sr) + abs(tc - sc) == 1) {
		cout << -1 << "\n";
		return 0;
	}	
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < m + 1; j++) {
			if (g_road[i][j] == '#') continue;
			// 각 정점 분할
			int v = makeV(i, j);
			int left = leftV(v), right = rightV(v);
			g_graph[left].push_back(edge(right, 1, g_graph[right].size()));
			g_graph[right].push_back(edge(left, 0, g_graph[left].size()-1));
			// 정점들 끼리 연결
			for (int k = 0; k < 4; k++) {
				int ady = i + dy[k], adx = j + dx[k];
				if (canGo(ady, adx)) {
					g_graph[right].push_back(edge(leftV(makeV(ady, adx)), g_INF, g_graph[leftV(makeV(ady, adx))].size()));
					g_graph[leftV(makeV(ady, adx))].push_back(edge(right, 0, g_graph[right].size()-1));
				}
			}
		}
	}	
	// run Dinic Algorithm
	dinic();
	cout << g_maxFlow << "\n";
}