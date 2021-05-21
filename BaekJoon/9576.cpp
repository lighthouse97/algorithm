// 9576.cpp
// 책 나눠주기
// 이것도 일반적인 이분 매칭 문제이다. 약간 차이점은 M 정점의 정보를 가지고 N의 연결정보를 유추해야 한다는 점이다.
// 이것 외에는 특별히 어려운 점은 없다!
// 제한시간 2초 중 348ms(6,128KB)가 소요되었다.
// 맞은사람 960/1425로 상위 67.36%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
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

void doTest()
{
	int N, M;
	cin >> N >> M;
	g_graph.resize(N + 1);
	g_visited.resize(M + 1, false);
	g_matched.resize(M + 1, 0);

	int a, b;
	for (int i = 1; i < M + 1; i++) {
		cin >> a >> b;
		for (int j = a; j < b + 1; j++)
			g_graph[j].push_back(i);
	}

	int answer = 0;
	for (int i = 1; i < N + 1; i++) {
		if (dfs(i)) answer++;
		g_visited = vector<bool>(M + 1, false);
	}
	cout << answer << "\n";
	g_graph.clear();
	g_visited.clear();
	g_matched.clear();
}

int main()
{
	FAST;
	int t;
	cin >> t;
	for (int i = 0; i < t; i++)
		doTest();
}