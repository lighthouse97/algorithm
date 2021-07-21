// 2611.cpp
// 자동차 경주
// Olympiad > 한국정보올림피아드 > 한국정보올림피아드시․도지역본선 > 지역본선 2004 > 중등부 4번
// 위상 정렬 문제. 마지막 출발점 1로 돌이오는 간선을 N + 1 정점에 연결시키고 위상 정렬로 푼다.
// 경로를 출력해야 하기 때문에 최대값 저장하는 배열에 점수와 이전 정점의 정보도 같이 저장한다.
// 제한시간 1초 중 120ms(7,424KB)가 소요되었다.
// 맞은사람 8/243로 상위 3.29%에 rank되었다.

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
#include <stack>
//#include <set>
#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct edge {
	int to, score;
	edge() : to(), score() {}
	edge(int t, int s) : to(t), score(s) {}
};
vector<vector<edge>> g_graph;
vector<int> g_degree;
int g_N = 0;
///
vector<vector<int>> g_score;

void topological_sort()
{
	queue<int> myq;
	for (int i = 1; i < g_N + 1; i++)
		if (g_degree[i] == 0) myq.push(i);
	int cur;
	while (!myq.empty()) {
		cur = myq.front(); myq.pop();
		for (edge& next : g_graph[cur]) {
			if (g_score[cur][0] + next.score > g_score[next.to][0]) {
				g_score[next.to][0] = g_score[cur][0] + next.score; // store max score
				g_score[next.to][1] = cur; // save previous vertex makes max score
			}
			g_degree[next.to]--;
			if (g_degree[next.to] == 0) myq.push(next.to);
		}
	}
}

int main()
{
	FAST;
	int N, M;
	cin >> N >> M;
	g_N = N + 1;
	g_graph.resize(g_N + 1);
	g_degree.resize(g_N + 1, 0);
	g_score.resize(g_N + 1, vector<int>(2, 0)); // 0 : score, 1 : previous
	int p, q, r;
	for (int i = 0; i < M; i++) {
		cin >> p >> q >> r;
		if (q == 1) q = g_N;
		g_graph[p].push_back({ q, r });
		g_degree[q]++;
	}
	topological_sort();
	cout << g_score[g_N][0] << "\n";
	stack<int> myst;
	for (int i = g_N; i != 0; i = g_score[i][1]) myst.push(i);
	while (!myst.empty()) {
		int cur = myst.top(); myst.pop();
		cout << (cur == g_N ? 1 : cur) << " ";
	}
	cout << "\n";
}