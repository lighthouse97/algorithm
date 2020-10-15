// 1867.cpp
// 돌맹이 제거
// 이 문제는 행 또는 열 방향으로
// 모든 간선을 연결할 수 있는 최소의 정점의 갯수를 구하면 된다.
// "모든 간선을 연결할 수 있는 최소의 정점의 갯수"라는 말에서 부터
// "최소 버텍스 커버"의 갯수를 구하는 문제이고 이는
// 쾨닉의 정리에 의해 이분 그래프에서 최대 매칭 갯수를 구하면 된다.
// 즉 행 -> 열로 이분 그래프를 만들고 여기서 최대 매칭을 구하면 최대 매칭에 해당되는
// 점에서 행 또는 열 방향으로 모든 점들(돌의 위치)를 연결시킬 수 있다.
// 예제 문제에서 최대 매칭에 해당하는 점은 (1,1), (2,2)가 된는데,
// (1, 1)에서 같은 행으로 (1, 3)이 연결되고
// (2, 2)에서 같은 열로 (3, 2)가 연결이 되어 모든 정점이 연결이 된다.
// Olympiad > USA Computing Olympiad > 2005-2006 Season > USACO November 2005 Contest > Gold 1번
// 제한시간 2초 중 0ms(2,120KB)가 소요되었다.
// 맞은사람 317/640로 상위 49.53%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs, hypot, round
#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_graph;
vector<bool> g_visited;
vector<int> g_matched;

bool dfs(int from)
{
	for (int to : g_graph[from]) {
		if (!g_visited[to] && !g_matched[to]) {
			g_visited[to] = true;
			g_matched[to] = from;
			return true;
		}
	}
	for (int to : g_graph[from]) {
		if (!g_visited[to]) {
			g_visited[to] = true;
			if (!g_matched[to] || dfs(g_matched[to])) {
				g_matched[to] = from;
				return true;
			}
		}
	}
	return false;
}

int main()
{
	FAST;

	int n, k;
	int answer = 0;

	cin >> n >> k;
	g_graph.resize(n + 1);
	g_visited.resize(n + 1, false);
	g_matched.resize(n + 1, false);

	int a, b;
	for (int i = 0; i < k; i++) {
		cin >> a >> b;
		g_graph[a].push_back(b);
	}
	for (int i = 1; i < n + 1; i++) {
		g_visited = vector<bool>(n + 1, false);
		if (dfs(i)) answer++;
	}
	cout << answer << "\n";
}