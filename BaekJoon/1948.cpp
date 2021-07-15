// 1948.cpp
// 임계경로
// 앞의 '1516 게임 개발'과 유사한 문제이다.(거의 같은 계열...)
// 각 정점에서 가장 긴 시간에 해당 되는 간선의 수를 구하는 것이 추가가 되는데, 이것은 dfs로 탐색하면서 찾아야 한다.
// dfs탐색 구현을 못했다. 결국 컨닝하고 풀었다!!! 씁슬하다!!!
// 제한시간 2초 중 32ms(5,164KB)가 소요되었다.
// 맞은사람 252/1246로 상위 20.22%에 rank되었다.

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

struct edge {
	int to, time;
	edge() : to(0), time(0) {}
	edge(int a, int b) : to(a), time(b) {}
};

vector<vector<edge>> g_graph;
vector<int> g_degree;
int g_N = 0;
///
vector<int> g_answer;

void topological_sort()
{
	queue<int> myq;
	for (int i = 1; i < g_N + 1; i++)
		if (g_degree[i] == 0) { myq.push(i); g_answer[i] = 0; }
	int cur;
	while (!myq.empty()) {
		cur = myq.front(); myq.pop();
		for (edge& to : g_graph[cur]) {
			g_degree[to.to]--;
			g_answer[to.to] = max(g_answer[to.to], g_answer[cur] + to.time);
			if (g_degree[to.to] == 0)
				myq.push(to.to);
		}
	}
}

int sum_ = 0;
vector<int> visit_;
vector<vector<edge>> igraph_;
void count_road(int cur)
{
	bool ret = true;
	visit_[cur] = 1;
	for (edge& next : igraph_[cur]) {
		if (g_answer[cur] - next.time == g_answer[next.to]) {
			sum_++;
			if (!visit_[next.to]) count_road(next.to);
		}
	}
}

int main()
{
	FAST;
	int n, m;
	cin >> n >> m;
	g_N = n;
	g_graph.resize(n + 1);
	igraph_.resize(n + 1);
	g_degree.resize(n + 1, 0);
	int from, to, time;
	g_answer.resize(n + 1, 0);
	for (int i = 0; i < m; i++) {
		cin >> from >> to >> time;
		g_graph[from].push_back({ to, time });
		igraph_[to].push_back({ from, time });
		g_degree[to]++;
	}
	int start, end;
	cin >> start >> end;
	topological_sort();
	visit_.resize(n + 1, 0);
	count_road(end);
	cout << g_answer[end] << "\n";
	cout << sum_ << "\n";
}