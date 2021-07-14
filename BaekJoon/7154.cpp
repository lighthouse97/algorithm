// 7154.cpp
// Job Postings
// University > North American Invitational Programming Contest > UCIPC 2013 G��
// MCMF(Minumum Cost Maximum Flow)
// ���� �״�� �׷��� �𵨸��Ͽ� MCMF�� Ǯ�� ���� �ʳ� �ʹ�...
// ���� �״�� �𵨸��ϸ� TLE�� �߻��Ѵ�. ������ ������ �� ��������...
// �ʹ� ���� �����ߴ�. �������� �����ϴ�.
// --->
// �װ� �ƴ϶� ���� ���ظ� ���͸��� �� ���� �𵨸��� �߸���ٰ� �� ����....
// �������� �ð��� ��û ��ƸԾ���!!!
// �л� �Ѹ��� 5���� �Է��ε�, 1���� �Է°� n���� �Է�(���� �켱����)��
// �Ųٷ� �ؼ��ߴ�!!!(m���� �л����� 5���� �ƴ� 1 + n���� �Է��� �о���̴� m*5�� �����ε� m*(1+n)���� �ڵ��Ͽ� �翬��
// TLE�� �߻��ߴ�!!!!!!!!!!!!
// ���� ����������!!!
// ���ѽð� 5�� �� 876ms(2,160KB)�� �ҿ�Ǿ���.
// ������� 27/121�� ���� 22.31%�� rank�Ǿ���.

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
// Edmond-Karp �˰������ �ſ� ����
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
	int table[3][4] = { {4, 3, 2, 1}, {8, 7, 6, 5}, {12, 11, 10, 9} };
	while (true) {
		int n, m;
		cin >> n >> m;
		if (!n && !m) break;
		g_S = n + m + 1; g_T = g_S + 1; g_N = g_T;
		g_graph.assign(g_N + 1, {});
		int p;
		for (int i = 1; i < n + 1; i++) { // �ҽ� -> job
			cin >> p;
			addEdge(g_S, i, 0, p, 0);
		}
		int y, c1, c2, c3, c4;
		for (int i = 1; i < m + 1; i++) { // job -> �л�
			cin >> y >> c1 >> c2 >> c3 >> c4;
			addEdge(c1 + 1, n + i, 0, 1, -table[y - 1][0]);
			addEdge(c2 + 1, n + i, 0, 1, -table[y - 1][1]);
			addEdge(c3 + 1, n + i, 0, 1, -table[y - 1][2]);
			addEdge(c4 + 1, n + i, 0, 1, -table[y - 1][3]);
			addEdge(n + i, g_T, 0, 1, 0); // �л� -> g_T
		}
		g_maxFlow = g_minCost = 0;
		SPFA();
		cout << -g_minCost << "\n";
	}
}