// 9470.cpp
// Strahler 순서
// ICPC > Regionals > North America > Greater New York Region > 2013 Greater New York Programming Contest C번
// 한국말로 '하천차수'라고 하고 Strahler가 고안하였다.
// 결국 위상정렬로 풀 수 있는 문제이고,
// '1516 게임 개발'과 유사하게 풀 수 있다.
// 제한시간 2초 중 0ms(2,024KB)가 소요되었다.
// 맞은사람 375/611로 상위 61.37%에 rank되었다.

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
struct order { int order; int cnt; };
vector<order> g_answer;

void topological_sort()
{
	queue<int> myq;
	for (int i = 1; i < g_N + 1; i++)
		if (g_degree[i] == 0) { myq.push(i); g_answer[i] = { 1, 0 }; }
	int cur;
	while (!myq.empty()) {
		cur = myq.front(); myq.pop();
		for (int to : g_graph[cur]) {
			if (g_answer[to].order < g_answer[cur].order) {
				g_answer[to].order = g_answer[cur].order;
				g_answer[to].cnt = 1;
			}
			else if (g_answer[to].order == g_answer[cur].order) g_answer[to].cnt++;
			g_degree[to]--;
			if (g_degree[to] == 0) {
				myq.push(to);
				if (g_answer[to].cnt > 1) g_answer[to].order++;
			}
		}
	}
}

void doTest()
{
	int K, M, P;
	cin >> K >> M >> P;
	g_graph.assign(M + 1, {});
	g_degree.assign(M + 1, 0);
	g_answer.assign(M + 1, { 0, 0 });
	g_N = M;
	int a, b;
	for (int i = 0; i < P; i++) {
		cin >> a >> b;
		g_graph[a].push_back(b);
		g_degree[b]++;
	}
	topological_sort();
	cout << K << " " << g_answer[M].order << "\n";
}

int main()
{
	FAST;
	int T;
	cin >> T;
	while (T--) doTest();
}