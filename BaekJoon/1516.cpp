// 1516.cpp
// 게임 개발
// 전형적인 위상정렬 문제이다.
// 바로 풀어보자!!!
// 문제를 제대로 이해하지 못했다. 그리고 반례를 만드는 능력도 아직 많이 부족하다!!!
// 한 정점에 조상이 여럿일 경우 이 한 정점의 소요 시간은 자신의 조상 중 가장 시간이
// 많이 걸리는 조상의 시간과 자신의 시간을 합해야 한다.
// 왜냐하면 바로 위의 여럿 조상이 모두 만들어져야 비로소 자신이 만들어질 수 있기 때문이다.
// 제한시간 2초 중 4ms(2,420KB)가 소요되었다.
// 맞은사람 980/3748로 상위 26.14%에 rank되었다.

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
vector<int> g_time;
vector<int> g_answer;

void topological_sort()
{
	queue<int> myq;
	for (int i = 1; i < g_N + 1; i++)
		if (g_degree[i] == 0) { myq.push(i); g_answer[i] = g_time[i]; }
	int cur;
	while (!myq.empty()) {
		cur = myq.front(); myq.pop();
		for (int to : g_graph[cur]) {
			g_degree[to]--;
			g_answer[to] = max(g_answer[to], g_answer[cur] + g_time[to]);
			if (g_degree[to] == 0)
				myq.push(to);
		}
	}
}

int main() {
	FAST;
	int N;
	cin >> N;
	g_graph.resize(N + 1);
	g_degree.resize(N + 1, 0);
	g_N = N;
	int t, b;
	g_time.resize(g_N + 1, 0);
	g_answer.resize(g_N + 1, 0);
	for (int i = 1; i < g_N + 1; i++) {
		cin >> t;
		g_time[i] = t;
		while (1) {
			cin >> b;
			if (b == -1) break;
			g_graph[b].push_back(i);
			g_degree[i]++;
		}
	}
	topological_sort();
	for (int i = 1; i < g_N + 1; i++)
		cout << g_answer[i] << "\n";
}