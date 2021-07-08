// 1210.cpp
// ���Ǿ�
// Olympiad > Baltic Olympiad in Informatics > BOI 2008 0��
// Network Flow, Maximum Flow Minumum Cut
// ���� �и�
// ��������� ���, maximum flow�� ���� ������ ���� ���� ã�°��� ���� ��ƴ�.
// 1) ������ �����Ƿ� �����и�, �и��� ���������� �ܹ��⿡ �־��� capacity����, ���������� ����⿡ capacity�� INF
// 2) �ִ������� ���� �� source --> sink���� BFS Ž���ϸ鼭 flow == capacity�� ������ ��� ã�Ƽ� �������� �����Ѵ�.
// 3) 2) ���� ������ �� ��ο� ������ ������ �� �� �ϳ��� ���� �Ѵ�. �׷��� ù��° �Ÿ� ����µ� ��� Ʋ����!
// 4) ����� ��ΰŸ� ������ ������, �� ����ϰ� ���� �ߴ� ����� ������, 
//    �� ���� �� ��Ŀ����� �ݷʸ� ������ ã���� ���� �� ������ �ϴ� ����(GIVE UP) �����̴�!!!
// AC�� ���� �����, source�������� BFS Ž���ؼ�, �湮���� �ʾҰ� �ܿ��뷮(residual capacity) > 0�� ������ ť�� �ְ� visitó���Ѵ�.
// ���� ���� 1 ~ N���� Ž���ϸ鼭 IN(i)�� visit�Ͽ��� OUT(i)�� visit ���� ���� i ������ ����Ѵ�.
// �׷���... �̰��ϰ� 3)�ϰ� ��� ���̰� �ִ��� ������ �� ���� ����!!!
// ���ѽð� 2�� �� 4ms(3,876KB)�� �ҿ�Ǿ���.
// ������� 22/164�� ���� 13.41%�� rank�Ǿ���.

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

vector<int> find_point(int start)
{
	vector<bool> visit(g_N + 1, false);
	vector<int> answer;
	queue<int> myq;
	myq.push(start);
	visit[start] = true;
	while (!myq.empty()) {
		int cur = myq.front(); myq.pop();
		for (edge& link : g_graph[cur]) {
			if (!visit[link.to] && link.space()) {				
				visit[link.to] = true;
				myq.push(link.to);								
			}
		}
	}
	for (int i = 1; i < g_N / 2 + 1; i++) {
		if (visit[2 * i - 1] && !visit[2 * i]) answer.push_back(i);
	}
	sort(answer.begin(), answer.end());
	return answer;
}

int main()
{
	FAST;
	int n, m;
	cin >> n >> m;
	g_N = n * 2; // because of �����и�
	g_graph.resize(g_N + 1);
	int s, t;
	cin >> s >> t;
	g_S = s * 2 - 1; g_T = t * 2;
	int c;
	for (int i = 1; i < n + 1; i++) { // ������ �и�
		cin >> c;
		addEdge(i * 2 - 1, i * 2, 0, c);
	}
	for (int i = 0; i < m; i++) { // ���� ���̿� ���� ����(�����)
		cin >> s >> t;
		addEdge(s * 2, t * 2 - 1, 0, INF);
		addEdge(t * 2, s * 2 - 1, 0, INF);
	}	
	dinic();
	vector<int> answer;		
	answer = find_point(g_S);	
	for (int x : answer) cout << x << " ";
	cout << "\n";
}