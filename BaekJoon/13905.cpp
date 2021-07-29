// 13905.cpp
// 세부
// University > 서강대학교 > 제12회 총장배 서강대학교 프로그래밍 대회 Champion F번
// MST 문제인데, 간선의 cost가 정렬이 된 상태이기 때문에 출발점과 도착점이 같은 집합으로 묶이는 순간의 간선의 가중치가 답이 된다.
// 만일 간선의 가중치에 음수를 가했으면 답을 출력할 때 다시 -를 붙여주어야 한다.
// MST의 속성을 아주 잘 이용하는 좋은 문제로 볼 수 있다!!!
// MST 탐색한 다음에 출발점부터 bfs 또는 dfs 탐색을 해서 찾아갈 수도 있는데 그건 좀 비효율적으로 보인다!!!
// 제한시간 1초 중 104ms(5,932KB)가 소요되었다.
// 맞은사람 8/304로 상위 2.63%에 rank되었다.

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

int kruskal(int vcnt, int s, int t)
{
	int count = 0, minval = 0;
	int answer;
	sort(g_graph.begin(), g_graph.end()); // 비용에 대해 오름차순
	for (edge& x : g_graph) {
		if (djs_find(x.from) != djs_find(x.to)) {
			djs_union(x.from, x.to);
			count++;
			minval += x.cost;
			if (djs_find(s) == djs_find(t)) { // '출발점 - 도착점' 경로가 만들어지는 간선이 연결됨.
				answer = x.cost;
				break;
			}
		}
		if (count == vcnt - 1) break;
	}
	return answer;
}

int main()
{
	FAST;
	int N, M, s, t;
	cin >> N >> M >> s >> t;
	g_graph.resize(M, { 0, 0, 0 });
	g_parent.resize(N + 1, -1);
	int h1, h2, k;
	for (int i = 0; i < M; i++) {
		cin >> h1 >> h2 >> k;
		g_graph[i] = { h1, h2, -k };
	}
	cout << -kruskal(N, s, t) << "\n";
}