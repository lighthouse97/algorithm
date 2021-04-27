// 10282.cpp
// 해킹
// 이것도 쉬운 dijkstra 문제이다.
// 간선 정보로 그래프 만들고, dijkstra 돌려서 도달 가능한 정점의 수, 가장 큰 최단 거리 값을 출력하면 된다.
// 제한시간 2초 중 136ms(4,252KB)가 소요되었다.
// 맞은사람 170/1463로 상위 11.61%에 rank되었다.

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

void doTest()
{
	int d, c;
	cin >> g_N >> d >> c;
	g_graph.resize(g_N + 1);
	g_dist.resize(g_N + 1, INF);

	int a, b, s;
	for (int i = 0; i < d; i++) {
		cin >> a >> b >> s;
		g_graph[b].push_back({ a, s });
	}
	dijkstra(c);
	int sum = 0, ts = 0;
	for (int i = 1; i < g_N + 1; i++) {
		if (g_dist[i] != INF) {
			sum++;
			if (g_dist[i] > ts) ts = g_dist[i];
		}
	}
	cout << sum << " " << ts << "\n";
	g_graph.clear();
	g_dist.clear();
}

int main()
{
	FAST;
	int t;
	cin >> t;
	while (t--) doTest();
}