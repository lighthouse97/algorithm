// 1420.cpp
// �б� ������!
// Dinic algorithm�� ����Ͽ���.
// �������� �ڸ��Ƿ� ���� �����ؾ� �ϰ� network flow�� �� ������ ������ �ٴ� �˰������� Ǭ��.
// ��� �����ؾ� ���� ���� �ٸ� ����� Ǭ ���� ���� �ܿ� �����Ͽ���!
// �� ������ ��� Edmond-Karp algorithm���� �ð��� �� ���� �ɷȴ�.(8ms -> 12ms, Edmond�� 8ms)
// 12ms(5,864KB)
// ������ ���� ���� Dinic algorithm���� Ǯ�� 0ms�� �ɷȴ�. �ѹ� �ڼ��� ���� �ڴ�!
// ��... �׸��� �������� capacity�� INF�� ���� �ʰ�(�̰� ���ذ� �� �Ȱ���) 1�� �ص� AC�� ���´�!

#include "pch.h"
//#include <cstdio> // NULL
#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs, hypot, round
#include <vector>
#include <algorithm> // sort, max, min, fill
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
#include <queue> // queue, priority_queue
#include <map>
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct edge {
	int capacity;
	int flow;
};

map<pair<int, int>, edge> g_flow;
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
			if (g_level[next] == -1 && g_flow[{current, next}].capacity - g_flow[{current, next}].flow > 0) {
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

	for (int& i = g_work[current]; i < (int)g_graph[current].size(); i++) {
		int next = g_graph[current][i];
		if (g_level[next] == g_level[current] + 1 && g_flow[{current, next}].capacity - g_flow[{current, next}].flow > 0) {
			ret = dfs(next, min(flow, g_flow[{current, next}].capacity - g_flow[{current, next}].flow));
			if (ret > 0) {
				g_flow[{current, next}].flow += ret;
				g_flow[{next, current}].flow -= ret;
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

int g_m, g_n;
int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };
vector<string> g_road;

inline int makeV(int i, int j) { return (i - 1)*g_m + j; }
inline int leftV(int v) { return v * 2 - 1; }
inline int rightV(int v) { return v * 2; }
inline bool canGo(int i, int j) { return (i < 1 || j < 1 || i > g_n || j > g_m || g_road[i][j] == '#') ? false : true; }

int main()
{
	FAST;

	int n, m;
	int vsize;
	cin >> n >> m;
	g_m = m; g_n = n;
	g_road.resize(n + 1);
	for (int i = 1; i < n + 1; i++) {
		cin >> g_road[i];
		g_road[i] = " " + g_road[i]; // index 1���� ����(�տ� ""(null)�� ������ ��Ʈ�� insert�� �ȵȴ�)
	}
	vsize = n * m * 2; // bacause of �����и�	
	g_graph.resize(vsize + 1);
	g_level.resize(vsize + 1, -1);
	g_work.resize(vsize + 1, 0);
	
	int sr = 0, sc = 0, tr = 0, tc = 0;
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < m + 1; j++) {
			if (g_road[i][j] == 'K') {
				g_S = rightV(makeV(i, j));
				sr = i; sc = j;
			}
			else if (g_road[i][j] == 'H') {
				g_T = leftV(makeV(i, j));
				tr = i; tc = j;
			}
			else if (g_road[i][j] == '#') continue;
			// �� ���� ����
			int v = makeV(i, j);
			int left = leftV(v), right = rightV(v);
			g_flow[{left, right}].capacity = 1;
			g_flow[{right, left}].capacity = 0;
			g_graph[left].push_back(right);
			g_graph[right].push_back(left);
			// ������ ���� ����
			for (int k = 0; k < 4; k++) {
				int ady = i + dy[k], adx = j + dx[k];
				if (canGo(ady, adx)) {
					g_flow[{right, leftV(makeV(ady, adx))}].capacity = g_INF;
					g_flow[{leftV(makeV(ady, adx)), right}].capacity = 0;
					g_graph[right].push_back(leftV(makeV(ady, adx)));
					g_graph[leftV(makeV(ady, adx))].push_back(right);
				}
			}
		}
	}
	// S�� T�� ������ ������ S �Ǵ� T�� ������ �ٲ� �� �����Ƿ� S�� T���̿� ���� �� ���� ����. �̶��� ���� �� ���� ����̴�.
	if ((n == 1 && m == 1) || g_S == 0 || g_T == 0 || abs(tr - sr) + abs(tc - sc) == 1) {
		cout << -1 << "\n";
		return 0;
	}
	// run Dinic Algorithm
	dinic();
	cout << g_maxFlow << "\n";
}