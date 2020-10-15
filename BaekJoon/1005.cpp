// 1005.cpp
// ACM Craft
// 위상 정렬을 응용하는 문제이다.
// 이런 문제는 아이디어를 재빨리 도출해야 하는데 문제 이해하고 아이디어 도출하는데 시간이 두어시간 걸렸다.
// 위상 정렬로 순서 잡으면서 각 지점에 누적 시간을 저장하다가 특정 지점에 누적시간이
// 여러개면 그 중 큰 값 하나만 적용한다.
// 위상 정렬이 끝나고 목표 지점의 누적 시간만 출력하면 된다! -> 구질구질하게 할 거 없이 이렇게 하면 심플하다!!!
// 그런데, 반드시 1번부터 시작해야 한다는 규칙은 어디에도 없다! 예제보고 햇갈렸는데,
// 이 점도 고려해야 한다. 이점 고려하지 않아서 한번 틀렸다!!!
// 제한시간 1초 중 160ms(2792KB)가 소요되었다.
// 맞은사람 99/3401로 상위 2.91%에 rank되었다.

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
#include <queue> // queue, priority_queue

using namespace std;

int g_N, g_goal;
vector<vector<int>> g_graph;
vector<int> g_degree;
vector<vector<int>> g_cost;

int topological_sort()
{
	queue<int> myq;
	int pick;
	for (int i = 1; i <= g_N; i++) {
		if (g_degree[i] == 0) {
			g_cost[i][1] = g_cost[i][0];
			myq.push(i);
		}
	}
	while (!myq.empty()) {
		pick = myq.front();
		myq.pop();
		if (pick == g_goal) break;
		for (int x : g_graph[pick]) {
			g_cost[x][1] = max(g_cost[x][1], g_cost[pick][1] + g_cost[x][0]);
			g_degree[x]--;
			if (g_degree[x] == 0)
				myq.push(x);
		}
	}
	return g_cost[g_goal][1];
}

void do_test()
{
	int K, x, y, result;
	cin >> g_N >> K;
	g_graph.resize(g_N + 1);
	g_degree.resize(g_N + 1, 0);
	g_cost.resize(g_N + 1, vector<int>(2, 0));
	// cost 입력
	for (int i = 1; i <= g_N; i++) 
		cin >> g_cost[i][0];
	// 규칙 입력
	for (int i = 1; i <= K; i++) {
		cin >> x >> y;
		g_graph[x].push_back(y);
		g_degree[y]++;
	}
	// 목표 unit 입력
	cin >> g_goal;
	result = topological_sort();
	cout << result << "\n";
	
	g_graph.clear();
	g_degree.clear();
	g_cost.clear();
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
		do_test();
}