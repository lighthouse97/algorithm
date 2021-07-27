// 4792.cpp
// 레드 블루 스패닝 트리
// University > North American Invitational Programming Contest > UCIPC 2012 G번
// 파란색 간선의 cost를 1, 빨간색 간선의 cost를 0으로 하고 MST 돌린다.
// 그러면 파란색 간선을 최소로 사용했을 때의 파란색 간선의 갯수가 나온다.
// 다음 파란색 간선의 cost를 -1, 빨간색 간선의 cost를 0으로 하고 MST 돌린다.
// 결과에 -1 곱하면 파란색 간선을 최대로 사용했을 때의 파란색 간선의 갯수가 나온다.
// 파란색 간선의 최소값과 최대값 사이의 범위에 k가 있으면 k개의 파란색 간선으로 ST를 구성할 수 있는
// 것이다.
// 아래는 처음에 틀리게 생각한 경우이다.
// MST, 파란색 간선의 cost를 0, 빨간색 간선의 cost를 1로 하고
// MST 구한다.
// MST 중에 파란색 간선의 갯수가 K개가 넘어가면 빨간색 간선으로 넘어간다.
///////
// 제한시간 3초 중 196ms(6,832KB)가 소요되었다.
// 맞은사람 60/639로 상위 9.38%에 rank되었다.

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
	int n, m, k;
	while (true) {
		cin >> n >> m >> k;
		if (!n && !m && !k) break;
		g_graph.assign(m, { 0, 0, 0 });
		g_parent.assign(n + 1, -1);
		char c;
		int color, f, t;
		for (int i = 0; i < m; i++) {
			cin >> c >> f >> t;
			color = (c == 'B') ? 1 : 0;
			g_graph[i] = { f, t, color };
		}
		int minval = kruskal(n); // blue min value

		g_parent.assign(n + 1, -1);
		for (int i = 0; i < m; i++) g_graph[i].cost *= -1;
		int maxval = -kruskal(n); // blue max value
		cout << (minval <= k && k <= maxval ? 1 : 0) << "\n";
	}
}