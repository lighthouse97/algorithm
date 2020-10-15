// 1865_1.cpp
// 웜홀
// 다익스트라를 이용해서 풀어서 시간을 좀 더 단축시켜 본다.
// 다익스트라로 풀되 이 문제의 경우 priority queue를 사용하면 메모리 초과가 발생하기 때문에 queue를 사용해야 된다.
// 벨만포드로 풀 경우 36ms, 다익스트라로 풀면 4ms가 소요된다.

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
#include <queue> // queue, priority_queue

using namespace std;

struct vertex {
	int name;
	int value;
	vertex() {}
	vertex(int n, int v) : name(n), value(v) {}
};

int TC, N, M, W;
vector<vector<vertex>> graph;
vector<int> dist;
queue<vertex> myq;

void dijksta(int start)
{
	int distance;
	vertex cur;
	myq.push(vertex(start, 0));
	dist[start] = 0;
	while (!myq.empty()) {
		cur = myq.front();
		myq.pop();
		if (cur.name == start && cur.value < 0) break;
		if (cur.value > dist[cur.name]) continue;
		for (vertex i : graph[cur.name]) {
			distance = cur.value + i.value;
			if (distance < dist[i.name]) {
				dist[i.name] = distance;
				myq.push(vertex(i.name, distance));
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
	dijksta(1);
	if (dist[1] < 0) cout << "YES" << "\n";
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
		while (!myq.empty()) myq.pop();
	}
}