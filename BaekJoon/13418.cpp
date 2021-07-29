// 13418.cpp
// 학교 탐방하기
// University > 국민대학교 > 2016 국민대학교 교내 경시대회 F번
// MST
// 그냥 풀면 된다. cost 부호 바꿔서 Kruskal 2번 돌린다.
// 제한시간 1초 중 124ms(7,880KB)가 소요되었다.
// 맞은사람 19/578로 상위 3.28%에 rank되었다.

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
//#include <queue> // queue, priority_queue
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
		}
		if (count == vcnt - 1) break;
	}
	return minval;
}

int main()
{
	FAST;
	int N, M;
	cin >> N >> M;
	g_graph.resize(M + 1, { 0, 0, 0 });
	g_parent.resize(N + 1, -1);
	int a, b, c;
	for (int i = 0; i < M + 1; i++) {
		cin >> a >> b >> c;
		c ^= 1;
		g_graph[i] = { a, b, c };
	}
	int minval = kruskal(N + 1);
	minval *= minval;

	for (int i = 0; i < M + 1; i++) g_graph[i].cost *= -1; // 최대값
	g_parent.assign(N + 1, -1); // Disjoint-Set도 초기화해야 함!!!
	int maxval = kruskal(N + 1);
	maxval *= maxval;
	cout << (maxval - minval) << "\n";
}