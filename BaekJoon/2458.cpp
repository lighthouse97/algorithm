// 2458.cpp
// 키 순서
// Floyd-Warshall, 9205와 비슷한 문제이다.
// 갈 수 있으면 1, 갈 수 없으면 0 표시한 다음에, Floyd-Warshall 돌린다.
// 0인 경로만 탐색하면서 a->b, b->a 모두 0인 경로만 카운트해서 전체 정점 갯수에서 빼준다.
// 즉 특정 정점에서 앞, 뒤 번호로 연결된 경로가 하나도 없으면 그 정점은 자신의 키 순서를 알 수 없는 정점이다.
// 예로 문제에서 정점 4는 앞뒤로 모든 정점이 연결되어 있고, 나머지 정점은 앞뒤로 연결이 전혀 안된 것이 하나 이상 있다.
// 그게 답이다!
// dfs를 이용해서 풀면 좀 더 빨리 처리가 된다.
// floyd_warshall() 함수에서 g_graph[i][j], g_grapj[i][k], g_graph[k][j] 모두 query하는 방법과 g_grapj[i][k], g_graph[k][j] 2개만 query하는 방법
// 이 있는데, g_grapj[i][k], g_graph[k][j] 2개만 query하는 방법이 훨씬 수행시간이 줄어든다.
// 대략, 340ms -> 132ms로 수행시간이 1/3 가량 줄어든다.
// 제한시간 1초 중 340ms(3,080KB)가 소요되었다.
// 맞은사람 1801/2824로 상위 63.77%에 rank되었다.
// floyd_warshall() 함수에서 최적화 했을 경우, 340ms -> 132ms로 최적화되고 맞은 사람 1027/2825로 상위 36.35%에 rank 된다. 

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

vector<vector<int>> g_graph;
int g_N;

void floyd_warshall()
{
	for (int k = 1; k < g_N + 1; k++) {
		for (int i = 1; i < g_N + 1; i++) {
			for (int j = 1; j < g_N + 1; j++) {
				//if (!g_graph[i][j]) // 갈 수 없는 경우만 따진다.
				//	g_graph[i][j] = g_graph[i][k] * g_graph[k][j];
				if (g_graph[i][k] & g_graph[k][j]) g_graph[i][j] = 1;
			}
		}
	}
}

int main()
{
	FAST;
	int M;
	cin >> g_N >> M;
	g_graph.resize(g_N + 1, vector<int>(g_N + 1, 0));

	int a, b;
	for (int i = 1; i < g_N + 1; i++) g_graph[i][i] = 1;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		g_graph[a][b] = 1;
	}
	floyd_warshall();
	int cnt = 0;
	for (int i = 1; i < g_N + 1; i++) {
		for (int j = 1; j < g_N + 1; j++) {
			if (!g_graph[i][j] && !g_graph[j][i]) { cnt++; break; }
		}
	}
	cout << (g_N - cnt) << "\n";
}