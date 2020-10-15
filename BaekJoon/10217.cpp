// 10217.cpp
// KCM Travel
// 최단 경로를 찾는데 비용의 제약 조건이 따르는 경로이다.
// 따라서 다익스트라로 최단 경로를 찾되,
// 최단 거리를 저장하는 dist배열을 각 정점에 최단 거리 하나만
// 저장하는 것이 아니라 비용별로 저장이 되는 이차원 배열로 저장되어야 한다.
// 최종 목적지에서 비용 초과를 제외하고 나머지 최단 거리 후보들 중 가장 작은
// 값을 선택한다.

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
#include <queue> // queue, priority_queue

using namespace std;

struct vertex {
	int name;
	int cost;
	int time;
	vertex() {}
	vertex(int n, int c, int t) : name(n), cost(c), time(t) {}
};

struct compare {
	bool operator() (const vertex& l, const vertex& r) const
	{
		return (l.time > r.time); // greater than, 오름차순
	}
};

int T, N, M, K;
vector<vector<vertex>> graph;
vector<vector<int>> dist;
priority_queue<vertex, vector<vertex>, compare> mypq; // 방문할 정점에 대한 우선순위 큐
const int INF = 999999;

void dijkstra(int start)
{
	int dur, exp;
	vertex cur;
	mypq.push(vertex(start, 0, 0));
	dist[start][0] = 0;
	while (!mypq.empty()) {
		cur = mypq.top();
		mypq.pop();
		if (cur.cost >= M) continue;
		if (cur.time > dist[cur.name][cur.cost]) continue; // 같은 정점에서 비용이 같으면 시간이 작은 것을 선택.
		for (vertex i : graph[cur.name]) {
			dur = cur.time + i.time;
			exp = cur.cost + i.cost;
			if (exp <= M && dur < dist[i.name][exp]) {
				dist[i.name][exp] = dur;
				mypq.push(vertex(i.name, exp, dur));
			}
		}
	}
}

void do_test()
{
	int u, v, c, d;
	int result = INF;
	cin >> N >> M >> K;
	graph.resize(N + 1);
	dist.resize(N + 1, vector<int>(10001, INF)); // 비용이 10000으로 정해져 있기 때문에 비용에 대한 시간값을 저장한다.
	for (int i = 0; i < K; i++) {
		cin >> u >> v >> c >> d;
		graph[u].push_back(vertex(v, c, d));
	}
	dijkstra(1);
	for (int i = 1; i <= M; i++) {
		if (dist[N][i] < result) {
			result = dist[N][i];
		}
	}
	if (result == INF) cout << "Poor KCM" << "\n";
	else cout << result << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> T;
	while (T--) {
		do_test();
		graph.clear();
		dist.clear();
	}
}