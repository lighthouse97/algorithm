// 2365.cpp
// ������ �����
// 1) 1 ~ N(row)�� source�� ����, capacity�� row��
// 2) N + 1 ~ 2N(col)�� sink�� ����, capacity�� col��
// 3) �������� ����. �� �� capacity�� INF�� �����ߴٰ� ���� WA������!
//    �� ���� capacity�� row��, col�� �� ���� ū ���� max�� �ؼ� ���� Ž������ ��� �ٲ���� �Ѵ�.
// 4) dinic������ maxFlow�� row��(�Ǵ� col��, �� �� ���� ��)���� ������ �������� ���� ���� Ž���� ������ �����Ѵ�.
// 5) ���� Ž���� ������ �� �� maxFlow�� ���� dinic�� �ѹ� �� �������� �����Ѵ�.
// 6) ���� Ž�� ������ ���� left��(lo��)�� ������ ������ �����ϴ� ���̰� �� ���� row-col ������ �帣�� flow�� ���ʷ� ����Ѵ�.
// �ݼ��� ��!!
// ó�� ���� ������ ���� �ð����� 5�ʷ� �־��� ������ network flow �Լ��� ���� �� ȣ���ϴ� �ű���...��� ��ġ�� ë��� �Ѵ�!
// ���� Ž������ dinic ������ ���� ������ capacity���� ��������� �ϴµ�, �� �� flow���� 0���� ���� �ʱ�ȭ���Ѿ� �ϴµ� �װ��� ���߷ȴ�!!!
// �̰� ������ �������� WA�� ���Դ�!!!
// ���ѽð� 2�� �� 0ms(2,156KB)�� �ҿ�Ǿ���.
// ������� 23/158�� ���� 14.55%�� rank�Ǿ���.

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

int main()
{
	FAST;
	int N;
	cin >> N;
	g_S = N * 2 + 1; g_T = g_S + 1; g_N = g_T;
	g_graph.resize(g_N + 1);
	int c, maxcap = 0, sum = 0;
	for (int i = 1; i < N + 1; i++) { // ���� ��(src -> ��)
		cin >> c;
		maxcap = max(maxcap, c);
		sum += c;
		addEdge(g_S, i, 0, c);
	}
	for (int i = 1 + N; i < 2 * N + 1; i++) { // ���� ��(�� -> sink)
		cin >> c;
		maxcap = max(maxcap, c);
		addEdge(i, g_T, 0, c);
	}
	for (int i = 1; i < N + 1; i++) { // �� -> ��
		for (int j = 1 + N; j < 2 * N + 1; j++)
			addEdge(i, j, 0, INF);
	}

	int left = 0, right = maxcap, mid = 0; // ���� Ž��(lower_bound)
	while (left < right) {
		mid = (left + right) >> 1;
		for (int i = 1; i < g_N + 1; i++) {
			for (edge& link : g_graph[i]) {
				link.flow = 0; // flow�� ��� �ʱ�ȭ
				if (i <= N && link.to < g_S) link.capa = mid;
			}
		}
		g_maxFlow = 0;
		dinic();
		if (g_maxFlow < sum) left = mid + 1;
		else right = mid;
	}

	if (g_maxFlow != sum) {
		for (int i = 1; i < g_N + 1; i++) { // �̺� Ž������ ã�� left�� dinic�ѹ� �� ������!
			for (edge& link : g_graph[i]) {
				link.flow = 0; // flow�� ��� �ʱ�ȭ
				if (i <= N && link.to < g_S) link.capa = left;
			}
		}
	}
	g_maxFlow = 0;
	dinic();

	cout << left << "\n";
	for (int i = 1; i < N + 1; i++) {
		for (edge& link : g_graph[i])
			if (link.to < g_S) cout << link.flow << " ";
		cout << "\n";
	}
}