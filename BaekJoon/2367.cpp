// 2367.cpp
// ��Ƽ
// Network Flow �����̴�.
// Edmond-Karp�� Ǯ ���� ������ Dinic �˰������ε� Ǯ �� �ֱ⿡
// Dinic �˰������� �ѹ� Ǯ��ڴ�.
// source - ��� ���� ��θ� ��� �뷮�� K�� �д�,
// Ǫ�� - sink ��θ� ��� �뷮�� �� Ǫ�庰 �뷮�� �ش�.
// ��� - Ǫ�� ��θ� ��� �뷮�� 1�� �ش�.
// �׸��� Dinic �˰������� �ִ� ������ ���ϸ� �ȴ�.
// ���ѽð� 2�� �� 0ms(3,084KB)�� �ҿ�Ǿ���.
// ������� 17/231�� ���� 7.35%�� rank�Ǿ���.

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

const int MAXVAL = 987654321;
struct vertex {
	int cap, flo; // capacity, Flow
	vertex() : cap(0), flo(0) {}
	vertex(int c, int f) : cap(c), flo(f) {}
};
vector<vector<int>> g_graph;
vector<vector<vertex>> g_flow;
vector<int> g_level; // level graph
vector<int> g_edge; // store next edge
int g_S, g_T, g_N;
int g_maxFlow = 0;

bool bfs()
{
	int cur;
	queue<int> myq;
	g_level.assign(g_N + 1, -1);
	g_level[g_S] = 0; // 0 level ���� ����
	myq.push(g_S);
	while (!myq.empty()) {
		cur = myq.front();
		myq.pop();
		for (int next : g_graph[cur]) { // ���� ������ ��� �ְ�, �ܿ��뷮 > 0 �̸�,
			if (g_level[next] == -1 && g_flow[cur][next].cap - g_flow[cur][next].flo > 0) {
				g_level[next] = g_level[cur] + 1;
				myq.push(next);
			}
		}
	}
	return (g_level[g_T] > -1);
}

int dfs(int cur, int flow)
{
	int ret;
	if (cur == g_T) return flow;
	for (int& i = g_edge[cur]; i < g_graph[cur].size(); i++) {
		int next = g_graph[cur][i];
		if (g_level[next] == g_level[cur] + 1 && g_flow[cur][next].cap - g_flow[cur][next].flo > 0) {
			ret = dfs(next, min(flow, g_flow[cur][next].cap - g_flow[cur][next].flo));
			if (ret > 0) {
				g_flow[cur][next].flo += ret;
				g_flow[next][cur].flo -= ret; // ������ ��Ī��
				return ret;
			}
		}
	}
	return 0;
}

void dinic()
{
	int flow;
	while (bfs()) { // level graph�� �����.
		g_edge.assign(g_N + 1, 0); // g_graph ������ ���� index�� 0���� ����
		while (true) {
			flow = dfs(g_S, MAXVAL);
			if (flow == 0) break; // ������θ� �� ã�� ���ϸ�...
			g_maxFlow += flow;
		}
	}
}

int main()
{
	FAST;
	int N, K, D;
	cin >> N >> K >> D;
	g_S = 0;
	g_T = N + D + 1;
	g_N = g_T + 1; // g_T + source
	g_graph.resize(g_N + 1);
	g_flow.resize(g_N + 1, vector<vertex>(g_N + 1, { 0, 0 }));

	for (int i = 1; i < N + 1; i++) { // source - man(cap = K)
		g_graph[g_S].push_back(i);
		g_graph[i].push_back(g_S);
		g_flow[g_S][i].cap = K;
	}
	int fc, fs = N; // food start = N
	for (int i = 1; i < D + 1; i++) { // food - sink(cap = each D)
		cin >> fc;
		g_graph[i + fs].push_back(g_T);
		g_graph[g_T].push_back(i + fs);
		g_flow[i + fs][g_T].cap = fc;
	}
	int fcnt, food;
	for (int i = 1; i < N + 1; i++) { // man - food (cap = 1)
		cin >> fcnt;
		for (int j = 1; j < fcnt + 1; j++) {
			cin >> food;
			g_graph[i].push_back(food + fs);
			g_graph[food + fs].push_back(i);
			g_flow[i][food + fs].cap = 1;
		}
	}
	dinic();
	cout << g_maxFlow << "\n";
}