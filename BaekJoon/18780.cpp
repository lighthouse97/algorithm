// 18780.cpp
// Timeline
// Olympiad > USA Computing Olympiad > 2019-2020 Season > USACO 2020 February Contest > Gold 1번
// 이것도 위상 정렬 문제인데, 문제 이해가 관건이다!!!
// 역시 고민했지만, 내 예상이 맞았다!!!
// '각 세션(정점)의 시간'과 '이전 세션의 시간 + 소요 시간' 중 큰 값을 고른다!!! 
// 제한시간 2초 중 96ms(7,528KB)가 소요되었다.
// 맞은사람 53/103로 상위 51.45%에 rank되었다.

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
	int to, days;
	edge() : to(), days() {}
	edge(int t, int d) : to(t), days(d) {}
};
vector<vector<edge>> g_graph;
vector<int> g_degree;
int g_N = 0;
///
vector<int> g_time;

void topological_sort()
{
	queue<int> myq;
	for (int i = 1; i < g_N + 1; i++)
		if (g_degree[i] == 0) myq.push(i);
	int cur;
	while (!myq.empty()) {
		cur = myq.front(); myq.pop();
		for (edge& next : g_graph[cur]) {
			g_time[next.to] = max(g_time[next.to], g_time[cur] + next.days);
			g_degree[next.to]--;
			if (g_degree[next.to] == 0) myq.push(next.to);
		}
	}
}

int main()
{
	FAST;
	int N, M, C;
	cin >> N >> M >> C;
	g_graph.resize(N + 1);
	g_degree.resize(N + 1, 0);
	g_time.resize(N + 1, 0);
	g_N = N;
	for (int i = 1; i < N + 1; i++) cin >> g_time[i];
	int a, b, x;
	for (int i = 0; i < C; i++) {
		cin >> a >> b >> x;
		g_graph[a].push_back({ b, x });
		g_degree[b]++;
	}
	topological_sort();

	for (int i = 1; i < N + 1; i++) cout << g_time[i] << "\n";
}