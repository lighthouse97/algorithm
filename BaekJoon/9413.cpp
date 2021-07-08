// 9413.cpp
// ���ֵ� ����
// ICPC > Regionals > Asia Pacific > Thailand > Asia Thailand National Programming Contest > 2010 ACM-ICPC Thailand National Programming Contest F��
// MCMF(Minimum Cost Maximum Flow) �����̴�.
// 1) ���� �и�(�ҽ�, ��ũ ����)
// 2) �ҽ� -> ��� ����, ��ũ -> ��� ���� ����, ��� ���� ���� ����
// 3) �ҽ� -> �ҽ�' : capacity = 2, ��� = 0 (�ݵ�� ��� 2���� ���;� �ؼ� cap = 2)
// 4) ��ũ -> ��ũ' : capacity = 2, ��� = 0 (�ݵ�� ��� 2���� ���;� �ؼ� cap = 2)
// 5) i��° ���� -> i��° ����' : capacity = 1, ��� = -1 (�ߺ��湮�� �ƴ϶� cap = 1, �ִ밪�� ���ؼ� ������ ��� ����)
// 6) �ҽ�' -> ��� ���� : capacity = INF, ��� = 0
// 7) ��� ����' -> ��ũ : capacity = INF, ��� = 0
// 8) ��� ����' -> ��� ���� : capacity = INF, ��� = 0
// �̷��� �׷��� �𵨸��Ѵ�.
// ���ѽð� 1�� �� 8ms(2,540KB)�� �ҿ�Ǿ���.
// ������� 33/116�� ���� 28.44%�� rank�Ǿ���.

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
#include <string> // string, stoi
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

void doTest()
{
	int N, M;
	cin >> N >> M;
	g_S = 2 * N + 1; g_T = g_S + 1 + 2; g_N = g_T;
	g_graph.assign(g_N + 1, {});
	for (int i = 1; i < N + 1; i++) addEdge(i, i + N, 0, 1, -1); // 1 ~ N �����и�
	addEdge(g_S, g_S + 1, 0, 2, 0); // �ҽ� ���� �и�
	addEdge(g_T - 1, g_T, 0, 2, 0); // sink ���� �и�
	int from, to;
	for (int i = 0; i < M; i++) {
		cin >> from >> to;
		addEdge(from + N, to, 0, INF, 0); // �����鳢�� ����
	}
	for (int i = 1; i < N + 1; i++) // src -> �����鳢�� ����
		addEdge(g_S + 1, i, 0, INF, 0);
	for (int i = 1; i < N + 1; i++) // ������ -> sink ���� ����
		addEdge(i + N, g_T - 1, 0, INF, 0);
	g_maxFlow = g_minCost = 0;
	SPFA();
	cout << -g_minCost << "\n";
}

int main()
{
	FAST;
	int T;
	cin >> T;
	while (T--) doTest();
}