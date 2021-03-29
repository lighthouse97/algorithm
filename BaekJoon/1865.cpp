// 1865.cpp
// 웜홀
// 벨만-포드 알고리즘을 사용하는 문제이다.
// 문제의 조건이 출발점 1에서 어느 순간 임의의 출발점으로 바뀌었다.
// 따라서 모든 출발점에 대해서 벨만포드를 돌려봐야 하지만 이렇게 하면 TLE가 발생할 것이고,
// 출발점을 1로 잡되 출발점을 포함하지 않더라도 사이클이 발생하면 특정 출발점에서 시간이 거꾸로 가는 경우가 생기는 것으로 판단할 수 있다. 
// 출발점과 만나지 않는 정점들에서 사이클이 발생할 수 있으므로 이전에 했던 다익스트라 방식은 사용할 수 없다.(무한루프 발생할 수 있다)
// 제한시간 2초 중 32ms(2,148KB)가 소요되었다.
// 맞은사람 1159/2153로 상위 53.83%에 rank되었다.

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

struct vertex {
	int name;
	int value;
	vertex() {}
	vertex(int n, int v) : name(n), value(v) {}
};

const int INF = 25000000;
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
				if (distance < dist[x.name]) { // 각 점의 최단 경로를 업데이트한다.(최단경로 update된 점에 대해)
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
	dist.resize(N + 1, INF);
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