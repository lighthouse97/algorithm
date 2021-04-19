// 1719.cpp
// 택배
// 11780과 유사하게 Floyd-Warshall로 모든 정점에 대해 최단 경로와 그 경로를 출력하는 문제이다.
// 한가지 유의할 점은, 최단 경로에서 가장 마지막에 방문했던 정점이 아니라 가장 먼저 방문한 정점을 기록해야 한다!!!
// 그래서 계속 역추적을 해야 한다!!!
// k를 저장하고 이 k에 대해 출력할 때 역추적해도 되자만,
// g_graph[i][j]에 대해 중간 경로가 k이면 최단 경로 update시에 g_graph[i][j].k = g_graph[i][k].k 로 업데이트해도 된다.(이게 더 간결하다)
// i -> j의 최단 거리의 중간 경로가 k이면 i -> k의 최단 거리의 중간 경로 k로 업데이트한다. 이렇게 하면 최종 i -> j 최단 거리의 첫 방문정점을 알 수 있다.
// 제한시간 2초 중 16ms(2,416KB)가 소요되었다.
// 맞은사람 86/752로 상위 11.43%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
//#include <list>
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

struct point {
	int t, k; // time, k(path)
	point() : t(0), k(0) {}
	point(int t, int k) : t(t), k(k) {}
};

const int INF = 987654321;
int g_N;
vector<vector<point>> g_graph;

void floyd_warshall()
{
	for (int k = 1; k < g_N + 1; k++) {
		for (int i = 1; i < g_N + 1; i++) {
			for (int j = 1; j < g_N + 1; j++) { 
				if (g_graph[i][k].t + g_graph[k][j].t < g_graph[i][j].t) {
					g_graph[i][j].t = g_graph[i][k].t + g_graph[k][j].t;
					g_graph[i][j].k = g_graph[i][k].k; // 중간 경로 저장
				}
			}
		}
	}
}

int main()
{
	FAST;
	cin >> g_N;
	g_graph.resize(g_N + 1, vector<point>(g_N + 1, { INF, 0 }));
	for (int i = 1; i < g_N + 1; i++) g_graph[i][i].t = 0;
	int m;
	cin >> m;
	int s, e, t;
	for (int i = 0; i < m; i++) {
		cin >> s >> e >> t;
		g_graph[s][e].t = t;
		g_graph[e][s].t = t;
		g_graph[s][e].k = e;
		g_graph[e][s].k = s;
	}
	floyd_warshall();
	for (int i = 1; i < g_N + 1; i++) {
		for (int j = 1; j < g_N + 1; j++) {
			if (i == j) cout << '-' << " ";
			else
				cout << g_graph[i][j].k << " ";
		}
		cout << "\n";
	}
}