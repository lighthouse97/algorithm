// 1956.cpp
// 운동
// 플로이드-와샬(floyd-warshall) 알고리즘을 이용하는 문제이다.
// 구한다음 왕복 싸이클을 찾아서 그 중 가장 작은 값을 구한다.
// 108ms가 소요되었다.
// 초기화할 때 i==j일 때 0을 넣지 않고 INF로 초기화한다음(정석에서 약간 변형) 플로이드-와샬을 돌려서
// graph[i][i]일 때의 최소값을 구하면 시간을 더 줄일 수 있다.(108ms -> 100ms)


#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
//#include <queue> // queue, priority_queue

using namespace std;

int V, E;
vector<vector<int>> graph;
const int INF = 10001;

void floyd_warshall()
{
	// 거쳐야 할 경로(1~V)
	for (int k = 1; k <= V; k++) {
		// 출발점(1~V)
		for (int i = 1; i <= V; i++) {
			// 도착점(1~N)
			for (int j = 1; j <= V; j++) {
				if (graph[i][k] + graph[k][j] < graph[i][j])
					graph[i][j] = graph[i][k] + graph[k][j];
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int a, b, c, minval = INF;
	cin >> V >> E;
	graph.resize(V + 1, vector<int>(V + 1, INF)); // initialise to INF
	for (int i = 1; i <= V; i++)
		graph[i][i] = 0;

	for (int i = 0; i < E; i++) {
		cin >> a >> b >> c;
		graph[a][b] = c;
	}
	floyd_warshall();
	for (int i = 1; i <= V; i++) {
		for (int j = i + 1; j <= V; j++) {
			if (graph[i][j] + graph[j][i] < minval)
				minval = graph[i][j] + graph[j][i];
		}
	}
	cout << (minval == INF ? -1 : minval) << "\n";
}
