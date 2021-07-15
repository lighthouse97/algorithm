// 2623.cpp
// 음악프로그램
// Olympiad > 한국정보올림피아드 > KOI 2002 > 중등부 1번
// 위상정렬. 아주 쉬운 기본 문제이다. 이것도 못 풀면 ㅂㅅ
// cycle을 찾아내는 게 주 목적이다!!!
// 함 풀어보자!!!
// 제한시간 1초 중 0ms(2,168KB)가 소요되었다.
// 맞은사람 1366/2896로 상위 47.16%에 rank되었다.

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
bool g_cycle = false;

void topological_sort()
{
	queue<int> myq;
	for (int i = 1; i < g_N + 1; i++)
		if (g_degree[i] == 0) myq.push(i);
	int cur;
	while (!myq.empty()) {
		cur = myq.front(); myq.pop();
		g_answer.push_back(cur);
		for (int to : g_graph[cur]) {
			g_degree[to]--;
			if (g_degree[to] == 0)
				myq.push(to);
		}
	}
	if (g_answer.size() != g_N) g_cycle = true; // detect cycle!
}

int main()
{
	FAST;
	int N, M;
	cin >> N >> M;
	g_N = N;
	g_graph.resize(N + 1);
	g_degree.resize(N + 1, 0);
	int cnt;
	for (int i = 0; i < M; i++) {
		cin >> cnt;
		vector<int> temp(cnt, 0);
		for (int j = 0; j < cnt; j++) cin >> temp[j];
		for (int k = 0; k < cnt - 1; k++) {
			g_graph[temp[k]].push_back(temp[k + 1]);
			g_degree[temp[k + 1]]++;
		}
	}
	topological_sort();
	if (g_cycle) cout << 0 << "\n";
	else {
		for (int x : g_answer) cout << x << "\n";
	}
}