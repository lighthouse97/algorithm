// 7577.cpp
// 탐사
// Olympiad > 한국정보올림피아드 > 한국정보올림피아드시․도지역본선 > 지역본선 2013 > 고등부 2번
// Difference Constraints System and Shortest Path를 이용하는 문제이다.
// 즉 Difference Constraints System문제인데 Bellman-Ford를 도구로 이용하는 문제이다.
// 1) 두 지점 x, y에 대해 s(x)는 0에서 x지점까지의 합이고 s(y)는 0에서 y지점까지의 합일 때, Probe[x, y] = w는 
//    s(y) - s(x-1) = w로 표시할 수 있고, 이는 s(y) <= s(x-1) + w AND s(x-1) <= x(y) - w 로 나타낼 수 있다.
// 2) 또 특정 지점 x는 0또는 1이기 때문에, 0 <= s(x) - s(x-1) <= 1 이 되고, 
//    s(x) <= s(x-1) + 1 AND s(x-1) <= s(x) + 0 으로 나타낼 수 있다.
// 3) 출발점은 0번 노드는 사용되기 때문에 노드 갯수 N개일때, N + 1을 출발점으로 잡는다. 도착점은 N이 된다.
// 최단 경로 알고리즘(bellman-ford algorithm)를 통하여 모든 노드에 대해 최단 경로를 구하고, 
// cycle 여부를 확인한 뒤에 cycle이 없으면, s(0)부터 출발하여 s(i)값에 연속으로 변화가 없으면 물체가 없으므로 ‘-’를,
// s(i)값이 증가하면 물체가 있으므로 ‘#’를 표시해 준다. cycle이 발견되면 “NONE”를 출력하면 된다.
// 제한시간 1초 중 0ms(2,148KB)가 소요되었다.
// 맞은사람 140/199로 상위 70.35%에 rank되었다.

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

struct thing {
	int to, sum;
	thing() : to(0), sum(0) {}
	thing(int i, int s) : to(i), sum(s) {}
};

vector<vector<thing>> g_graph;
vector<int> g_count;
const int INF = 987654321;
int g_K, g_N;
int g_start, g_cycle = false;

void bellman_ford()
{
	g_count[g_start] = 0;
	int cost;
	for (int rep = 1; rep <= g_K + 2; rep++) {
		for (int i = 0; i < g_K + 2; i++) {
			for (thing& nex : g_graph[i]) {
				cost = g_count[i] + nex.sum;
				if (g_count[i] != INF && cost < g_count[nex.to]) {
					g_count[nex.to] = cost;
					if (rep == g_K + 2) { g_cycle = true; return; }
				}
			}
		}
	}
}

int main() {
	FAST;
	cin >> g_K >> g_N;
	g_graph.resize(g_K + 2); // 0, 1~g_K, g_K+1
	g_count.resize(g_K + 2, INF);
	g_start = g_K + 1;

	int x, y, r;
	for (int i = 0; i < g_N; i++) { // 조건1) sum[y] - sum[x - 1] = r
		cin >> x >> y >> r;
		g_graph[x - 1].push_back({ y, r });
		g_graph[y].push_back({ x - 1, -r });
	}
	for (int i = 0; i <= g_K; i++) { // 조건2) 0 <= sum[i] - sum[i - 1] <= 1
		if (i > 0) {
			g_graph[i - 1].push_back({ i, 1 });
			g_graph[i].push_back({ i - 1, 0 });
		}
		g_graph[g_start].push_back({ i, 0 }); // start -> each i의 가중치는 0
	}
	bellman_ford();
	if (g_cycle) { cout << "NONE" << "\n"; return 0; }
	else {
		for (int i = 1; i < g_K + 1; i++) {
			if (g_count[i - 1] == g_count[i]) cout << "-";
			else cout << "#";
		}
		cout << "\n";
	}
}