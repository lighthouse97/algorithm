// 11404.cpp
// 플로이드
// 플로이드-와샬(floyd-warshall) 알고리즘을 이용하는 문제이다.
// 특정 출발점이 아닌 모든 정점에 대한 최단거리를 구한다.
// 따라서 다익스트라(O((V+E)logV)), 벨만-포드(O(VE))에 비해
// 시간복잡도가 더 높다.매우 높은 편에 속한다.(O(V^3))
// 알고리즘 자체는 쉬운 편이다.
// 재채점에서 틀렸다.(20.03.05)
// 최소값을 찾으므로 전체 경로의 초기 비용을 INF로 초기화 하는데 이 값이 n최대값(100)*cost최대값(100,000)=10,000,000
// 보다 커야 한다. 그런데 INF값을 cost최대값 100,000기준 100,001을 했으니 cost값이 큰 문제에서는 틀릴 수 밖에 없다.
// 제한시간 1초 중 24ms(2,116KB)가 소요되었다.
// 맞은사람 394/3337로 상위 11.80%에 rank되었다.

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

int N, M;
vector<vector<int>> graph;
const int INF = 10000001;

void floyd_warshall()
{
	// 거쳐야 할 경로(1~N)
	for (int k = 1; k <= N; k++) {
		// 출발점(1~N)
		for (int i = 1; i <= N; i++) {
			// 도착점(1~N)
			for (int j = 1; j <= N; j++) {
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

	int a, b, c;
	cin >> N >> M;
	graph.resize(N+1, vector<int>(N+1, INF)); // initialise to INF
	for (int i = 1; i <= N; i++)
		graph[i][i] = 0;
	
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> c;
		if(c < graph[a][b]) graph[a][b] = c;
	}
	floyd_warshall();
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << (graph[i][j] == INF ? 0 : graph[i][j]) << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}
