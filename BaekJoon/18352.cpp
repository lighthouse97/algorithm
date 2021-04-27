// 18352.cpp
// 특정 거리의 도시 찾기
// 이건 아주 쉬운 다익스트라(Dijkstra) 문제이다.
// 정점간 거리 1로 그래프 데이터를 입력받아 dikjstra를 돌린다.
// 출발점 X로부터 최단 거리 K인 모든 정점들을 출력한다. 최단 거리 K인 정점이 하나도 없을 경우 -1을 출력한다.
// 제한시간 2초 중 468ms(27,888KB)가 소요되었다.
// 맞은사람 182/1533로 상위 11.87%에 rank되었다.

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
#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const int INF = 987654321;
struct vertex {
	int name;
	int value;
	vertex() {}
	vertex(int n, int v) : name(n), value(v) {}
	bool operator< (const vertex& rhs) const { return value > rhs.value; } // 오름차순 정렬
};

int g_N;
vector<vector<vertex>> g_graph;
vector<int> g_dist;

void dijkstra(int start)
{
	priority_queue<vertex> mypq;
	int distance;
	vertex cur;
	mypq.push(vertex(start, 0));
	g_dist[start] = 0;
	while (!mypq.empty()) {
		cur = mypq.top();
		mypq.pop();
		if (cur.value > g_dist[cur.name]) continue;
		for (vertex i : g_graph[cur.name]) {
			distance = cur.value + i.value;
			if (distance < g_dist[i.name]) {
				g_dist[i.name] = distance;
				mypq.push(vertex(i.name, distance));
			}
		}
	}
}

int main()
{
	FAST;
	int M, K, X;
	cin >> g_N >> M >> K >> X;
	g_graph.resize(g_N + 1);
	g_dist.resize(g_N + 1, INF);

	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		g_graph[a].push_back({ b, 1 });
	}
	dijkstra(X);
	int answer = 0;
	for (int i = 1; i < g_N + 1; i++) {
		if (i == X) continue;
		if (g_dist[i] == K) {
			answer++;
			cout << i << "\n";
		}
	}
	if (!answer) cout << -1 << "\n";
}