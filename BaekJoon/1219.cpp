// 1219.cpp
// 오민식의 고민
// 최단 거리 알고리즘 중에서 사이클 유무를 체크할 수 있는 벨만 포드(Bellman-Ford) 알고리즘을 이용하는 문제이다.
// 벨만 포드가 최단 경로 찾을 때 음수 가중치에 대해 사이클 유무를 찾는 것인데... 이 문제는 이를 뒤집어서 생각해야 한다.
// (최장 경로에 양수 가중치에 대해 사이클 유무...)
// 각 정점의 최대값을 저장하는 배열에서 100개의 도시가 100개의 경로로 사이클을 이룰 경우 1000000 * 190 * 100으로
// int의 범위를 벗어날 수 있으므로 long long type으로 배열을 선언해야 한다!!!
// 그런데 bellman-ford문제이기도 하지만 cycle 여부 판단하는 것이 까다롭다!!(이 부분에 함정카드가 숨어있다)
// 함정 1) 일단 cycle이 발생해도 목적지에 도달 할 수 없는 경우면(둘 다 발생한 경우), 무조건 목적지 우선이다. gg로 가야 한다!
// 함정 2) cycle연결고리에 목적지가 있는 경우도 있지만 연결고리 바깥에 연결되어 있는 경우도 있다.
//         이 경우는 cycle에 관여된 모든 정점을 queue에 넣어서 bfs로 연결된 모든 정점을 탐색, 목적지로 가는 지 따져봐야 한다.
//         bfs탐색 구현에서, bfs 탐색전 최초 queue에 들어간 정점이 목적지일수도 있으므로 항상 pop한 current queue부터
//         목적지인가를 따져 봐야 한다.
//			  연결고리에 목적지가 있으면 Gee, 없으면 목적지에서의 이윤이다.
// 제한시간 2초 중 0ms(2,020KB)가 소요되었다.
// 맞은사람 429/699로 상위 61.37%에 rank되었다.

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
#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

typedef long long ll;
struct path {
	int c, p; // next city, traffic price
	path() : c(0), p(0) {}
	path(int c, int p) : c(c), p(p) {}
};

const ll INF = 99999999999;
vector<vector<path>> g_city; // 도시 그래프
vector<ll> g_maxp; // 최대 수입 저장
vector<int> g_profit; // 각 도시에서 얻을 수 있는 수입
int g_N, g_S, g_E, g_M;
vector<int> g_check; // 도착지점이 사이클 영향을 받는지 체크!

void bellman_ford()
{
	ll money;
	g_maxp[g_S] = g_profit[g_S];
	for (int i = 0; i < g_N; i++) {
		for (int j = 0; j < g_N; j++) {
			for (path& x : g_city[j]) {
				money = g_maxp[j] - x.p + g_profit[x.c]; // 현재도시의 이득 - 이동비용 + 다음 도시의 이득
				if (g_maxp[j] != -INF && money > g_maxp[x.c]) {
					g_maxp[x.c] = money;
					if (i == g_N - 1) g_check.push_back(x.c); // 사이클 발생 지점 저장. 나중에 추적해 본다!
				}
			}
		}
	}
}

int main()
{
	FAST;
	cin >> g_N >> g_S >> g_E >> g_M;
	g_city.resize(g_N);
	g_maxp.resize(g_N, -INF);
	g_profit.resize(g_N, 0);
	g_check.reserve(g_N);
	int s, e, p;
	for (int i = 0; i < g_M; i++) {
		cin >> s >> e >> p;
		g_city[s].push_back({ e, p });
	}
	for (int i = 0; i < g_N; i++) cin >> g_profit[i];

	bellman_ford(); // bellman-ford algorithm

	ll result = g_maxp[g_E];

	bool cycle = false; // 여기서 부터 사이클과 도착지점이 연결되어 있는지 판별(bfs로 판별)
	vector<bool> visited(g_N, false);
	queue<int> myq;
	for (int x : g_check) myq.push(x);
	while (!myq.empty()) {
		int cur = myq.front();
		myq.pop();
		visited[cur] = true;
		if (cur == g_E) { cycle = true; break; }
		for (path& x : g_city[cur]) {
			if (!visited[x.c]) {
				visited[x.c] = true;
				myq.push(x.c);
			}
		}
	}

	if (result == -INF) cout << "gg" << "\n";
	else {
		if (cycle) cout << "Gee" << "\n";
		else cout << result << "\n";
	}
}