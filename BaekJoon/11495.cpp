// 11495.cpp
// ���� 0 �����
// ICPC > Regionals > Asia Pacific > Korea > Asia Regional - Daejeon 2015 C��
// Network Flow�����ε� �̰� �� Network Flow �������� �ƴ� �� ���� �����̴�.
// ���� ����� �����̴�!!!
// Ǯ���� �ٽ��� �밢�����δ� �� �� ���� ���� �¿�� ��ĭ�� �� �� �����Ƿ� ü���� ������ �����ϰ�,
// ����, �������� ��ġ�� �ʰ� 2���� �׷����� ������. �� ��ĭ�� �� �����ϰ� ������ �׷����� �����Ѵ�.
// �׸��� 2���� �׷찣�� �����¿�� �׷��� �����ϰ�(���� �ҽ�, ��ũ�� �� �׷쿡 ����) �ִ� ������ ���Ѵ�.
// �־��� ������ ������ ��� ���� ������ ���� �ִ�� �����ϴ� ȸ���̰�, �տ����� �ִ� ������ �������� 2����
// �ѹ����� ���� �� �ִ� ���� ȸ���̹Ƿ� �� ���� ��� ������ �տ��� �� �ָ� �ʿ��� �ּ����� ���� Ƚ���� �ȴ�.
// Network Flow���� �ִ� ������ Dinic �˰����� ����Ͽ���.
// ���ѽð� 7�� �� 228ms(66,696KB)�� �ҿ�Ǿ���.
// ������� 139/376�� ���� 36.96%�� rank�Ǿ���.

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

struct info {
	int r, c, index;
	info() : r(0), c(0), index(0) {}
	info(int r, int c, int i) : r(r), c(c), index(i) {}
};

void doTest()
{
	int n, m;
	cin >> n >> m;
	g_S = n * m + 1;
	g_T = g_S + 1;
	g_N = g_T;
	g_graph.assign(g_N + 1, {});
	g_flow.assign(g_N + 1, vector<edge>(g_N + 1, { 0, 0 }));
	g_maxFlow = 0;
	vector<vector<int>> table(n + 1, vector<int>(m + 1, -1));
	vector<info> aa;
	vector<info> bb;
	bool flag = true; int total = 0;
	for (int i = 1; i < n + 1; i++) { // ���� ������ �Է� �� A, B �׷� �и�
		flag = (i % 2) ? true : false;
		for (int j = 1; j < m + 1; j++) {
			cin >> table[i][j];
			total += table[i][j];
			if (flag) {
				aa.push_back({ i, j, (i - 1) * m + j });
				flag = false;
			}
			else {
				bb.push_back({ i, j, (i - 1) * m + j });
				flag = true;
			}
		}
	}
	int dr[4] = { -1, 0, 1, 0 };
	int dc[4] = { 0, -1, 0, 1 };
	int nr, nc, ind;
	for (info& cur : aa) {
		g_flow[g_S][cur.index].capa = table[cur.r][cur.c]; // src -> A ���� ���� ����
		g_graph[g_S].push_back(cur.index);
		g_graph[cur.index].push_back(g_S);
		for (int i = 0; i < 4; i++) { // A, B ���� ���� ����
			nr = cur.r + dr[i];
			nc = cur.c + dc[i];
			if (nr < 1 || nc < 1 || nr > n || nc > m) continue;
			ind = (nr - 1) * m + nc;
			g_flow[cur.index][ind].capa = MAXVAL;
			g_graph[cur.index].push_back(ind);
			g_graph[ind].push_back(cur.index);
		}
	}
	for (info& cur : bb) { // B -> sink ������ ���� ����
		g_flow[cur.index][g_T].capa = table[cur.r][cur.c];
		g_graph[cur.index].push_back(g_T);
		g_graph[g_T].push_back(cur.index);
	}
	dinic();
	cout << (total - g_maxFlow) << "\n";
}

int main()
{
	FAST;
	int T;
	cin >> T;
	while (T--) doTest();
}