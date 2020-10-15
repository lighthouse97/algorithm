// 17412.cpp
// 도시 왕복하기1
// 가장 기본적인 Network Flow문제이다.
// 즉 주어진 그래프에서 출발점에서 목적지까지 maximum flow, 즉 가장 큰 유량을 구하는 문제이다.
// 이 문제를 풀기위한 대표적인 알고리즘들이 있는데,
// 그 중에서 BFS를 활용한 Edmonds-Karp algorithm을 사용하여 구현하였다.이는 Ford-Fulkerson algorithm을 기본으로 BFS로 변형한 것이다.
// 자 함 풀어보자!
// 주의할 점!
// 단방향이라 역방향 간선이나 역방향의 capacity는 없어야 한다.(양방향 문제는 따로 있다. 없어야 0이 된다. 괜히 만들면 틀린다.)
// 알고리즘 특성상 역방향에 대한 flow 값은 항상 존재해야 제대로 값을 찾아갈 수 있다.
// network flow를 잘 이해하지 못한 상태에서 어설프게 문제를 푸니 쓸데없이 시간만 많이 잡아먹었다!!!
// 제한시간 2초 중 4ms(3,308KB)가 소요되었다.
// 맞은사람 60/206로 상위 29.12%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs, hypot, round
#include <vector>
#include <algorithm> // sort, max, min, fill
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
#include <queue> // queue, priority_queue
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct vertex {
	int capacity;
	int flow;
};

vector<vector<vertex>> g_flow; // flow/capacity information
vector<int> g_prev;
int g_S = 0, g_T = 0, g_N = 0; // start, sink(terminal), number of vertex
int g_maxFlow = 0; // 최대 유량

void edmond_karp()
{
	int current;
	int maxval = 10000;
	queue<int> myq;
	while (true) {
		//g_prev = vector<int>(g_prev.size(), -1);
		fill(g_prev.begin(), g_prev.end(), -1);		
		myq.push(g_S);
		while (!myq.empty() && g_prev[g_T] == -1) {
			current = myq.front();
			myq.pop();			
		   for(int next = 1; next < g_N + 1; next++) {				
				if (g_prev[next] != -1) continue; // 이게 현재 탐색에서 이미 갔던 곳으로 가는 것을 막아주는 역할을 한다.
				                                  // 다음 번 탐색에서는 다시 초기화 된다.
				if (g_flow[current][next].capacity - g_flow[current][next].flow > 0) { // 더 흘릴 수 있는 flow가 남은 간선을 찾는다.
					g_prev[next] = current;
					myq.push(next);					
				}
			}
		}
		while (!myq.empty()) myq.pop(); // queue clear
		// flow update!
		if (g_prev[g_T] == -1) break; // '출발 -> 목적지'까지 모든 경로 탐색하고 더 탐색할 필요 없을 경우이다!
		int minFlow = maxval;
		for (int i = g_T; i != g_S; i = g_prev[i]) { // sink -> source까지 역으로 거슬러 온다.
			minFlow = min(minFlow, g_flow[g_prev[i]][i].capacity - g_flow[g_prev[i]][i].flow);
		}
		for (int i = g_T; i != g_S; i = g_prev[i]) {
			g_flow[g_prev[i]][i].flow += minFlow;
			g_flow[i][g_prev[i]].flow -= minFlow; // 알고리즘 특성 상 역방향 flow 고려
		}
		g_maxFlow += minFlow;
	}
}

int main()
{
	FAST;

	int n, p;
	cin >> n >> p;
	g_N = n;
	g_flow.resize(n + 1, vector<vertex>(n + 1, { 0, 0 }));
	g_prev.resize(n + 1, -1);

	g_S = 1;
	g_T = 2;
	int from, to;
	for (int i = 0; i < p; i++) {
		cin >> from >> to;				
		g_flow[from][to].capacity++; // 간선 중복방문이 안되기 때문에 간선의 capacity는 1로 둔다		
	}
	edmond_karp(); // edmonds-karp algorithm
	cout << g_maxFlow << "\n";
}