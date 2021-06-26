// 5651.cpp
// ���� �߿��� ����
// ICPC > Regionals > Asia Pacific > Thailand > 2011 ACM-ICPC Asia Phuket Regional Programming Contest P4��
// Network Flow ���� ����. source -> sink���� ��ΰ� ����� ���� ��, minFlow�� �ش�Ǵ� ������
// ��� �� ������ count�ϸ� �ȴ�.
// --> �̷��� �ϸ� Ʋ����!!!
//     �ִ� ������ ������� ���ϰ� �ܿ� �뷮�� 0�� �������� ������� ��ȸ�� �� �ִ� ��ΰ� ������ ī��Ʈ +1�ϰ�
//     ��ȸ�� �� �ִ� ��ΰ� ������ ���� �߿��� ������ �ƴϹǷ� ī��Ʈ���� �ʴ´�.
//     �̴� ������ �����, �������� �޾Ƽ� bfs�� Ž���غ���.
// Dinic �˰������� Ǯ�� ����.
// ���ѽð� 1�� �� 56ms(3,128KB)�� �ҿ�Ǿ���.
// ������� 54/298�� ���� 18.12%�� rank�Ǿ���.

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
struct edge {
	int capa, flow; // capacity, flow 
	edge() : capa(0), flow(0) {}
	edge(int c, int f) : capa(c), flow(f) {}
	bool space() { return capa > flow; }
};
vector<vector<int>> g_graph;
vector<vector<edge>> g_flow;
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
			if (g_level[next] == -1 && g_flow[cur][next].space()) {
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
		if (g_level[next] == g_level[cur] + 1 && g_flow[cur][next].space()) {
			ret = dfs(next, min(flow, g_flow[cur][next].capa - g_flow[cur][next].flow));
			if (ret > 0) {
				g_flow[cur][next].flow += ret;
				g_flow[next][cur].flow -= ret; // ������ ��Ī��				
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

bool checkEdge(int s, int e) // �ܿ� �뷮�� 0�� ���� �� ��ȸ ��ΰ� ���� ���� ã�´�.
{
	queue<int> myq;
	vector<bool> visited(g_N + 1, false);
	myq.push(s);
	visited[s] = true;
	while (!myq.empty()) {
		int cur = myq.front(); myq.pop();
		if (cur == e) break;
		for (int next : g_graph[cur]) {
			if (!visited[next] && g_flow[cur][next].space()) {
				myq.push(next);
				visited[next] = true;
			}
		}
	}
	if (visited[e]) return true;
	return false;
}

void doTest()
{
	int N, M;
	cin >> N >> M;
	g_S = 1; g_T = N; g_N = N;
	g_graph.assign(g_N + 1, {});
	g_flow.assign(g_N + 1, vector<edge>(g_N + 1, { 0, 0 }));
	g_maxFlow = 0;
	vector<vector<int>> candidate(M, vector<int>(2, 0));
	int f, t, b;
	for (int i = 0; i < M; i++) {
		cin >> f >> t >> b;
		g_flow[f][t].capa += b;
		g_graph[f].push_back(t);
		g_graph[t].push_back(f);
		candidate[i] = { f, t };
	}
	dinic();
	int answer = 0;
	int s, e;
	for (int i = 0; i < M; i++) {
		s = candidate[i][0];
		e = candidate[i][1];
		if (!g_flow[s][e].space())
			if (!checkEdge(s, e)) answer++;
	}
	cout << answer << "\n";
}

int main()
{
	FAST;
	int T;
	cin >> T;
	for (int i = 0; i < T; i++) doTest();
}