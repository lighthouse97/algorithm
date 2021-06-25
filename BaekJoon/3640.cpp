// 3640.cpp
// ����
// ICPC > Regionals > Europe > Northwestern European Regional Contest > NWERC 2012 A��
// MCMF(Minimum Cost Maximum Flow) �����̴�.
// �ҽ��� �����, �������� ��ũ�� �뷮�� 2�� �� �ְ� �������� �뷮 1�� �ؼ� �׷��� �����ϸ� �ȴ�.
// �߰�! �������� ������ �ߺ� �湮�� �� ���� ������ �־����� ������ ���� ������ �ؾ� �Ѵ�!!!
//       (�ᱹ ������ ������ �ƴϴ�!)
// source -> �����, ������ -> sink�� �뷮�� 2�� �Ǿ�� �ϴ� �ͻӸ� �ƴ϶�, ����� - �����', ������ - ������' ������
// �뷮�� 2�� �Ǿ�� �ϴµ� �̰� ���߷ȴ�!!
// ���� �и��� �� i < v + 1�ε�, i < v�� �� �� �ߴ�.
// ���ѽð� 1�� �� 100ms(52,320KB)�� �ҿ�Ǿ���.
// ������� 254/358�� ���� 70.94%�� rank�Ǿ���.

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
	int v, e;
	while (cin >> v) {
		cin >> e;
		g_S = v * 2 + 1;
		g_T = g_S + 1;
		g_N = g_T;
		g_graph.assign(g_N + 1, {});
		g_flow.assign(g_N + 1, vector<vertex>(g_N + 1, { 0, 0, 0 }));
		g_prev.assign(g_N + 1, -1);
		g_maxFlow = g_minCost = 0;

		g_flow[g_S][1].cap = 2; // source -> �����
		g_graph[g_S].push_back(1);
		g_graph[1].push_back(g_S);
		g_flow[v * 2][g_T].cap = 2; // ������ -> sink
		g_graph[v * 2].push_back(g_T);
		g_graph[g_T].push_back(v * 2);
		for (int i = 1; i < v + 1; i++) { // ���� �и�
			int cap = (i == 1 || i == v) ? 2 : 1;
			g_flow[i * 2 - 1][i * 2].cap = cap;
			g_graph[i * 2 - 1].push_back(i * 2);
			g_graph[i * 2].push_back(i * 2 - 1);
		}
		int a, b, c;
		for (int i = 0; i < e; i++) {
			cin >> a >> b >> c;
			g_flow[a * 2][b * 2 - 1].cap = 1;
			g_flow[a * 2][b * 2 - 1].cos = c;
			g_flow[b * 2 - 1][a * 2].cos = -c;
			g_graph[a * 2].push_back(b * 2 - 1);
			g_graph[b * 2 - 1].push_back(a * 2);
		}
		SPFA();
		cout << g_minCost << "\n";
	}
}