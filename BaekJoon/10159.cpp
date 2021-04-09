// 10159.cpp
// 저울
// Olympiad > 한국정보올림피아드 > 한국정보올림피아드시․도지역본선 > 지역본선 2014 > 고등부 2번
// Olympiad > 한국정보올림피아드 > 한국정보올림피아드시․도지역본선 > 지역본선 2014 > 중등부 3번
// Olympiad > 한국정보올림피아드 > 한국정보올림피아드시․도지역본선 > 지역본선 2014 > 초등부 4번
// 앞의 2458과 같다. 한가지 차이점은 모든 정점에 대해서 순서를 알 수 없는 정점의 갯수를 출력해 준다는 점이 다른다.
// 제한시간 1초 중 0ms(2,152KB)가 소요되었다.
// 맞은사람 1312/2360로 상위 55.59%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
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

int g_N;
vector<vector<int>> g_graph;
vector<vector<int>> g_igraph; // 역방향 그래프
vector<bool> g_visit;
int g_cnt, g_icnt;

void dfs(int r)
{
	g_visit[r] = true;
	g_cnt++;
	for (int x : g_graph[r]) {
		if (!g_visit[x]) dfs(x);
	}
}

void idfs(int r) // 역방향으로 탐색
{
	g_visit[r] = true;
	g_icnt++;
	for (int x : g_igraph[r]) {
		if (!g_visit[x]) idfs(x);
	}
}

int main()
{
	FAST;
	int m;
	cin >> g_N >> m;
	g_graph.resize(g_N + 1);
	g_igraph.resize(g_N + 1);
	g_visit.resize(g_N + 1, 0);
	int a, b;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		g_graph[a].push_back(b);
		g_igraph[b].push_back(a);
	}
	for (int i = 1; i < g_N + 1; i++) {
		g_cnt = g_icnt = 0;
		g_visit = vector<bool>(g_N + 1, false);
		dfs(i);
		g_visit = vector<bool>(g_N + 1, false);
		idfs(i);
		cout << (g_N - g_cnt - g_icnt + 1) << "\n";
	}
}