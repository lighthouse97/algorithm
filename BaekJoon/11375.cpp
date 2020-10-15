// 11375.cpp
// 열혈강호
// 전형적인 이분매칭 문제이다.
// 문제만 딱 봐도 이건 이분 매칭 문제인줄 파악해야 한다.
// 제한시간 2초 중 316ms(6,096KB)가 소요되었다.
// 맞은사람 455/1710로 상위 26.60%에 rank되었다.
// dfs 함수에서 구조를 약간 바꾸니 전체 수행시간이 316ms -> 80ms로 약 4배나 빨라졌다.
// 이에 맞은사람 21/1711로 상위 1.22%에 rank되었다.

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
int g_count = 0;

// original method
/*
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
*/

// 이분매칭에서 동일한 dfs 알고리즘이지만 아래의 방식으로하면 수행시간이 약4배나 빨라진다!
// original이 더 직관적이고 이해하기 쉽지만 아래 방법이 dfs() 함수 호출 횟수를 더 많이 줄여준다! 
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

	int n, m;
	cin >> n >> m;
	g_graph.resize(n + 1);
	g_visited.resize(m + 1, false);
	g_matched.resize(m + 1, 0);

	int cnt, job;
	for (int i = 1; i < n + 1; i++) {
		cin >> cnt;
		for (int j = 0; j < cnt; j++) {
			cin >> job;
			g_graph[i].push_back(job);
		}
	}

	for (int i = 1; i < n + 1; i++) {
		g_visited = vector<bool>(m + 1, false);
		if (dfs(i)) g_count++;
	}
	cout << g_count << "\n";
}