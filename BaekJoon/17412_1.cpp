// 17412_1.cpp
// 도시 왕복하기 1
// Network Flow, Edmond-Karp algorithm
// Edmond-Karp 알고리즘 적용에 있어서 간선의 방향이 단방향이냐 양방향이냐에 따라서
// 서로 다르게 구현했는데, 
// 어차피 유량의 대칭성을 이용하여 간선의 역방향 탐색은 단방향이나 양방향이나 공통으로 적용이 되므로, 
// g_graph는 양방향으로 공통으로 구현을 하고, 
// g_flow의 역방향의 capacity를 양방향은 c(c > 0)값, 단방향은 0으로 설정한다.
// 이렇게 구현을 통일시켜서 소스를 관리하도록 한다.(약간의 수행시간 손해는 보지만 크게 개의치 않겠다!)
// 제한시간 2초 중 8ms(3,348KB)가 소요되었다.
// 맞은사람 320/496로 상위 64.51%에 rank되었다. 

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

const int MAXVAL = 10000;
struct vertex {
	int flo, cap;
	vertex() : flo(0), cap(0) {}
	vertex(int f, int c) : flo(f), cap(c) {}
};

vector<vector<int>> g_graph;
vector<vector<vertex>> g_flow;
vector<int> g_prev;
int g_N, g_S, g_T; // source, sink, n count
int g_maxFlow = 0;

void edmond_karp()
{
	while (true) {
		g_prev.assign(g_N + 1, -1); // 시작하기 전에 prev를 모두 -1로 초기화시킨다.
		queue<int> myq;
		myq.push(g_S); // source -> queue
		g_prev[g_S] = g_S;
		int cur;
		while (!myq.empty()) {
			cur = myq.front();
			myq.pop();
			for (int next : g_graph[cur]) { // 이전에 방문하지 않아야 하고, 더 흘릴 flow가 있을 경우, 다음 정점으로 진행.
				if (g_prev[next] == -1 && g_flow[cur][next].cap - g_flow[cur][next].flo > 0) {
					g_prev[next] = cur;
					myq.push(next);
				}
			}
			if (g_prev[g_T] != -1) break; // source -> sink까지 경로 찾았음!
		}
		if (g_prev[g_T] == -1) break; // source -> sink 까지 흐름이 없을 경우 flow를 다 찾은 경우이므로 더 찾을 필요 없다.

		int minFlow = MAXVAL;
		for (int i = g_T; i != g_S; i = g_prev[i]) // 잔여(residual)유량이 가장 작은 것으로만 통과 가능하다
			minFlow = min(minFlow, g_flow[g_prev[i]][i].cap - g_flow[g_prev[i]][i].flo);
		for (int i = g_T; i != g_S; i = g_prev[i]) {
			g_flow[g_prev[i]][i].flo += minFlow; // 정방향은 flow 더해주고
			g_flow[i][g_prev[i]].flo -= minFlow; // 역방향은 flow 빼준다
		}
		g_maxFlow += minFlow;
	}
}

int main()
{
	int N, P;
	cin >> N >> P;
	g_N = N;
	g_graph.resize(g_N + 1);
	g_flow.resize(g_N + 1, vector<vertex>(g_N + 1, { 0, 0 }));
	g_prev.resize(g_N + 1, -1);
	int a, b;
	for (int i = 1; i < P + 1; i++) {
		cin >> a >> b;
		g_graph[a].push_back(b);
		g_graph[b].push_back(a);
		g_flow[a][b].cap = 1;
	}
	g_S = 1; g_T = 2;
	edmond_karp();
	cout << g_maxFlow << "\n";
}