// 16202.cpp
// MST 게임
// MST를 여러번 부르는 문제이다.
// MST를 매번 부를 때마다 정렬된 g_graph의 시작 index를 하나씩 증가시켜 준다.
// 제한시간 2초 중 12ms(2,260KB)가 소요되었다.
// 맞은사람 30/186로 상위 16.12%에 rank되었다.

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

int kruskal(int vcnt, int start)
{
	int count = 0, minval = 0;
	for (int i = start; i < g_graph.size(); i++) {
		edge& x = g_graph[i];
		if (djs_find(x.from) != djs_find(x.to)) {
			djs_union(x.from, x.to);
			count++;
			minval += x.cost;
		}
		if (count == vcnt - 1) break;
	}
	if (count < vcnt - 1) return 0;
	return minval;
}

int main()
{
	FAST;
	int N, M, K;
	cin >> N >> M >> K;
	g_graph.resize(M, { 0, 0, 0 });
	int x, y;
	for (int i = 0; i < M; i++) {
		cin >> x >> y;
		g_graph[i] = { x, y, i + 1 }; // 이미 정렬되어 저장
	}
	vector<int> answer(K, 0);
	for (int i = 0; i < K; i++) {
		g_parent.assign(N + 1, -1);
		int val = kruskal(N, i);
		if (!val) break;
		answer[i] = val;
	}
	for (int x : answer) cout << x << " ";
	cout << "\n";
}