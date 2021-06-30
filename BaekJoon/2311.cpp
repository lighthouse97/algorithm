// 2311.cpp
// �պ� ����
// MCMF(Minimum Cost Maximum Flow) �����ε�, �պ��̶� SPFA(Shortest Path Faster Algorithm)�� 2�� ���� �Ѵ�.
// ��, ó�� 1 -> N���� ���ٰ� �ٽ� N -> 1�� �� �� ������/�������� �뷮 �� ������ �ڹٲ��� �Ѵ�.
// -> �̷��� Ǯ�� Ʋ����!!! ó���� ������ �ִ� ��ηθ� ���� ���߿� N���� 1�� �� ���� ��찡
//    �߻��Ѵ�.
// -> ���� ������ ���ݸ� �� �ϸ�(���� �� ������ ���ߴ�!!!) ������̶� 1 -> N���� �ִ� ��η� �ι� �� �� ������ �ȴ�!
//    �׷��� source - 1, N - sink�� �߰� �����ϰ� �� ������ �뷮�� 2�� �ϰ� �������� �뷮�� 1�� �Ѵ�.
//    �׸��� �ִ� ������ ���ϸ� �ȴ�.
// -> �׷��� �̷��Ը� �ص� �� WA��!!
//    ������ ������ a - b ��ΰ� ������̶� a -> b, b -> a ��� ������ ������ ������ �Ѵ�.(������ ���� ������ ������ ���� ����!!!)
//    ����� ������� ����ؼ� ������ �� �ٲپ�� �Ѵ�.
// ���ѽð� 2�� �� 0ms(2,692KB)�� �ҿ�Ǿ���.
// ������� 40/212�� ���� 18.86%�� rank�Ǿ���.

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

const int INF = 1999999999;

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
		for (int i = g_T; i != g_S; i = prev[i].name)
			minFlow = min(minFlow, g_graph[prev[i].name][prev[i].index].capa - g_graph[prev[i].name][prev[i].index].flow);
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
	int N, M;
	cin >> N >> M;
	g_S = N + 1;
	g_T = g_S + 1;
	g_N = g_T;
	g_graph.resize(g_N + 1, {});

	addEdge(g_S, 1, 0, 2, 0); // source -> 1
	addEdge(N, g_T, 0, 2, 0); // N -> g_T	
	int a, b, c;
	for (int i = 0; i < M; i++) { // ���� - ����
		cin >> a >> b >> c;
		addEdge(a, b, 0, 1, c); // a -> b
		addEdge(b, a, 0, 1, c); // b -> a , �����ó��
	}
	SPFA();
	cout << g_minCost << "\n";
}