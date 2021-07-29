// 14621.cpp
// 나만 안되는 연애
// University > 인하대학교 > 2017 인하대학교 프로그래밍 경진대회(IUPC) J번
// MST(Minimum Spanning Tree) 문제이다.
// 그냥 풀어보자!!!
// 제한시간 2초 중 0ms(2,344KB)가 소요되었다.
// 맞은사람 40/680로 상위 5.88%에 rank되었다.

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
	if (count < vcnt - 1) return -1;
	return minval;
}

int main()
{
	FAST;
	int N, M;
	cin >> N >> M;
	g_parent.resize(N + 1, -1);
	vector<int> sex(N + 1, 0); // 0 : male, 1 : female
	char ss;
	for (int i = 1; i < N + 1; i++) {
		cin >> ss;
		sex[i] = (ss == 'M') ? 0 : 1;
	}
	int u, v, d;
	for (int i = 0; i < M; i++) {
		cin >> u >> v >> d;
		if (sex[u] != sex[v]) g_graph.push_back({ u, v, d });
	}
	cout << kruskal(N) << "\n";
}