// 2316_e.cpp
// 도시 왕복하기 2
// 앞의 2316에서 g_graph와 g_flow를 하나로 합치고 edge라는 구조체에 필요한 정보를 다 몰아넣아서 소스를
// 좀 더 최적화 시켰다.
// 최적화 시켰으나 12ms로 시간이 더 걸렸다.
// 기존 8ms -> 최적화 후 12ms
// 주어진 데이터의 간선, 정점의 갯수가 일정 규모 이상이 되어야 edge구조체로 최적화시킨게 더 빠른 것 같다.

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

struct edge {
	int to;
	int capacity;
	int rev; // 상대편(to)에서 나(from)가 몇번째 vector 원소인지에 대한 index정보이다.
	int flow;
	edge(int t, int c, int r) : to(t), capacity(c), rev(r), flow(0) {}
};

struct pre {
	int v; // 자신의 previous 정점
	int index; // 자신의 previous 정점에서 자신의 index. // vector 구현이라 구현상 필요하다.
	pre(int v, int i) : v(v), index(i) {}
};

vector<vector<edge>> g_graph;
vector<pre> g_prev;
int g_S = 0, g_T = 0, g_N = 0; // start, sink(terminal), number of vertex
int g_maxFlow = 0; // 최대 유량
const int g_INF = 987654321;

void edmond_karp()
{
	int current;	
	queue<int> myq;
	while (true) {
		fill(g_prev.begin(), g_prev.end(), pre(-1, -1));
		myq.push(g_S);
		while (!myq.empty() && g_prev[g_T].v == -1) {
			current = myq.front();
			myq.pop();
			for (int i = 0; i < (int)g_graph[current].size(); i++) {
				edge next = g_graph[current][i];
				if (g_prev[next.to].v != -1) continue; // 이게 현재 탐색에서 이미 갔던 곳으로 가는 것을 막아주는 역할을 한다.
															 // 다음 번 탐색에서는 다시 초기화 된다.
				if (next.capacity - next.flow > 0) { // 더 흘릴 수 있는 flow가 남은 간선을 찾는다.
					g_prev[next.to].v = current;
					g_prev[next.to].index = i;
					myq.push(next.to);
				}
			}
		}
		while (!myq.empty()) myq.pop(); // clear the queue
		// flow update!
		if (g_prev[g_T].v == -1) break; // '출발 -> 목적지'까지 모든 경로 탐색하고 더 탐색할 필요 없을 경우이다!		
		for (int i = g_T; i != g_S; i = g_prev[i].v) { // sink -> source까지 역으로 거슬러 온다.
			edge& e = g_graph[g_prev[i].v][g_prev[i].index];
			e.flow += 1;
			g_graph[e.to][e.rev].flow -= 1; // // 알고리즘 특성 상 역방향 flow 고려			
		}		
		g_maxFlow += 1;
	}
}

int main()
{
	FAST;

	int n, p;
	cin >> n >> p;
	g_N = 2 * n;
	g_graph.resize(2 * n + 1);
	g_prev.resize(2 * n + 1, { -1, -1 });
	
	// 정점 v -> v'의 방향성 간선을 만든다.(v(2*i-1) -> v'(2*i))
	for (int i = 1; i < n + 1; i++) {	
		g_graph[2 * i - 1].push_back(edge(2 * i, 1, g_graph[2 * i].size()));
		g_graph[2 * i].push_back(edge(2 * i - 1, 0, g_graph[2 * i - 1].size() - 1)); // V -> V'에서 flow는 단뱡향이라도 그래프 진행자체는 양방향이 맞다. 이 정점을 통해 다른 정점으로 갈 수 있어야 한다.
	}
	g_S = 1 * 2;
	g_T = 2 * 2 - 1;
	int from, to;
	for (int i = 0; i < p; i++) {
		cin >> from >> to;						
		g_graph[2 * from].push_back(edge(2 * to - 1, 1, g_graph[2 * to - 1].size())); // 간선 중복방문이 안되기 때문에 간선의 capacity는 1로 둔다
		g_graph[2 * to - 1].push_back(edge(2 * from, 0, g_graph[2 * from].size() - 1)); // 역방향 flow
		g_graph[2 * to].push_back(edge(2 * from - 1, 1, g_graph[2 * from - 1].size())); 
		g_graph[2 * from - 1].push_back(edge(2 * to, 0, g_graph[2 * to].size() - 1)); // 역벙향 flow
	}
	edmond_karp(); // edmonds-karp algorithm
	cout << g_maxFlow << "\n";
}