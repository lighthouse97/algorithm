// 1585.cpp
// ����
// MCMF(Minimum Cost Maximum Flow)
// MCMF, SPFA�� 2�� ���� �ּ�, �ִ밪�� ���Ѵٴ� �� ����� �ٸ� �����鿡 ���� ��������� ���� �����̴�.
// src -> in, out -> sink, in -> out �̷��� ��Ī�Ѵ�.
// src -> in, out -> sink �� capacity = 1, cost = 0,
// in -> out �� capacity = 1, cost�� �������� �־��� ���ǿ� �°� ���� �� ���� �Ѵ�.
// cost�� ��ȣ�� �ٲٰ� flow 0���� �ʱ�ȭ ���� SPFA�� �ι� �����ָ� �ȴ�. 
// ���ѽð� 2�� �� 4ms(2,160KB)�� �ҿ�Ǿ���.
// ������� 37/137�� ���� 27.00%�� rank�Ǿ���.

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

const int INF = 987654321;

struct edge {
	int to, flow, capa, cost, revi; // to ����, flow, capacity, cost, reverse index(to ���� from�� index)
	edge() : to(-1), flow(0), capa(0), cost(0), revi(-1) {}
	edge(int t, int f, int c, int co, int r) : to(t), flow(f), capa(c), cost(co), revi(r) {}
	bool space() { return capa > flow; }
};

vector<vector<edge>> g_graph;
int g_N, g_S, g_T; // N, source, sink
int g_maxFlow = 0, g_minCost = 0;

void addEdge(int from, int to, int flow, int capa, int cost)
{
	g_graph[from].push_back({ to, flow, capa, cost, (int)g_graph[to].size() }); // ������
	g_graph[to].push_back({ from, 0, 0, -cost, (int)g_graph[from].size() - 1 }); // ������
}

// Shortest Path Faster Algorithm
// Edmond-Karp �˰���� �ſ� ����
void SPFA()
{
	struct vt {
		int name, index;
		vt(int n, int i) : name(n), index(i) {} // ����, ���������� �ε���
	}; // local struct
	vector<bool> checkQ; // queue�� �ִ��� �˻�.���� �ߺ� �湮�� �� �־� �ʿ���
	vector<int> dist; // distance(�ִܰŸ�, �ּҺ��)
	vector<vt> prev;
	while (true) {
		queue<int> myq;
		prev.assign(g_N + 1, { -1, -1 });
		checkQ.assign(g_N + 1, false);
		dist.assign(g_N + 1, INF);
		myq.push(g_S); checkQ[g_S] = true;
		prev[g_S].name = g_S;
		dist[g_S] = 0;
		int cur;
		while (!myq.empty()) {
			cur = myq.front();
			myq.pop(); checkQ[cur] = false;
			for (int i = 0; i < g_graph[cur].size(); i++) {
				edge& next = g_graph[cur][i];
				if (next.space() && dist[cur] + next.cost < dist[next.to]) { // flow & �ִܰŸ� ����
					prev[next.to].name = cur; // ���� ���� ����
					prev[next.to].index = i; // ���� ���������� �ε��� ����
					dist[next.to] = dist[cur] + next.cost;
					if (!checkQ[next.to]) { myq.push(next.to); checkQ[next.to] = true; }
				}
			}
			// source -> sink ��� ã���� �ִܰ�θ� ã�ƾ� �ϱ� ������ ������ �ʰ� ��� Ž��			
		}
		if (prev[g_T].name == -1) break; // ���̻� sourcce -> sink ��� ����

		int minFlow = INF;
		for (int i = g_T; i != g_S; i = prev[i].name) {
			edge& link = g_graph[prev[i].name][prev[i].index];
			minFlow = min(minFlow, link.capa - link.flow);
		}
		for (int i = g_T; i != g_S; i = prev[i].name) {
			edge& link = g_graph[prev[i].name][prev[i].index];
			link.flow += minFlow;
			g_graph[link.to][link.revi].flow -= minFlow;
			g_minCost += minFlow * link.cost;
		}
		g_maxFlow += minFlow;
	}
}

int main()
{
	FAST;
	int N, T, F;
	cin >> N;
	g_S = 2 * N + 1; g_T = g_S + 1; g_N = g_T;
	g_graph.resize(g_N + 1);
	vector<int> in_t(N + 1, 0), out_t(N + 1, 0);
	for (int i = 1; i < N + 1; i++) cin >> in_t[i];
	for (int i = 1; i < N + 1; i++) cin >> out_t[i];
	cin >> T >> F;
	for (int i = 1; i < N + 1; i++)// src -> in
		addEdge(g_S, i, 0, 1, 0);
	for (int i = N + 1; i < 2 * N + 1; i++) // out -> sink
		addEdge(i, g_T, 0, 1, 0);
	for (int i = 1; i < N + 1; i++) { // in -> out
		for (int j = 1; j < N + 1; j++) {
			int cost = 0, dur = out_t[j] - in_t[i];
			if (dur < 1) continue; // '���� �ð� < ������ �ð�' ������ �ִ�.
			cost = (dur < T) ? (T - dur) * (T - dur) : 0;
			cost = min(cost, F); // cost�� F�� ���� �ʴ´�.
			addEdge(i, j + N, 0, 1, -cost); // �ִ밪 ����!
		}
	}
	SPFA(); // get max cost
	int resultMin, resultMax;
	if (g_maxFlow != N) resultMax = -1;
	else resultMax = -g_minCost;

	for (int i = 1; i < g_N + 1; i++) { // Now get min cost
		for (edge& link : g_graph[i]) {
			link.flow = 0; // initialize flow
			if (i < g_S && link.to < g_S) link.cost = -link.cost; // inverse cost
		}
	}
	g_maxFlow = g_minCost = 0;
	SPFA();
	if (g_maxFlow != N) resultMin = -1;
	else resultMin = g_minCost;

	if (resultMin < 0 || resultMax < 0) cout << -1 << "\n";
	else cout << resultMin << " " << resultMax << "\n";
}