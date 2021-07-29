// 10423.cpp
// 전기가 부족해
// University > 서강대학교 > 2014 Sogang Programming Contest - Master E번
// University > 서강대학교 > 2014 Sogang Programming Contest - Champion D번
// MST 문제인데... MST에서 간선을 연결할 때마다 양 정점이 모두 발전소 집합에 속하는지만 체크해서
// 양쪽이 모두 속하는 경우만 간선 연결에서 배제한다.
// 즉 한쪽만 발전소이거나 양쪽 모두 발전소가 아닌 경우만 연결해서 간선의 최소값을 구한다.
// 제한시간 1초 중 32ms(3,200KB)가 소요되었다.
// 맞은사람 35/628로 상위 5.57%에 rank되었다.

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
/////
vector<bool> g_plant;

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
		int f1 = djs_find(x.from);
		int f2 = djs_find(x.to);
		if (f1 != f2) {
			if (!g_plant[f1] || !g_plant[f2]) { // 양쪽이 모두 다 발전소 아닌 경우
				if (g_plant[f2]) djs_union(x.to, x.from);
				else djs_union(x.from, x.to);
				count++;
				minval += x.cost;
			}
		}
		if (count == vcnt - 1) break;
	}
	return minval;
}

int main()
{
	FAST;
	int N, M, K;
	cin >> N >> M >> K;
	g_graph.resize(M, { 0, 0, 0 });
	g_parent.resize(N + 1, -1);
	g_plant.resize(N + 1, false);
	int p;
	for (int i = 0; i < K; i++) {
		cin >> p;
		g_plant[p] = true;
	}
	int u, v, w;
	for (int i = 0; i < M; i++) {
		cin >> u >> v >> w;
		g_graph[i] = { u, v, w };
	}
	cout << kruskal(N) << "\n";
}