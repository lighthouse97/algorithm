// 11779.cpp
// 최소비용 구하기2
// '최소비용 구하기(1916)'에서 최소비용뿐만 아니라 그 경로까지 같이
// 구하는 문제이다.
// 24ms(3332KB) 소요되었다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
#include <stack>
//#include <set>
//#include <cmath> // sqrt
#include <queue> // queue, priority_queue

using namespace std;

const int MAX_VAL = 987654321;

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

int N, M;
vector<vector<vertex>> graph; // 정점 입력
vector<vector<int>> dist; // 출발점에서 각 정점까지 거리([][0] : 최소거리, [][1] : 앞에 연결된 정점
priority_queue<vertex, vector<vertex>, compare> mypq; // 방문할 정점에 대한 우선순위 큐

void dijksta(int start)
{
	int distance;
	vertex cur;
	mypq.push(vertex(start, 0));
	dist[start][0] = 0;
	while (!mypq.empty()) {
		cur = mypq.top();
		mypq.pop();
		if (cur.value > dist[cur.name][0]) continue; // 최단거리라서 동일 지점에 대해 pq의 거리가 dist보다 더 멀면 그냥 통과
		for (vertex i : graph[cur.name]) { // cur 정점의 child 검색
			distance = cur.value + i.value;
			if (distance < dist[i.name][0]) { // cur 정점과 child 정점 거리합이 dist[child]보다 작으면 작은 경로 우선으로
				dist[i.name][0] = distance;    // 탐색해야 하므로 pq에 넣는다. // pq에 name은 같고 value는 다른 여러개가 들어갈 수 있다.
				dist[i.name][1] = cur.name; // 최단 거리 직전 경로 기록
				mypq.push(vertex(i.name, distance));
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int from, to, val;
	int start, goal, cur;
	stack<int> path;
	cin >> N >> M;
	graph.resize(N + 1);
	dist.resize(N + 1, vector<int>(2));
	for (int i = 1; i <= N; i++) { // initialise the dist
		dist[i][0] = MAX_VAL;
		dist[i][1] = 0;
	}

	for (int i = 0; i < M; i++) {
		cin >> from >> to >> val;
		graph[from].push_back(vertex(to, val));
	}
	cin >> start >> goal;
	dijksta(start);
	cout << dist[goal][0] << "\n";
	// find the path
	cur = goal;
	while (1) {
		path.push(cur);
		if (cur == start) break;
		cur = dist[cur][1];
	}
	cout << path.size() << "\n";
	while (!path.empty()) {
		cout << path.top() << " ";
		path.pop();
	}
	cout << "\n";
}