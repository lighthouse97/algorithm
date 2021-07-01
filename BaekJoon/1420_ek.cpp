// 1420_1.cpp
// 학교 가지마!
// edmond-karp algorithm을 사용하였다.
// g_flow 메모리 자체를 잘못 잡았다!!!
// g_flow를 (n*m*2+1)*(n*m*2+1)의 전체 배열로 아주 무식하게 잡으면 무려 최대 800MB가 잡혀 메모리 초과가 발생한다.
// 앞의 문제와는 달리 이 문제는 문제의 집합의 크기가 2차원 배열(n*m)로 상대적으로 크기가 크기 때문에 g_flow배열을
// 단순 무식하게 전체로 다 잡으면 메모리 초과가 발생한다.
// 그리고 문제의 특성상 전체를 다 사용하는 것도 아니기 때문에 map을 이용하여 필요한 부분만 사용하면
// 메모리 초과를 막을 수 있다.
// 음... 그리고 정점간의 capacity를 INF로 하지 않고(이게 이해가 잘 안갔음) 1로 해도 AC가 나온다!
// 제한시간 2초 중 8ms(4,844KB)가 소요되었다.
// 맞은사람 254/336로 상위 75.59%에 rank되었다.

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
vector<int> g_prev;
int g_S = 0, g_T = 0; // S(0), T(N+1)
int g_maxFlow = 0; // 최대 유량
const int g_INF = 987654321;

void edmond_karp()
{
	int current;	
	queue<int> myq;
	while (true) {
		fill(g_prev.begin(), g_prev.end(), -1);
		myq.push(g_S);
		g_prev[g_S] = g_S; // for speed optimization
		while (!myq.empty() && g_prev[g_T] == -1) {
			current = myq.front();
			myq.pop();
			for (int next : g_graph[current]) {
				if (g_prev[next] != -1) continue; // 이게 현재 탐색에서 이미 갔던 곳으로 가는 것을 막아주는 역할을 한다.
															 // 다음 번 탐색에서는 다시 초기화 된다.
				if (g_flow[{current, next}].capacity - g_flow[{current, next}].flow > 0) { // 더 흘릴 수 있는 flow가 남은 간선을 찾는다.
					g_prev[next] = current;
					myq.push(next);					
				}
			}
		}
		while (!myq.empty()) myq.pop(); // clear the queue
		// flow update!
		if (g_prev[g_T] == -1) break; // '출발 -> 목적지'까지 모든 경로 탐색하고 더 탐색할 필요 없을 경우이다!		
		for (int i = g_T; i != g_S; i = g_prev[i]) { // sink -> source까지 역으로 거슬러 온다.			
			g_flow[{g_prev[i], i}].flow += 1;
			g_flow[{i, g_prev[i]}].flow -= 1; // 알고리즘 특성 상 역방향 flow 고려			
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
	vsize = n * m * 2; // bacause of 정점분리	
	g_graph.resize(vsize + 1);
	g_prev.resize(vsize + 1, -1);

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
				if (canGo(ady, adx)) { // 여기서 leftV 계산 최적화해도 수행시간에는 별 영향이 없다.
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
	// run Edmond-Karp Algorithm
	edmond_karp();
	cout << g_maxFlow << "\n";
}