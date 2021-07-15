// 14567.cpp
// 선수과목(Prerequisite)
// University > 중앙대학교 > CodeRace 2017 G번
// 이 문제도 '1516 게임 개발' 문제와 아주 유사하다.
// 함 풀어보자!!!
// 제한시간 5초 중 88ms(4,940KB)가 소요되었다.
// 맞은사람 83/545로 상위 15.22%에 rank되었다.

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

vector<vector<int>> g_graph;
vector<int> g_degree;
int g_N = 0;
///
vector<int> g_answer;

void topological_sort()
{
	queue<int> myq;
	for (int i = 1; i < g_N + 1; i++)
		if (g_degree[i] == 0) { myq.push(i); g_answer[i] = 1; }
	int cur;
	while (!myq.empty()) {
		cur = myq.front(); myq.pop();
		for (int to : g_graph[cur]) {
			g_degree[to]--;
			g_answer[to] = max(g_answer[to], g_answer[cur] + 1);
			if (g_degree[to] == 0)
				myq.push(to);
		}
	}
}

int main()
{
	FAST;
	int N, M;
	cin >> N >> M;
	g_graph.resize(N + 1);
	g_degree.resize(N + 1, 0);
	g_N = N;
	g_answer.resize(N + 1, 0);
	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		g_graph[a].push_back(b);
		g_degree[b]++;
	}
	topological_sort();
	for (int i = 1; i < N + 1; i++) cout << g_answer[i] << " ";
	cout << "\n";
}