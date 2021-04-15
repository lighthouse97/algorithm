// 14938.cpp
// 서강 그라운드
// University > 서강대학교 > 2017 Sogang Programming Contest - Master D번
// Floyd-Warshall로 풀 수 있다. 앞에서 푼 1508문제와 비슷하다.
// Floyd-Warshall로 각 정점에 대해 최단 경로를 모두 구한다.
// 다음 각 정점마다 최단 경로 중 수색 범위에 들어가는 경로의 아이템 수를 합산한다.
// 각 정점의 합산된 아이템 수 중 가장 큰 값을 고른다.
// 제한시간 1초 중 0ms(2,056KB)가 소요되었다.
// 맞은사람 417/824로 상위 50.60%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
//#include <vector>
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
int g_N;
int g_graph[101][101];
int g_item[101];

void floyd_warshall()
{
	for (int k = 1; k < g_N + 1; k++) {
		for (int i = 1; i < g_N + 1; i++) {
			for (int j = 1; j < g_N + 1; j++) {
				if (g_graph[i][k] + g_graph[k][j] < g_graph[i][j])
					g_graph[i][j] = g_graph[i][k] + g_graph[k][j];
			}
		}
	}
}

int main()
{
	FAST;

	int m, r;
	cin >> g_N >> m >> r;
	for (int i = 1; i < g_N + 1; i++) { // initialize
		for (int j = 1; j < g_N + 1; j++) {
			if (i == j) g_graph[i][j] = 0;
			else g_graph[i][j] = INF;
		}
	}
	for (int i = 1; i < g_N + 1; i++) cin >> g_item[i];
	int s, e, l;
	for (int i = 0; i < r; i++) {
		cin >> s >> e >> l;
		g_graph[s][e] = g_graph[e][s] = l;
	}
	floyd_warshall();

	int sum = 0, maxsum = 0;
	for (int i = 1; i < g_N + 1; i++) {
		sum = 0;
		for (int j = 1; j < g_N + 1; j++) {
			if (g_graph[i][j] < m + 1) sum += g_item[j];
		}
		if (sum > maxsum) maxsum = sum;
	}
	cout << maxsum << "\n";
}