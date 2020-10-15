// 1420_1_e.cpp
// 학교 가지마!
// edmond-karp algorithm을 사용하였다.
// 1420_1을 flow와 graph를 하나로 합쳐서 edge란 구조체에 다 집어넣고
// 소스를 좀 더 최적화 시킨 버전. 동시에 수행시간에 대한 최적화도 하였다.
// edmond-karp algorithm으로 구동한 결과는?
// 최적화 성공. 수행시간 및 메모리 사용량이 감소하였다. (8ms(4,844KB) -> 0ms(3,548KB))
// 제한시간 2초 중 0ms(3,548KB)가 소요되었다.
// 맞은사람 59/336로 상위 17.55%에 rank되었다.

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

struct pre {
	int v; // 자신의 previous 정점
	int index; // 자신의 previous 정점에서 자신의 index. // vector 구현이라 구현상 필요하다.
	pre(int v, int i) : v(v), index(i) {}
};

vector<vector<edge>> g_graph;
vector<pre> g_prev;
int g_S = 0, g_T = 0;
int g_maxFlow = 0; // 최대 유량
const int g_INF = 987654321;

void edmond_karp()
{
	int current;
	queue<int> myq;
	while (true) {
		fill(g_prev.begin(), g_prev.end(), pre(-1, -1));
		myq.push(g_S);
		g_prev[g_S].v = g_S; // for speed optimization
		while (!myq.empty() && g_prev[g_T].v == -1) {
			current = myq.front();
			myq.pop();			
			for(int i = 0; i < (int)g_graph[current].size(); i++) {
				edge next = g_graph[current][i];
				if (g_prev[next.to].v != -1) continue; // 이게 현재 탐색에서 이미 갔던 곳으로 가는 것을 막아주는 역할을 한다.
															      // 다음 번 탐색에서는 다시 초기화 된다.
				if (next.capacity - next.flow > 0) { // 더 흘릴 수 있는 flow가 남은 간선을 찾는다.					
					g_prev[next.to].v = current;
					g_prev[next.to].index = i;
					myq.push(next.to);
				}
			}
		}
		while (!myq.empty()) myq.pop(); // clear the queue
		// flow update!
		if (g_prev[g_T].v == -1) break; // '출발 -> 목적지'까지 모든 경로 탐색하고 더 탐색할 필요 없을 경우이다!		
		for (int i = g_T; i != g_S; i = g_prev[i].v) { // sink -> source까지 역으로 거슬러 온다.						
			edge& e = g_graph[g_prev[i].v][g_prev[i].index];
			e.flow += 1;
			g_graph[e.to][e.rev].flow -= 1; // 알고리즘 특성 상 역방향 flow 고려
		}
		g_maxFlow += 1;
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
	g_prev.resize(vsize + 1, { -1, -1 });

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
			g_graph[right].push_back(edge(left, 0, g_graph[left].size() - 1));
			// 정점들 끼리 연결
			for (int k = 0; k < 4; k++) {
				int ady = i + dy[k], adx = j + dx[k];
				if (canGo(ady, adx)) {
					g_graph[right].push_back(edge(leftV(makeV(ady, adx)), g_INF, g_graph[leftV(makeV(ady, adx))].size()));
					g_graph[leftV(makeV(ady, adx))].push_back(edge(right, 0, g_graph[right].size() - 1));
				}
			}
		}
	}
	// run Edmond-Karp Algorithm
	edmond_karp();
	cout << g_maxFlow << "\n";
}