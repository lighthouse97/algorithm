// 1738.cpp
// 골목길
// 벨만 포드 알고리즘 문제인데, 1219(오민식의 고민) 문제와 같이 최소값이 아닌 최대값을 찾는 문제이다.
// N번째 마지막 정점에서의 최대값을 구하는 게 아니라 최대값이 있을 때의 경로를 구하는 점이 다르다.
// 경로를 구하기 위해서는 dist[]배열에 최대값 및 직전 경로까지 같이 저장한다.
// N번째 정점에 도달하지 못하면 -1, cycle이 발생하여 이게 N번째 정점에 영향을 미치면 이 때도 -1을 출력한다.
// 결국 '1219(오민식의 고민)'과 완전 동일한 문제인데, 경로출력하는 것만 다르다!
// 제한시간 2초 중 4ms(2,296KB)가 소요되었다.
// 맞은사람 123/256로 상위 48.04%에 rank되었다.

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
#include <stack>
//#include <set>
#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct path {
	int c, p; // next(or previous) city, traffic price
	path() : c(0), p(0) {}
	path(int c, int p) : c(c), p(p) {}
};

const int INF = 2000000000;
vector<vector<path>> g_graph; // 골목길 그래프
vector<path> g_maxp; // 최대 수입 저장
int g_N, g_M;
vector<int> g_check; // 도착지점이 사이클 영향을 받는지 체크!

void bellman_ford()
{
	int money;
	g_maxp[1] = { 1, 0 };
	for (int i = 1; i < g_N + 1; i++) {
		for (int j = 1; j < g_N + 1; j++) {
			for (path& x : g_graph[j]) {
				money = g_maxp[j].p + x.p; // 현재도시의 이득 - 이동비용 + 다음 도시의 이득
				if (g_maxp[j].p != -INF && money > g_maxp[x.c].p) {
					g_maxp[x.c] = { j, money };
					if (i == g_N) g_check.push_back(x.c); // 사이클 발생 지점 저장. 나중에 추적해 본다!
				}
			}
		}
	}
}

int main()
{
	FAST;
	cin >> g_N >> g_M;
	g_graph.resize(g_N + 1);
	g_maxp.resize(g_N + 1, { 0, -INF });
	g_check.reserve(g_N + 1);
	int u, v, w;
	for (int i = 0; i < g_M; i++) {
		cin >> u >> v >> w;
		g_graph[u].push_back({ v, w });
	}
	bellman_ford(); // bellman ford 알고리즘
	
	int result = g_maxp[g_N].p;
	if (result == -INF) {
		cout << -1 << "\n";
		return 0;
	}
	bool cycle = false; // 여기서 부터 사이클과 도착지점이 연결되어 있는지 판별(bfs로 판별)
	vector<bool> visited(g_N + 1, false);
	queue<int> myq;
	for (int x : g_check) myq.push(x);
	while (!myq.empty()) {
		int cur = myq.front();
		myq.pop();
		visited[cur] = true;
		if (cur == g_N) { cycle = true; break; } // 도착지점(N)이 사이클 관계임.
		for (path& x : g_graph[cur]) {
			if (!visited[x.c]) {
				visited[x.c] = true;
				myq.push(x.c);
			}
		}
	}
	if (cycle) cout << -1 << "\n";
	else { // 목표지점에 cycle이 없을 경우 최적 경로를 출력한다.
		stack<int> chain;
		int cur = g_N;
		while (1) {
			chain.push(cur);
			if (cur == 1) break;
			cur = g_maxp[cur].c; // previous						
		}
		while (!chain.empty()) {
			cout << chain.top() << " ";
			chain.pop();
		}
		cout << "\n";
	}
}