// 17412_1.cpp
// 도시 왕복하기 1
// Network Flow, Edmond-Karp algorithm
// 정점사이의 간선이 양방향 또는 여러 개인 경우의 문제들이 있다.
// 이런 경우는 기존 방식의 Edmond-Karp 알고리즘 코드로는 풀기가 애매하기 때문에
// 처음부터 이를 고려한 코드로 다시 구현하였다.
// 즉 g_graph에 간선 정보 및 flow, capacity 모두 다 때려넣고 구헌하였다.
// 이 방식이 기존 단방향 문제도 모두 포함하기 때문에 이 코드를 표준 Edmind-Karp 코드로
// 사용하기로 한다.
// 8ms(2,552KB) 소요되었다.
// 기존 코드 4ms(3,308KB)에 비해 수행시간은 약간 손해를 보지만 코드 사이즈는 줄어 들었다.
// 이렇게 구현을 통일시켜서 소스를 관리하도록 한다.(약간의 수행시간 손해는 보지만 크게 개의치 않겠다!)

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

struct edge {
	int to, flow, capa, revi;
	edge() : to(-1), flow(0), capa(0), revi(-1) {}
	edge(int t, int f, int c, int r) : to(t), flow(f), capa(c), revi(r) {}
	bool space() { return capa > flow; }
};

vector<vector<edge>> g_graph;
int g_N, g_S, g_T; // source, sink, n count
int g_maxFlow = 0;

void addEdge(int from, int to, int flow, int capa)
{
	g_graph[from].push_back({ to, flow, capa, (int)g_graph[to].size() });
	g_graph[to].push_back({ from, 0, 0, (int)g_graph[from].size() - 1 });
}

void edmond_karp()
{
	struct vt {
		int num, index;
		vt(int n, int i) : num(n), index(i) {}
	};
	vector<vt> prev;
	while (true) {
		prev.assign(g_N + 1, { -1, -1 }); // 시작하기 전에 prev를 모두 -1로 초기화시킨다.
		queue<int> myq;
		myq.push(g_S); // source -> queue
		prev[g_S].num = g_S;
		int cur;
		while (!myq.empty()) {
			cur = myq.front();
			myq.pop();
			for (int i = 0; i < g_graph[cur].size(); i++) {
				edge& next = g_graph[cur][i];
				if (prev[next.to].num == -1 && next.space()) { // 이전에 방문하지 않아야 하고, 더 흘릴 flow가 있을 경우, 다음 정점으로 진행.
					prev[next.to].num = cur;
					prev[next.to].index = i;
					myq.push(next.to);
				}
			}
			if (prev[g_T].num != -1) break; // source -> sink까지 경로 찾았음!
		}
		if (prev[g_T].num == -1) break; // source -> sink 까지 흐름이 없을 경우 flow를 다 찾은 경우이므로 더 찾을 필요 없다.

		int minFlow = MAXVAL;
		for (int i = g_T; i != g_S; i = prev[i].num) { // 잔여(residual)유량이 가장 작은 것으로만 통과 가능하다
			edge& link = g_graph[prev[i].num][prev[i].index];
			minFlow = min(minFlow, link.capa - link.flow);
		}
		for (int i = g_T; i != g_S; i = prev[i].num) {
			edge& link = g_graph[prev[i].num][prev[i].index];
			link.flow += minFlow; // 정방향은 flow 더해주고
			g_graph[link.to][link.revi].flow -= minFlow; // 역방향은 flow 빼준다
		}
		g_maxFlow += minFlow;
	}
}

int main()
{
	int N, P;
	cin >> N >> P;
	g_S = 1; g_T = 2; g_N = N;
	g_graph.resize(g_N + 1);
	int a, b;
	for (int i = 1; i < P + 1; i++) {
		cin >> a >> b;
		addEdge(a, b, 0, 1);
	}
	edmond_karp();
	cout << g_maxFlow << "\n";
}