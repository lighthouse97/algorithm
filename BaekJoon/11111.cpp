// 11111.cpp
// �κ���� ��ȫ�� 2
// '11495 ���� 0 �����' ������ �����ϴ�.
// ü���� ������ �����ϰ�, ����, �������� ��ġ�� �ʰ� 2���� �׷����� ������. 
// �� ��ĭ�� �� �����ϰ� ������ �׷����� �����Ѵ�.
// �׸��� 2���� �׷찣�� �����¿�� �׷��� �����ϰ�(���� �ҽ�, ��ũ�� �� �׷쿡 ����) �ִ� ������ ���Ѵ�.
// ������ �ִ밪�� ���ϹǷ� ����� -�� �ΰ� �ּ� ����� ���� ������ ����� �ٽ� -�� ���ش�.
// --> �̷��� �ϸ� Ʋ���� �ϳ��� ������!
//     ������ ������ �غ��� 37�� �ȳ����� 36�� ���´�.
// �� ������ ���� �κξ��� ��� �κθ� ¦������ �߶󳻾� �Ѵٴ� ���̴�.
// �̷��� �ϸ� �κ� ����� �ͺ��� ���鿡�� �ּҰ��� ������ ���� ���� �ִ�.
// �� �� ��¥���� ���� ���鿡�� �� �̵��̶� flow�� ����� �ʰ� ��� ä���� �ϱ� ������
// ������ ¦�� �� �������� ���߾� ���鿡���� ���غ��� ������ �� �� �ְ� �ȴ�.
// ���� �׷� B�Ӹ� �ƴ϶� �׷� A��(�� ��� ����) sink�� ������Ѽ�
// �κ� �� �� ���� ��ε� ���� �� �ְ� �� ��� �Ѵ�.
// �̷��� �ؾ� ¦������ ���� ��ο� �Ѱ� ���� ��� �� ���鿡�� ������ ����
// �����ϰ� �� �� �ִ�.
// ���ѽð� 1�� �� 236ms(2,788KB)�� �ҿ�Ǿ���.
// ������� 91/173�� ���� 52.60%�� rank�Ǿ���.

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

int main()
{
	FAST;
	int N, M;
	cin >> N >> M;

	g_S = N * M + 1; g_T = g_S + 1; g_N = g_T;
	g_graph.resize(g_N + 1);
	vector<vector<int>> cost_tbl = // ��� ���̺�
	{ { 0, 0, 0, 0, 0, 0},
		 { 0, 10, 8, 7, 5, 1},
		 { 0, 8, 6, 4 ,3, 1},
		 { 0, 7, 4, 3, 2, 1},
		 { 0, 5, 3 ,2, 2, 1},
		 { 0, 1, 1, 1, 1, 0} };
	vector<vector<int>> tofu_tbl(N + 1, vector<int>(M + 1, 0)); // �κ���
	struct info { int r, c, id; };
	vector<info> aa; vector<info> bb; // �׷� A, �׷� B
	string ss;
	for (int i = 1; i < N + 1; i++) {
		cin >> ss;
		for (int j = 1; j < ss.length() + 1; j++) {
			tofu_tbl[i][j] = (ss[j - 1] != 'F') ? ss[j - 1] - 'A' + 1 : 5;
			if ((i + j) % 2 == 0) aa.push_back({ i, j, (i - 1) * M + j }); // �׷� a �Է�
			else bb.push_back({ i, j, (i - 1) * M + j }); // �׷� b �Է� 			
		}
	}
	for (info& x : aa) {
		addEdge(g_S, x.id, 0, 1, 0); // src -> group a
		addEdge(x.id, g_T, 0, 1, 0); // group a -> sink
	}
	for (info& x : bb)
		addEdge(x.id, g_T, 0, 1, 0); // groub b -> sink
	int dr[4] = { -1, 0, 1, 0 };
	int dc[4] = { 0, -1, 0, 1 };
	for (info x : aa) {
		for (int i = 0; i < 4; i++) {
			int nr = x.r + dr[i];
			int nc = x.c + dc[i];
			if (nr < 1 || nc < 1 || nr > N || nc > M) continue;
			int t1 = tofu_tbl[x.r][x.c];
			int t2 = tofu_tbl[nr][nc];
			addEdge(x.id, (nr - 1) * M + nc, 0, 1, -cost_tbl[t1][t2]);
		}
	}
	SPFA();
	cout << -g_minCost << "\n";
}