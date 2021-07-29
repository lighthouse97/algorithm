// 13905.cpp
// 세부
// University > 서강대학교 > 제12회 총장배 서강대학교 프로그래밍 대회 Champion F번
// MST 문제인데, BFS 또는 DFS로 출발점에서 도착점까지 경로를 따라가야 하는 부분이 추가된 문제이다.
// 제한시간 1초 중 144ms(13,648KB)가 소요되었다.
// 맞은사람 73/304로 상위 24.01%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil, hypot
#include <vector>
//#include <list>
#include <algorithm> // sort, max, min, copy, swap, unique
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

struct edge {
	int from, to, cost;
	edge() : from(0), to(0), cost(0) {}
	edge(int f, int t, int c) : from(f), to(t), cost(c) {}
	bool operator< (const edge& rhs) { return cost < rhs.cost; }
};

vector<edge> g_graph;
vector<int> g_parent;
vector<vector<edge>> g_st; // spanning tree

int djs_find(int item)
{
	if (g_parent[item] < 0) return item;
	return g_parent[item] = djs_find(g_parent[item]);
}

void djs_union(int u, int v)
{
	int u1 = djs_find(u);
	int v1 = djs_find(v);
	if (u1 == v1) return;
	else {
		g_parent[u1] += g_parent[v1];
		g_parent[v1] = u1;
	}
}

int kruskal(int vcnt)
{
	int count = 0, minval = 0;
	sort(g_graph.begin(), g_graph.end()); // 비용에 대해 오름차순
	for (edge& x : g_graph) {
		if (djs_find(x.from) != djs_find(x.to)) {
			djs_union(x.from, x.to);
			count++;
			minval += x.cost;
			g_st[x.from].push_back({ x.from, x.to, x.cost }); // spanning tree 구축(정방향)
			g_st[x.to].push_back({ x.to, x.from, x.cost }); // spanning tree 구축(역방향)
		}
		if (count == vcnt - 1) break;
	}
	return minval;
}

int main()
{
	FAST;
	int N, M, s, t;
	cin >> N >> M >> s >> t;
	g_graph.resize(M, { 0, 0, 0 });
	g_parent.resize(N + 1, -1);
	g_st.resize(N + 1);
	int h1, h2, k;
	for (int i = 0; i < M; i++) {
		cin >> h1 >> h2 >> k;
		g_graph[i] = { h1, h2, -k };
	}
	kruskal(N);

	queue<int> myq; // bfs로 s -> t 경로 탐색
	vector<int> visit(N + 1, 0);
	myq.push(s);
	visit[s] = -9999999;
	while (!myq.empty()) {
		int cur = myq.front(); myq.pop();
		if (cur == t) break;
		for (edge& next : g_st[cur]) {
			if (!visit[next.to]) {
				visit[next.to] = max(visit[cur], next.cost);
				myq.push(next.to);
			}
		}
	}
	cout << -visit[t] << "\n";
}