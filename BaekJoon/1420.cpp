// 1420.cpp
// �б� ������!
// ���� �ذ� ����� �����ϱⰡ �ſ� ��ƴ�.
// ��� �������� ���� �����ϰ� �� �� �ִ� �������� ����� �������� �����Ѵ�.
// �׸��� source -> sink ���� �ִ� ������ ���Ѵ�.
// 1) �������� ���� �ѹ��� ����� �ߺ��ؼ� ���� �� ������� ����.
//    �׷��� ������ �и���Ű�� ������ �뷮�� 1�� ����ش�.
// 2) ���������� ���� �������� �� ���� �� �ü��� �����Ƿ� ������ �뷮�� INF�� ��´�.
// Network Flow �˰����� Dinic�� ����Ͽ���.
// �� ���̵� ������ ���� ���ߴ�!!!
// 12ms(5,868KB) -> 4ms(4,264KB) �ҿ�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
#include <cstdlib> // abs
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

bool makeGraph(int n, int m, vector<string>& rd)
{
	auto makeV = [&](int i, int j) { return (i - 1) * m + j; };
	auto leftV = [](int v) { return v * 2 - 1; };
	auto rightV = [](int v) { return v * 2; };
	auto canGo = [&](int i, int j) { return (i < 1 || j < 1 || i > n || j > m || rd[i][j] == '#') ? false : true; };
	int sr = 0, sc = 0, tr = 0, tc = 0;
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < m + 1; j++) {
			if (rd[i][j] == 'K') {
				g_S = rightV(makeV(i, j)); // source ����
				sr = i; sc = j;
			}
			else if (rd[i][j] == 'H') {
				g_T = leftV(makeV(i, j)); // sink ����
				tr = i; tc = j;
			}
			else if (rd[i][j] == '#') continue;
			// �� ���� ����
			int v = makeV(i, j);
			int left = leftV(v), right = rightV(v);
			addEdge(left, right, 0, 1);
			// ������ ���� ����
			int dr[] = { 0, 1, 0, -1 };
			int dc[] = { -1, 0, 1, 0 };
			for (int k = 0; k < 4; k++) {
				int adr = i + dr[k], adc = j + dc[k];
				if (canGo(adr, adc))
					addEdge(right, leftV(makeV(adr, adc)), 0, INF);
			}
		}
	}
	if (abs(tr - sr) + abs(tc - sc) <= 1) return false; // src, sink�� ������ ���
	return true;
}

int main()
{
	FAST;
	int n, m;
	cin >> n >> m;
	vector<string> road(n + 1);
	for (int i = 1; i < n + 1; i++) {
		cin >> road[i];
		road[i] = " " + road[i]; // start from index 1
	}
	g_N = n * m * 2; // bacause of �����и�	
	g_graph.resize(g_N + 1);
	if (!makeGraph(n, m, road)) {
		cout << -1 << "\n";
		return 0;
	}
	dinic();
	cout << g_maxFlow << "\n";
}