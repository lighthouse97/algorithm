// 11378.cpp
// ������ȣ 4
// network flow�� �ִ� ������ ���ϴ� �����̴�.
// ������ �ϻ����� ���踦 network flow�� �𵨸��Ѵ�. �׸���
// k��ŭ�� bridge node�� source�� �������̿� ����ȴٴ� ���� �߰��ȴ�
// ���̵� �������� �ʾƼ� �ٸ� ����� Ǭ �� �����Ͽ� Ǯ����!
// ���ѽð� 3�� �� 376ms(38,040KB)�� �ҿ�Ǿ���.
// ������� 233/611�� ���� 38.13%�� rank�Ǿ���.

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
	int capacity;
	int flow;
};

vector<vector<edge>> g_flow; // flow/capacity information
vector<int> g_prev;
vector<vector<int>> g_graph;
int g_S = 0, g_T = 0, g_N = 0; // start, sink(terminal), number of vertex
int g_maxFlow = 0; // �ִ� ����
int g_bridge = 0; // bridge vertex

void edmond_karp()
{
	int current;
	int maxval = 2000;
	queue<int> myq;
	while (true) {
		fill(g_prev.begin(), g_prev.end(), -1);
		myq.push(g_S);
		g_prev[g_S] = g_S; // for speed optimization
		while (!myq.empty() && g_prev[g_T] == -1) {
			current = myq.front();
			myq.pop();
			for (int next : g_graph[current]) {
				if (g_prev[next] != -1) continue; // �̰� ���� Ž������ �̹� ���� ������ ���� ���� �����ִ� ������ �Ѵ�.
															 // ���� �� Ž�������� �ٽ� �ʱ�ȭ �ȴ�.
				if (g_flow[current][next].capacity - g_flow[current][next].flow > 0) { // �� �긱 �� �ִ� flow�� ���� ������ ã�´�.
					g_prev[next] = current;
					myq.push(next);
				}
			}
		}
		while (!myq.empty()) myq.pop(); // clear the queue
		// flow update!
		if (g_prev[g_T] == -1) break; // '��� -> ������'���� ��� ��� Ž���ϰ� �� Ž���� �ʿ� ���� ����̴�!
		int minFlow = maxval;
		for (int i = g_T; i != g_S; i = g_prev[i]) { // sink -> source���� ������ �Ž��� �´�.
			minFlow = min(minFlow, g_flow[g_prev[i]][i].capacity - g_flow[g_prev[i]][i].flow);
		}
		for (int i = g_T; i != g_S; i = g_prev[i]) {
			g_flow[g_prev[i]][i].flow += minFlow;
			g_flow[i][g_prev[i]].flow -= minFlow; // �˰��� Ư�� �� ������ flow ���			
		}
		g_maxFlow += minFlow;
	}
}

int main()
{
	FAST;

	const int maxn = 2010; // 1001 + 1000 + 3 = 2004 < 2010
	int n, m, k;
	cin >> n >> m >> k;
	// ���� : 1 ~ 1000, �� : 1001 ~ 2000, �ҽ� : 2001, ��ũ : 2002, �긴�� : 2003
	// ���� ���Ѵ�.
	g_N = n;
	g_flow.resize(maxn, vector<edge>(maxn, { 0, 0 }));
	g_prev.resize(maxn, -1);
	g_graph.resize(maxn);
	// staff -> job mapping
	int numJob, job;
	for (int i = 1; i < n + 1; i++) {
		cin >> numJob;
		for (int j = 0; j < numJob; j++) {
			cin >> job;
			g_graph[i].push_back(job + 1000);
			g_graph[job + 1000].push_back(i); // ������
			g_flow[i][job + 1000].capacity = 1; // staff->job capacity
		}
	}
	g_S = 2001; g_T = 2002; g_bridge = 2003;
	// source -> bridge mapping
	g_graph[g_S].push_back(g_bridge);
	g_graph[g_bridge].push_back(g_S);
	g_flow[g_S][g_bridge].capacity = k; // 1�� �ƴϰ� k �̴�!
	// source -> staff, bridge -> staff mapping
	for (int i = 1; i < n + 1; i++) {
		g_graph[g_S].push_back(i); // source -> staff
		g_graph[i].push_back(g_S);
		g_graph[g_bridge].push_back(i); // bridge -> staff
		g_graph[i].push_back(g_bridge);
		g_flow[g_S][i].capacity = 1; // source -> staff(capacity)
		g_flow[g_bridge][i].capacity = k; // bridge -> staff(capacity) // 1�� �ƴϰ� k�̴�!!!
	}
	// job -> sink mapping
	for (int i = 1001; i <= m + 1000; i++) {
		g_graph[i].push_back(g_T);
		g_graph[g_T].push_back(i);
		g_flow[i][g_T].capacity = 1;
	}
	edmond_karp();
	cout << g_maxFlow << "\n";
}