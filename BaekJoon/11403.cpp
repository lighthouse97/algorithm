// 11403.cpp
// 경로 찾기
// Floyd-Warshall 알고리즘을 이용하는 기본적인 문제이다.
// 자신이 자신한테 가는 경로는 없다고 전제를 하기 때문에 자신 -> 자신의 직접적인 경로의 비용은 INF인 것에 유의한다.
// 제한시간 1초 중 0ms(2,056KB)가 소요되었다.
// 맞은사람 1864/10446로 상위 17.84%에 rank되었다.

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

const int INF = 999;
int g_N;
int g_graph[101][101];

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
	cin >> g_N;
	for (int i = 1; i < g_N + 1; i++) {
		for (int j = 1; j < g_N + 1; j++) {
			cin >> g_graph[i][j];
			if (!g_graph[i][j]) g_graph[i][j] = INF;
		}
	}
	floyd_warshall();
	for (int i = 1; i < g_N + 1; i++) {
		for (int j = 1; j < g_N + 1; j++)
			cout << (g_graph[i][j] == INF ? 0 : 1) << " ";
		cout << "\n";
	}
}