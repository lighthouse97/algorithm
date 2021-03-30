// 3860_1.cpp
// 할로윈
// 3860에서는 bellman-ford 탐색 시 H * W 의 묘지맵을 그대로 두고 2차원 배열을 돌리면서 하나하나에 대해서 탐색을
// 했는데, 수행 시간을 좀 더 최적화 시키는 작업을 하여 탐색 시간을 더 빠르게 하였다.
// 묘지맵 입력시 잔디, 묘비, 구멍 등의 정보를 모두 고려하여 row, column 각각의 좌표를 정점으로 하는
// 하나의 그래프를 만들고, 이 그래프를 가지고 bellman-ford 탐색을 실시 하였다.
// 즉 최대한 기존의 탐색 형식과 같게 맞추었다.
// 이를 위해서는 row, column을 하나의 값으로 변환시켜주어야 한다. "변환값 = row * W + col"
// 이렇게 하면 최단경로 탐색시 루프의 갯수가 줄어들어 수행 시간이 더 최적화가 된다.
// 수행결과, 216ms(2,156KB) -> 132ms(2,168KB)로 수행시간이 38.8% 최적화되었다.
// 제한시간 1초 중 132ms(2,168KB)가 소요되었다.
// 맞은사람 152/377로 상위 40.31%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
//#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

typedef pair<int, int> pii; // to, time
const int INF = 987654321;

int g_W, g_H, g_N;
vector<vector<int>> g_map;
vector<vector<pii>> g_graph; //from -> (to, time)
vector<int> g_dist;
bool g_cycle = false;

void bellman_ford()
{
	int take;
	g_dist[0] = 0;
	for (int rep = 1; rep <= g_N; rep++) {
		for (int i = 0; i < g_N; i++) {
			for (pii& x : g_graph[i]) {
				take = g_dist[i] + x.second;
				if (g_dist[i] != INF && take < g_dist[x.first]) {
					g_dist[x.first] = take;
					if (rep == g_N) { g_cycle = true; return; }
				}
			}
		}
	}
}

void doTest()
{
	int G, E;
	int x, y, x1, y1, x2, y2, t;
	while (1) {
		cin >> g_W >> g_H;
		if (!g_W && !g_H) break;
		g_N = g_H * g_W;
		g_map.resize(g_H, vector<int>(g_W, 0)); // 잔디(0)으로 초기화
		g_graph.resize(g_N);
		g_dist.resize(g_N, INF);		
		int from, to;
		cin >> G; // 묘비
		for (int i = 0; i < G; i++) {
			cin >> x >> y;
			g_map[y][x] = 1; // 묘비
		}
		cin >> E;
		for (int i = 0; i < E; i++) { // jump 위치
			cin >> x1 >> y1 >> x2 >> y2 >> t;
			from = y1 * g_W + x1;
			to = y2 * g_W + x2;
			g_map[y1][x1] = 2; // jump
			g_graph[from].push_back({ to, t });
		}
		// 나머지 잔디에 대한 정리
		int adj[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
		int ar, ac;
		for (int i = 0; i < g_H; i++) {
			for (int j = 0; j < g_W; j++) {
				if (g_map[i][j] == 0) { // 묘비나 jump는 이미 했음!
					from = i * g_W + j;
					if (from == g_N - 1) continue; // 목적지에서는 간선 추가하지 않음!
					for (int k = 0; k < 4; k++) { // 동서남북 4방향
						ar = i + adj[k][0]; ac = j + adj[k][1];
						if (ar < 0 || ac < 0 || ar >= g_H || ac >= g_W || g_map[ar][ac] == 1) continue;
						to = ar * g_W + ac;
						g_graph[from].push_back({ to, 1 });
					}
				}
			}
		}
		bellman_ford();
		if (g_cycle) cout << "Never" << "\n";
		else if (g_dist[g_N - 1] == INF) cout << "Impossible" << "\n";
		else cout << g_dist[g_N - 1] << "\n";

		g_cycle = false;
		g_map.clear();
		g_graph.clear();
		g_dist.clear();
	} // while(1)
}

int main() {
	FAST;
	doTest();
}