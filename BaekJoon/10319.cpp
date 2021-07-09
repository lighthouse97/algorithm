// 10319.cpp
// ���� ����Į����
// ICPC > Regionals > Europe > Northwestern European Regional Contest > Benelux Algorithm Programming Contest > BAPC 2014 A��
// Network Flow
// ���� �����ε� ���� ����� �����̴�. ���� Ǯ���� ���߰� Ǯ�� �����ߴ�.(����ü �̷� ���̵��� ��� ������ ����?)
// �ð������̶� ������ �����Ƿ� �� �������� �ð��� ���� ������ ���� �� �����.
// ���� ��� �ٷ� ����, 1���� ����, 2���� ����,... �����ð� + �����ð� <= ����ð��� �ɶ����� �����.
// �׷��� �������� ���� ���� �ð��� ���� �������� �����ϴ� �ð��� �ǰ� ������ ��ĥ ������ ���� �ð� ������ Ÿ�� �ȴ�.
// �̷��� �����ؼ� sink���� �����ϸ� �� ���� max flow�� ���� �ð����� �� �� �ִ� �ִ� ������� �ȴ�.
// 1) source -> start ������, �����ð����� start�� ù��° ������ �ٷ� ����ǰ� capacity�� ������ ��� �� g�̴�.
// 2) ���� -> sink�� ������ ��� ������ sink�� �����ϴµ� capacity�� INF�̴�.
// 3) ���� -> ������ ������ ���� �� ���� �ð� + �����ð� <= ����ð� �� �͸� �����Ѵ�. capacity�� p�̴�.
// 4) ���������� �� �������� ���� ��� �������� �����Ų��. �� �� capacity�� INF�̴�.
// �׸��� network flow �˰������� �ִ� ������ ���Ѵ�.
// ���⼭�� dinic �˰����� ����Ͽ���.
// ���ѽð� 5�� �� 328ms(20,108KB)�� �ҿ�Ǿ���.
// ������� 29/131�� ���� 22.13%�� rank�Ǿ���.

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
	int to, flow, capa, revi;
	edge() : to(-1), flow(0), capa(0), revi(-1) {}
	edge(int t, int f, int c, int r) : to(t), flow(f), capa(c), revi(r) {}
	bool space() { return capa > flow; }
};

vector<vector<edge>> g_graph;
vector<int> g_level; // level graph
vector<int> g_edge; // store next edge
int g_S, g_T, g_N;
int g_maxFlow = 0;

void addEdge(int from, int to, int flow, int capa)
{
	g_graph[from].push_back({ to, flow, capa, (int)g_graph[to].size() });
	g_graph[to].push_back({ from, 0, 0, (int)g_graph[from].size() - 1 });
}

bool bfs() // dinic bfs
{
	int cur;
	queue<int> myq;
	g_level.assign(g_N + 1, -1);
	g_level[g_S] = 0; // 0 level ���� ����
	myq.push(g_S);
	while (!myq.empty()) {
		cur = myq.front();
		myq.pop();
		for (edge& next : g_graph[cur]) { // ���� ������ ��� �ְ�, �ܿ��뷮 > 0 �̸�,
			if (g_level[next.to] == -1 && next.space()) {
				g_level[next.to] = g_level[cur] + 1;
				myq.push(next.to);
			}
		}
	}
	return (g_level[g_T] > -1); // sink���� ��� ��������� return
}

int dfs(int cur, int flow) // dinic dfs
{
	int ret;
	if (cur == g_T) return flow;
	for (int& i = g_edge[cur]; i < g_graph[cur].size(); i++) {
		edge& next = g_graph[cur][i];
		if (g_level[next.to] == g_level[cur] + 1 && next.space()) {
			ret = dfs(next.to, min(flow, next.capa - next.flow));
			if (ret > 0) {
				next.flow += ret;
				g_graph[next.to][next.revi].flow -= ret; // ������ ��Ī��
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
			flow = dfs(g_S, INF);
			if (flow == 0) break; // ������θ� �� ã�� ���ϸ�...
			g_maxFlow += flow;
		}
	}
}

const int UNITN = 101; // unit time
void doTest()
{
	int n;
	cin >> n;
	g_S = (n + 1) * UNITN; g_T = g_S + 1; g_N = (n + 1) * UNITN + 2;
	g_graph.assign(g_N, {});
	int start, g, s;
	cin >> start >> g >> s; // start, people, time limit
	addEdge(g_S, start * UNITN, 0, g); // source -> start
	int m, ho;
	cin >> m;
	for (int i = 0; i < m; i++) { // ���� -> sink
		cin >> ho;
		for (int j = 0; j <= s; j++)
			addEdge(ho * UNITN + j, g_T, 0, INF);
	}
	int r, a, b, p, t;
	cin >> r;
	for (int i = 0; i < r; i++) { // ���� -> ����
		cin >> a >> b >> p >> t;
		for (int j = 0; j + t <= s; j++)
			addEdge(a * UNITN + j, b * UNITN + j + t, 0, p); // t ��ŭ �����Ǿ� ������
	}
	for (int i = 1; i < n + 1; i++) { // �� �������� ���� �������� ��ٷȴ� ���� �ð� ó�� 
		for (int j = 0; j < s; j++)
			addEdge(i * UNITN + j, i * UNITN + j + 1, 0, INF);
	}
	g_maxFlow = 0;
	dinic();
	cout << g_maxFlow << "\n";
}

int main()
{
	FAST;
	int T;
	cin >> T;
	while (T--) doTest();
}