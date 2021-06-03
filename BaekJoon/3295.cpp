// 3295.cpp
// 단방향 링크 네트워크
// ICPC > Regionals > Asia Pacific > Korea > Nationwide Internet Competition > Daejeon Nationalwide Internet Competition 2013 H번
// 이분 매칭 문제인데, 이분 그래프 구성하기까지 한참 걸렸다.
// 특히 문제 이해가 잘 안되어, 여러번 읽어봤는데, 결국 문제 그대로 정점과 간선 정보로 이분 그래프 만들고,
// 최대 매칭을 구하면 된다. 링이면 정점의 갯수와 간선의 갯수가 같고(k), 선형이면 정점 - 1이 간선의 갯수(k-1)이
// 되어 문제에서 설명하는 것과 같다.
// 특히 정점에 0이 포함되기 때문에, g_matched는 -1로 초기화 시켜야 한다.
// 제한시간 1초 중 44ms(2,432KB)가 소요되었다.
// 맞은사람 27/270로 상위 10.00%에 rank되었다.

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
		if (g_matched[to] == -1 || dfs(g_matched[to])) {
			g_matched[to] = from;
			return true;
		}
	}
	return false;
}

void doTest()
{
	int n, m;
	cin >> n >> m;
	g_graph.resize(n);
	int u, v;
	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		g_graph[u].push_back(v);
	}

	int count = 0;
	g_matched.assign(n, -1);
	for (int i = 0; i < n; i++) {
		g_visited.assign(n, false);
		if (dfs(i)) count++;
	}
	cout << count << "\n";
	g_graph.clear();
}

int main() {
	FAST;
	int T;
	cin >> T;
	for (int i = 0; i < T; i++) doTest();
}