// 1420.cpp
// 학교 가지마!
// Dinic algorithm을 사용하였다.
// 정점에서 자르므로 정점 분할해야 하고 network flow를 잘 설계한 다음에 다닉 알고리즘으로 푼다.
// 어떻게 접근해야 할지 몰라서 다른 사람이 푼 것을 보고 겨우 이해하였다!
// 이 문제의 경우 Edmond-Karp algorithm보다 시간이 더 많이 걸렸다.(8ms -> 12ms, Edmond는 8ms)
// 12ms(5,864KB)
// 상위권 답을 보니 Dinic algorithm으로 풀어 0ms가 걸렸다. 한번 자세히 봐야 겠다!
// 음... 그리고 정점간의 capacity를 INF로 하지 않고(이게 이해가 잘 안갔음) 1로 해도 AC가 나온다!

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
#include <map>
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct edge {
	int capacity;
	int flow;
};

map<pair<int, int>, edge> g_flow;
vector<vector<int>> g_graph;
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
		for (int next : g_graph[current]) {
			if (g_level[next] == -1 && g_flow[{current, next}].capacity - g_flow[{current, next}].flow > 0) {
				g_level[next] = g_level[current] + 1;
				myq.push(next);
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
		int next = g_graph[current][i];
		if (g_level[next] == g_level[current] + 1 && g_flow[{current, next}].capacity - g_flow[{current, next}].flow > 0) {
			ret = dfs(next, min(flow, g_flow[{current, next}].capacity - g_flow[{current, next}].flow));
			if (ret > 0) {
				g_flow[{current, next}].flow += ret;
				g_flow[{next, current}].flow -= ret;
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
	vsize = n * m * 2; // bacause of 정점분리	
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
			else if (g_road[i][j] == '#') continue;
			// 각 정점 분할
			int v = makeV(i, j);
			int left = leftV(v), right = rightV(v);
			g_flow[{left, right}].capacity = 1;
			g_flow[{right, left}].capacity = 0;
			g_graph[left].push_back(right);
			g_graph[right].push_back(left);
			// 정점들 끼리 연결
			for (int k = 0; k < 4; k++) {
				int ady = i + dy[k], adx = j + dx[k];
				if (canGo(ady, adx)) {
					g_flow[{right, leftV(makeV(ady, adx))}].capacity = g_INF;
					g_flow[{leftV(makeV(ady, adx)), right}].capacity = 0;
					g_graph[right].push_back(leftV(makeV(ady, adx)));
					g_graph[leftV(makeV(ady, adx))].push_back(right);
				}
			}
		}
	}
	// S와 T가 인접해 있으면 S 또는 T를 벽으로 바꿀 수 없으므로 S와 T사이에 벽을 둘 수가 없다. 이때는 막을 수 없는 경우이다.
	if ((n == 1 && m == 1) || g_S == 0 || g_T == 0 || abs(tr - sr) + abs(tc - sc) == 1) {
		cout << -1 << "\n";
		return 0;
	}
	// run Dinic Algorithm
	dinic();
	cout << g_maxFlow << "\n";
}