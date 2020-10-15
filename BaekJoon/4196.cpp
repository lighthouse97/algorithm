// 4196.cpp
// 도미노
// 직접적인 SCC 문제는 아니고 SCC의 구현 방식을 응용하는 문제이다.
// SCC 구할 때 처럼 dfs 탐색하면서 stack에 넣는 것은 같다.
// 단 역방향 탐색은 하지 않고 stack에 넣을 때 tree의 root가 stack에 마지막으로
// 들어간다. 이 성질을 이용하여 stack의 top부터, 즉 tree의 root를 우선으로
// dfs 탐색하여 dfs가 끝나는 갯수만큼 tree의 갯수가 나오고 이 tree의 갯수가
// 정답이 된다.
// 제한시간 1초 중 128ms(12456KB)가 소요되었다.
// 맞은사람 27/479로 상위 5.63%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <functional> // less, greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_graph;
vector<bool> g_visited;
stack<int> g_st;
int g_cnt = 0;

void dfs(int current, int type)
{
	g_visited[current] = true;
	for (int next : g_graph[current]) {
		if (g_visited[next]) continue;
		dfs(next, type);
	}
	if (!type) g_st.push(current);
}

void do_test()
{
	int n, m, x, y, num;
	cin >> n >> m;
	g_graph.resize(n + 1);
	g_visited.resize(n + 1, false);
	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		g_graph[x].push_back(y);
	}
	for (int i = 1; i <= n; i++) {
		if (!g_visited[i])
			dfs(i, 0);
	}
	g_visited = vector<bool>(n + 1, false);
	while (!g_st.empty()) {
		num = g_st.top();
		g_st.pop();
		if (g_visited[num]) continue;
		dfs(num, 1);
		g_cnt++;
	}
	cout << g_cnt << "\n";
	g_graph.clear();
	g_visited.clear();
	g_cnt = 0;
}

int main()
{
	FAST

	int t;
	cin >> t;
	for (int i = 0; i < t; i++)
		do_test();
}