// 11562.cpp
// 백양로 브레이크
// University > 연세대학교 > 2015 연세대학교 프로그래밍 경시대회 F번
// 처음부터 방향을 잘 못 잡았다!
// 정방향 기준으로 최단 거리를 잡고 정방향으로 갈 수 없는 위치를 역방향으로 따라가면서 양방향은 제외하고
// 나머지 역방향인 거리의 합을 답으로 정했는데 이렇게 하면 틀린다! 예를 들어,
// 1 -> 5에서 1 -> 2 -> 3 -> 5 경로와 1 -> 6 <-> 7 <-> 8 <-> 5의 경로가 있을 경우,
// 정방향 기준 최단 거리를 잡으면 당연히 1 -> 2 -> 3 -> 5 경로가 선택되고 5 -> 1로 갈 수 있으려면, 3개의 경로를 양방향으로 만들어 주어야 한다.
// 그러나 선택이 안된 1 -> 6 <-> 7 <-> 8 <-> 5 경로를 선택하면 1개의 경로만 양방향으로 만들어주면 된다.
// 따라서 정방향 기준 최단 경로를 잡으면 답이 나올 수가 없다.(함정으로 예제만하면 답이 나온다.)
// 그러면 어떻게 하느냐?
// 힌트를 보고야 말았는데... 결국 정방향은 관심없고 역방향에서 양방향 제외하고 경로가 최소가 될 때의 경로수를 구하면 된다.
// 즉 입력받을 때 양방향이 아니면 a -> b는 0, b -> a는 1, 양방향이면 둘다 0으로 입력한다.
// 그리고 Floyd-Warshall을 돌리면, 정방향으로 갈 수 있는 경로는 최단 경로가 모두 0이 될 것이고,
// 정방향으로 갈 수 없는 경로 중 역방향에서 양방향을 제외하고 최단 경로수가 구해진다. 즉 문제의 취지에 맞는 것이다.
// 제한시간 1초 중 24ms(2,284KB)가 소요되었다.
// 맞은사람 27/656로 상위 4.11%에 rank되었다.

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

const int INF = 987654421;
int g_N;
vector<vector<int>> g_graph;

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
	int m;
	cin >> g_N >> m;
	g_graph.resize(g_N + 1, vector<int>(g_N + 1, INF));
	for (int i = 1; i < g_N + 1; i++) g_graph[i][i] = 0;
	int u, v, b;
	for (int i = 0; i < m; i++) { // 여기가 핵심이다!
		cin >> u >> v >> b;
		g_graph[u][v] = 0;
		g_graph[v][u] = b ? 0 : 1;
	}
	floyd_warshall();
	int k, s, e; // query
	cin >> k;
	for (int i = 0; i < k; i++) {
		cin >> s >> e;
		cout << g_graph[s][e] << "\n";
	}
}