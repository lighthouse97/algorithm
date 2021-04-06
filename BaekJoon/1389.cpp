// 1389.cpp
// 케빈 베이컨의 6단계 법칙
// 이 문제도 Floyd-Warshall algorithm을 이용하는 문제이다.
// 양방향임을 유의해야 한다! 이거 간과하면 엉뚱한 결과가 나온다!
// 제한시간 2초 중 0ms(2,152KB)가 소요되었다.
// 맞은사람 3889/6175로 상위 62.97%에 rank되었다.

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

const int INF = 999;
int g_N, g_M;
vector<vector<int>> g_graph;
vector<int> g_sum;

void floyd_warshall()
{
	for (int k = 1; k < g_N + 1; k++) {
		for (int i = 1; i < g_N + 1; i++) {
			for (int j = 1; j < g_N + 1; j++) {
				if (g_graph[i][k] + g_graph[k][j] < g_graph[i][j]) {
					g_graph[i][j] = g_graph[i][k] + g_graph[k][j];
				}
			}
		}
	}
}

int main()
{
	FAST;
	cin >> g_N >> g_M;
	g_graph.resize(g_N + 1, vector<int>(g_N + 1, INF));
	g_sum.resize(g_N + 1, 0);
	for (int i = 1; i < g_N + 1; i++) g_graph[i][i] = 0;

	int r, c;
	for (int i = 0; i < g_M; i++) {
		cin >> r >> c;
		g_graph[r][c] = 1;
		g_graph[c][r] = 1; // 양방향이다!
	}
	floyd_warshall();

	int minval = INF, minnum = 1;
	for (int i = 1; i < g_N + 1; i++) {
		for (int j = 1; j < g_N + 1; j++) {
			g_sum[i] += g_graph[i][j];
		}
		if (g_sum[i] < minval) { minval = g_sum[i]; minnum = i; }
	}
	cout << minnum << "\n";
}