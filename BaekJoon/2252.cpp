// 2252.cpp
// 줄 세우기
// 위상 정렬(topological sort)을 이용하는 문제이다.
// 인터넷에서 위상 정렬 정리된 자료 찾아보고 공부해서 적용하였다.
// queue를 이용하는 방법과 dfs를 이용하는 방법이 있는데
// queue를 이용하는 방법을 사용하였다.
// 제한시간 2초 중 28ms(3904KB)가 소요되었다.
// 맞은사람 24/4132로 상위 0.58%에 rank되었다.

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
#include <queue> // queue, priority_queue

using namespace std;

int g_N, g_M;
vector<vector<int>> g_graph;
vector<int> g_degree;

void topological_sort()
{
	queue<int> myq;
	int pick;
	for (int i = 1; i <= g_N; i++) {
		if (g_degree[i] == 0)
			myq.push(i);
	}
	while (!myq.empty()) {
		pick = myq.front();
		myq.pop();
		cout << pick << " ";
		for (int x : g_graph[pick]) {
			g_degree[x]--;
			if (g_degree[x] == 0)
				myq.push(x);
		}
	}
	cout << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int a, b;
	cin >> g_N >> g_M;
	g_graph.resize(g_N + 1);
	g_degree.resize(g_N + 1, 0);
	for (int i = 0; i < g_M; i++) {
		cin >> a >> b;
		g_graph[a].push_back(b);
		g_degree[b]++;
	}
	topological_sort();
}
