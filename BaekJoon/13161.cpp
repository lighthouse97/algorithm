// 13161.cpp
// �д��� ����
// network flow���� minumun cut(�ּ� ����)�� ���ϴ� �����ε�, �̴� �� maximum flow(�ִ� ����)��
// ���ϴ� ������ ������ �����ϴ�.
// �� �׷����� 2���� �׷����� �ɰ���(cut) �������� �ּ� ����� �� �����鿡 ���� �ִ� ������ flow��(capacity�� �ƴ�)
// �� �հ� ����.
// A ������ ������ source�� �����ϰ� �̶��� capacity�� INF, B ������ ������ sink�� �����ϰ� �̶��� capacity�� INF,
// �׸��� A, B ���� �� ������ �������� flow�� ���� capacity�� ������ ���� �ִ� ���� �����Ѵ�.
// ���� network�� maximum flow�� ������ Ǭ��. �� ������ �ִ� 500��, ������ �ִ� 500^2���̹Ƿ� Edmond-Karp algorithm���δ�
// �ð� �ʰ��� �߻��ϰ� ���� �� ������ Dinic algorithm���� Ǭ��.(O(VE^2) -> O(V^2E)
// A, B ���� cut�� maximum flow���� ��, source���� bfsŽ���Ͽ� visited�ƴϰ� capacity - flow > 0 �� ������ ��Ƽ�
// A, �������� B�� �����ϸ� �ȴ�.
// 
// �Ѱ��� ������ ���� source, sink �ƴ� N���� ������� �׷����� ������ �� 2�� for ������ i, j �����ϱ� ������
// i -> j, j -> i�� for������ ���� ������ �ȴ�. �׷��� �����ؼ� ��������� �Ѵٰ� i-j�Ҷ� j->i�� ���� �����ع�����
// ������� 2������ ������ �Ǿ� ���ʿ��� ������ �� �ϰ� �Ǿ� �°� �ص� �ð��ʰ��� �߻��Ѵ�!!!
// ���ѽð� 1�� �� 32ms(5,040KB)�� �ҿ�Ǿ���.
// ������� 13/179�� ���� 7.26%�� rank�Ǿ���.

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

vector<vector<edge>> g_flow;
vector<vector<int>> g_graph;
vector<int> g_level;
vector<int> g_work;
int g_S = 0, g_T = 0; // S(0), T(N+1)
int g_maxFlow = 0; // �ִ� ����
const int g_INF = 987654321;

// Dinic bfs
bool bfs()
{
	queue<int> myq;
	int current;
	fill(g_level.begin(), g_level.end(), -1);
	g_level[g_S] = 0;
	myq.push(g_S);

	while (!myq.empty()) {
		current = myq.front();
		myq.pop();
		for (int next : g_graph[current]) {
			if (g_level[next] == -1 && g_flow[current][next].capacity - g_flow[current][next].flow > 0) {
				g_level[next] = g_level[current] + 1;
				myq.push(next);
			}
		}
	}
	return g_level[g_T] != -1;
}

// Dinic dfs
int dfs(int current, int flow)
{
	int ret;
	if (current == g_T) return flow;

	for (int& i = g_work[current]; i < g_graph[current].size(); i++) {
		int next = g_graph[current][i];
		if (g_level[next] == g_level[current] + 1 && g_flow[current][next].capacity - g_flow[current][next].flow > 0) {
			ret = dfs(next, min(flow, g_flow[current][next].capacity - g_flow[current][next].flow));
			if (ret > 0) {
				g_flow[current][next].flow += ret;
				g_flow[next][current].flow -= ret;
				return ret;
			}
		}
	}
	return 0;
}

// Run Dinic algorithm
void dinic()
{
	int flow;
	while (bfs()) {
		fill(g_work.begin(), g_work.end(), 0);
		while (true) {
			flow = dfs(g_S, g_INF);
			if (flow == 0) break;
			g_maxFlow += flow;
		}
	}
}

int main()
{
	FAST;

	int n;
	int in;
	cin >> n;
	g_T = n + 1;
	g_flow.resize(g_T + 1, vector<edge>(g_T + 1, {0, 0}));
	g_graph.resize(g_T + 1);
	g_level.resize(g_T + 1, -1);
	g_work.resize(g_T + 1, 0);

	for (int i = 1; i < n + 1; i++) { // S, A�׷� ����/ B, T�׷� ����
		cin >> in;
		if (in == 1) {
			g_flow[g_S][i].capacity = g_INF;
			g_graph[g_S].push_back(i);
			g_graph[i].push_back(g_S);
		}
		else if (in == 2) {
			g_flow[i][g_T].capacity = g_INF;
			g_graph[i].push_back(g_T);
			g_graph[g_T].push_back(i);
		}
	}
	// ������ �����鳢�� ����
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < n + 1; j++) {
			cin >> in;
			g_flow[i][j].capacity = in;
			if (i != j) {
				g_graph[i].push_back(j); // j -> i�� ������ for���� �����ϱ� ������ �ߺ��ؼ� ���⼭ j -> i �������� �ʿ����!
			}
		}
	}
	// run Dinic Algorithm
	dinic();
	cout << g_maxFlow << "\n";
	// ���� �׷� �и�(minumum-cut)
	queue<int> myq;
	vector<bool> visit;
	visit.resize(g_T + 1, false);
	visit[g_S] = true;
	myq.push(g_S);
	while (!myq.empty()) {
		int cur = myq.front();
		myq.pop();
		for (int next : g_graph[cur]) {
			if (!visit[next] && g_flow[cur][next].capacity - g_flow[cur][next].flow > 0) {
				visit[next] = true;
				myq.push(next);
			}
		}
	}
	for (int i = 1; i < n + 1; i++) {
		if (visit[i]) cout << i << " ";
	}
	cout << "\n";
	for (int i = 1; i < n + 1; i++) {
		if (!visit[i]) cout << i << " ";
	}
	cout << "\n";
}