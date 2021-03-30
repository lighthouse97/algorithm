// 3860.cpp
// 할로윈
// ICPC > Regionals > Europe > Southwestern European Regional Contest > SWERC 2009 F번
// 음수 비용이 있어 벨만포드로 푸는 문제인데, 그래프가 W * H 행렬로 되어 있는 점이 다르다.
// 그리고 중간에 점프라는 약간의 변형이 들어가 있는데 기존 문제(2665(미로 만들기))의 벨만포드 버전이라고 보면 된다.
// 문제 이해를 잘못해서 최초에 WA가 나왔는데, 문제 원문과 Q&A 내용을 잘 따져보면 다음과 같이 고려해야 한다.
// 1) 사이클이 하나라도 나오면 무조건 Never이다. 사이클 우회해서 목적지에 도달하거나 목적지 INF라도 사이클이 우선이다!
// 2) 목적지에서 무조건 빠져나오기 때문에 목적지를 경유하여 인접 정점으로 이동은 고려하지 않는다.
// 3) 마찬가지로 비석에서 이동도 고려하지 않는다.
// 4) 구멍에서는 지정된 곳으로만 이동할 수 있다.
// 5) 사이클 아니면 목적이 도달 여부 판단한다. 도달할 수 있으면 최단 시간 출력
// 실수하여 빠뜨린 부분이 있는데, g_dist update랄 때 현재 dist가 INF인지 체크하는 부분과, 비석일 때 이동 않하는 것을 빠뜨렸다. 
// 제한시간 1초 중 216ms(2,156KB)가 소요되었다.
// 맞은사람 285/376로 상위 75.79%에 rank되었다.


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
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const int INF = 987654321;
struct gravyrd {
	int type, ti, r, c; // type(0 : 잔디, 1 : 비석, 2 : 점프), ti(통과시간), r(row), c(column)
	gravyrd() : type(0), ti(1), r(-1), c(-1) {}
	gravyrd(int ty, int ti) : type(ty), ti(ti), r(-1), c(-1) {}
	gravyrd(int ty, int ti, int r, int c) : type(ty), ti(ti), r(r), c(c) {}
};

int g_W, g_H, g_N;
vector<vector<gravyrd>> g_graph;
vector<vector<int>> g_dist;
bool g_cycle = false;

void bellman_ford()
{
	int time, ar, ac;
	int adj[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
	g_dist[0][0] = 0;
	for (int rep = 1; rep < g_N + 1; rep++) { // repetition
		for (int i = 0; i < g_H; i++) { // row
			for (int j = 0; j < g_W; j++) { // column
				if (i == g_H - 1 && j == g_W - 1) continue; // 목적지
				else if (g_graph[i][j].type == 1) continue; // 비석(tombstone)
				else if(g_graph[i][j].type == 2) { // jump
					ar = g_graph[i][j].r; ac = g_graph[i][j].c;
					time = g_dist[i][j] + g_graph[i][j].ti;
					if (g_dist[i][j] != INF && time < g_dist[ar][ac]) {
						g_dist[ar][ac] = time;
						if (rep == g_N) { g_cycle = true; return; }
					}
				}
				else {
					for (int k = 0; k < 4; k++) { // 동서남북 인접 잔디로 이동
						ar = i + adj[k][0]; ac = j + adj[k][1];
						if (ar < 0 || ac < 0 || ar >= g_H || ac >= g_W || g_graph[ar][ac].type == 1) continue;
						time = g_dist[i][j] + g_graph[i][j].ti;
						if (g_dist[i][j] != INF && time < g_dist[ar][ac]) {
							g_dist[ar][ac] = time;
							if (rep == g_N) { g_cycle = true; return; }
						}
					}
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
		g_N = g_W * g_H;
		g_graph.resize(g_H, vector<gravyrd>(g_W, { 0, 1 })); // default 잔디
		g_dist.resize(g_H, vector<int>(g_W, INF)); // 최소값 구하므로 +INF로 초기화
		cin >> G;
		for (int i = 0; i < G; i++) {
			cin >> x >> y;
			g_graph[y][x] = { 1, INF }; // 묘비표시
		}
		cin >> E;
		for (int i = 0; i < E; i++) {
			cin >> x1 >> y1 >> x2 >> y2 >> t;
			g_graph[y1][x1] = { 2, t, y2, x2 }; // 점프할 구멍 표시
		}
		bellman_ford();
		if (g_cycle) cout << "Never" << "\n";
		else if (g_dist[g_H - 1][g_W - 1] == INF) cout << "Impossible" << "\n";
		else cout << g_dist[g_H - 1][g_W - 1] << "\n";
		
		g_cycle = false;
		g_graph.clear();
		g_dist.clear();
	} // while(1)
}

int main()
{
	FAST;
	doTest();
}