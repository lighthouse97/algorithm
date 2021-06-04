// 18138.cpp
// 리유나는 세일러복을 좋아해
// 그냥 이분매칭(Bipartite Matching) 문제이다. 이분 그래프 구성할 때 문제에서 주어진 조건만 맞춰서 그래프 구성하고,
// 다음에 그냥 이분 매칭을 돌리기만 하면 된다.
// 제한시간 1초 중 0ms(2,160KB)가 소요되었다.
// 맞은사람 118/199로 상위 59.29%에 rank되었다.

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
//#include <algorithm> // sort, max, min, copy, swap, unique
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

vector<vector<int>> g_graph;
vector<bool> g_visited;
vector<int> g_matched;

bool dfs(int from)
{
	for (int to : g_graph[from]) {
		if (g_visited[to]) continue;
		else g_visited[to] = true;
		if (g_matched[to] == 0 || dfs(g_matched[to])) {
			g_matched[to] = from;
			return true;
		}
	}
	return false;
}

bool CanMatched(int w1, int w2)
{
	if ((w1 <= 2 * w2 && 4 * w2 <= 3 * w1) || (w1 <= w2 && 4 * w2 <= 5 * w1)) return true;
	return false;
}

int main()
{
	FAST;
	int N, M;
	cin >> N >> M;
	g_graph.resize(N + 1);
	g_visited.resize(M + 1, false);
	g_matched.resize(M + 1, 0);

	vector<int> shirts(N + 1, 0);
	vector<int> collar(M + 1, 0);
	for (int i = 1; i < N + 1; i++) cin >> shirts[i];
	for (int i = 1; i < M + 1; i++) cin >> collar[i];

	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < M + 1; j++) {
			if (CanMatched(shirts[i], collar[j])) g_graph[i].push_back(j);
		}
	}

	int count = 0;
	for (int i = 1; i < N + 1; i++) {
		g_visited.assign(M + 1, false);
		if (dfs(i)) count++;
	}
	cout << count << "\n";
}