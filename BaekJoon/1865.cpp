// 1865.cpp
// 웜홀
// 벨만-포드 알고리즘을 사용하는 문제이다.
// 벨만-포드로 child를 업데이트할 때 업데이트되는 child에 출발점이 포함이 되는지 검사한다.
// 벨만-포드로 풀어서 negative cycle이 있는지 검사해도 되지만 다익스트라로 풀어서 출발점이 0보다 작은지로
// 검사해도 된다.(다익스트라로 푸는 것이 좀 더 시간이 절약된다.)

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
//#include <algorithm> // sort, max, min
#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
//#include <queue> // queue, priority_queue

using namespace std;

struct vertex {
	int name;
	int value;
	vertex() {}
	vertex(int n, int v) : name(n), value(v) {}
};

int TC, N, M, W;
int ncycle = 0; // negative cycle
vector<vector<vertex>> graph; // 정점 입력
vector<int> dist; // 출발점에서 각 정점까지 거리

void bellman_ford()
{
	int distance;
	dist[1] = 0;
	for (int i = 1; i <= N; i++) { // 업데이트 된 정점에서 탐색을 빠뜨리지 않기 위해 n-1번(n-1개의 간선)까지 돌린다.(n번째는 확인용) 
		for (int j = 1; j <= N; j++) {
			for (vertex x : graph[j]) { // 각 점의 모든 child에 대해
				distance = dist[j] + x.value;
				if (dist[j] != INT_MAX && distance < dist[x.name]) { // 각 점의 최단 경로를 업데이트한다.(최단경로 update된 점에 대해)
					dist[x.name] = distance;
					if (i == N) ncycle = 1; // i가 n-1 다음 n번째에도 update할 것이 생기면 이것은 negative cycle이 생긴 것이다.
				}
			}
		}
	}
}

void do_test()
{
	int s, e, t;
	cin >> N >> M >> W;
	graph.resize(N + 1);
	dist.resize(N + 1, INT_MAX);
	for (int i = 1; i <= M; i++) {
		cin >> s >> e >> t;
		graph[s].push_back(vertex(e, t));
		graph[e].push_back(vertex(s, t));
	}
	for (int i = 1; i <= W; i++) {
		cin >> s >> e >> t;
		graph[s].push_back(vertex(e, -t));
	}
	bellman_ford();
	if (ncycle) cout << "YES" << "\n";
	else cout << "NO" << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> TC;
	while (TC--) {
		do_test();
		graph.clear();
		dist.clear();
		ncycle = 0;
	}	
}