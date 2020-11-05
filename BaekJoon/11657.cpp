// 11657.cpp
// 타임머신
// 벨만-포드 알고리즘을 사용하는 문제이다.
// 문제의 경로에 -값이 있어 다익스트라 알고리즘으로는 문제를
// 풀 수 없고 벨만-포드 알고리즘으로 문제를 푼다.
// 다이스트라 알고리즘이 O((V+E)logV)의 시간복잡도를 가지는데 비해,
// O(E*V)의 시간복잡도를 가진다. (시간복잡도가 상대적으로 큰데 대신 음수 경로에 대해서도 처리할 수 있다.)
// 2020.11.05 추가!
// distance가 -INT_MAX보다 더 작아지는 underflow가 날 수 있기 때문에 distance를 long long type으로 잡아주어야 한다.
// 이거 때문에 '출력 초과'발생하여 AC받지 못했다.
// 왜 underflow가 발생하느냐?
// V : 500, E : 6000, C : -10,000 이라 할 때,
// 정점을 잇는 모든 간선이 왕복이고 각 간선의 cost가 -10,000이라면, bellman-ford 모두 다 돌리면 500 * 6000 * -10,000 < -INT_MAX
// 따라서 long long 으로 잡아주어야 한다.
// 제한시간 1초 중 8ms(2,148KB)가 소요되었다.
// 맞은사람 396/1346로 상위 29.42%에 rank되었다.

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

int N, M;
int ncycle = 0; // negative cycle
vector<vector<vertex>> graph; // 정점 입력
vector<long long> dist; // 출발점에서 각 정점까지 거리

void bellman_ford()
{
	long long distance;
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

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int a, b, c;
	cin >> N >> M;
	graph.resize(N + 1);
	dist.resize(N + 1, INT_MAX);
	for (int i = 1; i <= M; i++) {
		cin >> a >> b >> c;
		graph[a].push_back(vertex(b, c));
	}
	bellman_ford();
	if (ncycle) cout << -1 << "\n"; // negative cycle exist!
	else {
		for (int i = 2; i <= N; i++) {
			cout << ((dist[i] == INT_MAX) ? -1 : dist[i]) << "\n";
		}
	}
}