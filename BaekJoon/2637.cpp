// 2637.cpp
// 장난감 조립
// Olympiad > 한국정보올림피아드 > KOI 2000 > 중등부 1번
// 위상 정렬인데 '1516 게임 개발'과 유사 그러나 약간의 응용이 필요하다.
// 제한시간 1초 중 0ms(2,160KB)가 소요되었다.
// 맞은사람 584/780로 상위 74.87%에 rank되었다.

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

struct edge {
	int to, quantity;
	edge() : to(), quantity() {}
	edge(int t, int q) : to(t), quantity(q) {}
};

vector<vector<edge>> g_graph;
vector<int> g_degree;
int g_N = 0;
///
vector<vector<int>> g_parts;

void topological_sort()
{
	queue<int> myq;
	for (int i = 1; i < g_N + 1; i++)
		if (g_degree[i] == 0) {
			myq.push(i); g_parts[i][i] = 1;
		}
	int cur;
	while (!myq.empty()) {
		cur = myq.front(); myq.pop();
		for (edge& next : g_graph[cur]) {
			for (int i = 1; i < g_N + 1; i++) { // 푸품수 누적 반영
				if (g_parts[cur][i])
					g_parts[next.to][i] += (g_parts[cur][i] * next.quantity);
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
	g_graph.resize(N + 1);
	g_degree.resize(N + 1, 0);
	g_parts.resize(N + 1, vector<int>(N + 1, 0));
	g_N = N;
	int x, y, k;
	for (int i = 0; i < M; i++) {
		cin >> x >> y >> k;
		g_graph[y].push_back({ x, k });
		g_degree[x]++;
	}
	topological_sort();
	for (int i = 1; i < N + 1; i++)
		if (g_parts[N][i]) cout << i << " " << g_parts[N][i] << "\n";
}