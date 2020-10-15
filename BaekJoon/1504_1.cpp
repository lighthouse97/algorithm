// 1504_1.cpp
// 특정한 최단 경로
// 대표적인 다익스트라 알고리즘을 사용한다.
// 기존 다익스트라 함수를 출발지점만 달리해서 여러 번 호출한다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
#include <algorithm> // sort, max, min
#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
#include <queue> // queue, priority_queue

using namespace std;

struct vertex {
	int name;
	int value;
	vertex() {}
	vertex(int n, int v) : name(n), value(v) {}
};

struct compare {
	bool operator() (const vertex& l, const vertex& r) const
	{
		return (l.value > r.value); // greater than, 오름차순
	}
};

int N, E, A, B;
vector<vector<vertex>> graph; // 정점 입력

vector<int> dijksta(int start)
{
	vector<int> dist(N + 1, INT_MAX);
	priority_queue<vertex, vector<vertex>, compare> mypq;
	int distance;
	vertex cur;
	mypq.push(vertex(start, 0));
	dist[start] = 0;
	while (!mypq.empty()) {
		cur = mypq.top();
		mypq.pop();
		if (cur.value > dist[cur.name]) continue; // 최단거리라서 동일 지점에 대해 pq의 거리가 dist보다 더 멀면 그냥 통과
		for (vertex i : graph[cur.name]) { // cur 정점의 child 검색
			distance = cur.value + i.value;
			if (distance < dist[i.name]) { // cur 정점과 child 정점 거리합이 dist[child]보다 작으면 작은 경로 우선으로
				dist[i.name] = distance;    // 탐색해야 하므로 pq에 넣는다. // pq에 name은 같고 value는 다른 여러개가 들어갈 수 있다.
				mypq.push(vertex(i.name, distance));
			}
		}
	}
	return dist;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	vector<int> dist_1, dist_A, dist_B;
	int from, to, val;
	int result_a, result_b;
	cin >> N >> E;
	graph.resize(N + 1);

	for (int i = 0; i < E; i++) {
		cin >> from >> to >> val;
		graph[from].push_back(vertex(to, val));
		graph[to].push_back(vertex(from, val));
	}
	cin >> A >> B;
	// dijkstra()함수를 6번 부르지 않고, 3번만 호출함으로써 목적을 달성할 수 있다.
	// dijkstra(1,N), dijkstra(A,N), dijkstra(B,N)에서 
	// dijkstra(1,N) : 1 -> A, 1 -> B
	// dijkstra(A,N) : A -> B, A -> N
	// dijkstra(B,N) : B -> N, B -> A
	// 조합이 나온다. 이를 가지고 1->A->B->N, 1->B->A->N의 값을 구할 수 있다.
	dist_1 = dijksta(1);
	dist_A = dijksta(A);
	dist_B = dijksta(B);
	if (dist_1[A] == INT_MAX || dist_A[B] == INT_MAX || dist_B[N] == INT_MAX) result_a = -1;
	else result_a = dist_1[A] + dist_A[B] + dist_B[N];
	if (dist_1[B] == INT_MAX || dist_B[A] == INT_MAX || dist_A[N] == INT_MAX) result_b = -1;
	else result_b = dist_1[B] + dist_B[A] + dist_A[N];

	if (result_a < 0 && result_b < 0)
		cout << -1 << "\n";
	else if (result_a > 0 && result_b > 0)
		cout << min(result_a, result_b) << "\n";
	else if (result_a > 0)
		cout << result_a << "\n";
	else
		cout << result_b << "\n";
}