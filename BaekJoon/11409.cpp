// 11409.cpp
// ������ȣ 6
// �� ������ '11408 ������ȣ 5'�� �Ȱ����� �ּҰ��� �ƴ� �ִ밪�� ã�� �����̴�. ������ ������ �Ȱ���.
// �̷� ���� ������ -�� �Է¹޾Ƽ� �ּҰ����� ���� ������, ����� �� �ּҰ��� -�� �ٿ��� ����ϵ��� �Ѵ�.
// ���ѽð� 2�� �� 276ms(9,960KB)�� �ҿ�Ǿ���.
// ������� 183/385�� ���� 47.53%�� rank�Ǿ���.

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
struct vertex {
	int flo, cap, cos; // flow, capacity, cost
	vertex() : flo(0), cap(0), cos(0) {}
	vertex(int f, int ca, int co) : flo(f), cap(ca), cos(co) {}
};

vector<vector<int>> g_graph;
vector<vector<vertex>> g_flow;
vector<int> g_prev;
int g_N, g_S, g_T; // N, source, sink
int g_maxFlow = 0, g_minCost = 0;

// Shortest Path Faster Algorithm
// Edmond-Karp �˰���� �ſ� ����
void SPFA()
{
	vector<bool> checkQ; // queue�� �ִ��� �˻�.���� �ߺ� �湮�� �� �־� �ʿ���
	vector<int> dist; // distance(�ִܰŸ�, �ּҺ��)
	while (true) {
		queue<int> myq;
		g_prev.assign(g_N + 1, -1);
		checkQ.assign(g_N + 1, false);
		dist.assign(g_N + 1, INF);
		myq.push(g_S); checkQ[g_S] = true;
		g_prev[g_S] = g_S;
		dist[g_S] = 0;
		int cur;
		while (!myq.empty()) {
			cur = myq.front();
			myq.pop(); checkQ[cur] = false;
			for (int next : g_graph[cur]) {
				if (g_flow[cur][next].cap - g_flow[cur][next].flo > 0 && // flow & �ִܰŸ� ����
					dist[cur] + g_flow[cur][next].cos < dist[next]) {
					g_prev[next] = cur;
					dist[next] = dist[cur] + g_flow[cur][next].cos;
					if (!checkQ[next]) { myq.push(next); checkQ[next] = true; }
				}
			}
			// source -> sink ��� ã���� �ִܰ�θ� ã�ƾ� �ϱ� ������ ������ �ʰ� ��� Ž��			
		}
		if (g_prev[g_T] == -1) break; // ���̻� sourcce -> sink ��� ����

		int minFlow = INF;
		for (int i = g_T; i != g_S; i = g_prev[i])
			minFlow = min(minFlow, g_flow[g_prev[i]][i].cap - g_flow[g_prev[i]][i].flo);
		for (int i = g_T; i != g_S; i = g_prev[i]) {
			g_flow[g_prev[i]][i].flo += minFlow;
			g_flow[i][g_prev[i]].flo -= minFlow;
			g_minCost += minFlow * g_flow[g_prev[i]][i].cos;
		}
		g_maxFlow += minFlow;
	}
}

int main()
{
	FAST;
	int N, M;
	cin >> N >> M;
	g_S = N + M + 1;
	g_T = g_S + 1;
	g_N = g_T;

	g_graph.resize(g_N + 1);
	g_flow.resize(g_N + 1, vector<vertex>(g_N + 1, { 0, 0, 0 }));
	g_prev.resize(g_N + 1, -1);
	for (int i = 1; i < N + 1; i++) { // source -> ����
		g_flow[g_S][i].cap = 1;
		g_graph[g_S].push_back(i);
		g_graph[i].push_back(g_S);
	}
	for (int i = N + 1; i < N + M + 1; i++) { // job -> sink
		g_flow[i][g_T].cap = 1;
		g_graph[i].push_back(g_T);
		g_graph[g_T].push_back(i);
	}
	int jcnt, job, pay;
	for (int i = 1; i < N + 1; i++) { // ���� -> job
		cin >> jcnt;
		for (int j = 0; j < jcnt; j++) {
			cin >> job >> pay;
			job += N; // adjust job no.
			g_flow[i][job].cap = 1;
			g_flow[i][job].cos = -pay;
			g_flow[job][i].cos = pay;
			g_graph[i].push_back(job);
			g_graph[job].push_back(i);
		}
	}
	SPFA();
	cout << g_maxFlow << "\n";
	cout << -g_minCost << "\n";
}