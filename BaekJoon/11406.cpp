// 11406.cpp
// å �����ϱ� 2
// '11407 å �����ϱ� 3'���� �ּ� ���(�ִ� �Ÿ�) ���Ǹ� ���� ���̴�.
// �ִ� �Ÿ� ������ ������ �� ������ �׳� �ܼ��� Network Flow �����̴�.
// Network Flow �˰��� Edmond-Karp�� Dinic �˰��� �� Dinic �˰����� ����Ͽ���.
// ���ѽð� 1�� �� 0ms(2,556KB)�� �ҿ�Ǿ���.
// ������� 36/246�� ���� 14.63%�� rank�Ǿ���.

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
	int N, M;
	cin >> N >> M;
	g_S = N + M + 1;
	g_T = g_S + 1;
	g_N = g_T;
	g_graph.resize(g_N + 1);
	g_flow.resize(g_N + 1, vector<vertex>(g_N + 1, { 0, 0 }));

	for (int i = M + 1; i < M + N + 1; i++) { // ��� <-> sink
		cin >> g_flow[i][g_T].cap;
		g_graph[i].push_back(g_T);
		g_graph[g_T].push_back(i);
	}
	for (int i = 1; i < M + 1; i++) { // source <-> ����
		cin >> g_flow[g_S][i].cap;
		g_graph[g_S].push_back(i);
		g_graph[i].push_back(g_S);
	}
	for (int i = 1; i < M + 1; i++) { // ���� <-> ���(�뷮)
		for (int j = M + 1; j < M + N + 1; j++) {
			cin >> g_flow[i][j].cap;
			g_graph[i].push_back(j);
			g_graph[j].push_back(i);
		}
	}
	dinic();
	cout << g_maxFlow << "\n";
}