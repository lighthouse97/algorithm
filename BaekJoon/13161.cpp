// 13161.cpp
// 분단의 슬픔
// network flow에서 minumun cut(최소 유량)을 구하는 문제인데, 이는 곳 maximum flow(최대 유량)을
// 구하는 기존의 문제와 동일하다.
// 즉 그래프를 2개의 그룹으로 쪼개는(cut) 간선들의 최소 비용이 이 간선들에 대한 최대 유량의 flow값(capacity가 아님)
// 의 합과 같다.
// A 진영의 정점을 source에 연결하고 이때의 capacity는 INF, B 진영의 정점을 sink에 연결하고 이때의 capacity는 INF,
// 그리고 A, B 진영 및 나머지 정정들의 flow에 대한 capacity는 문제에 나와 있는 데로 연결한다.
// 다음 network의 maximum flow로 문제를 푼다. 단 정점이 최대 500개, 간선이 최대 500^2개이므로 Edmond-Karp algorithm으로는
// 시간 초과가 발생하고 따라서 이 문제는 Dinic algorithm으로 푼다.(O(VE^2) -> O(V^2E)
// A, B 진영 cut은 maximum flow구한 뒤, source부터 bfs탐색하여 visited아니고 capacity - flow > 0 인 정점만 모아서
// A, 나머지는 B로 구분하면 된다.
// 
// 한가지 주의할 점은 source, sink 아닌 N명의 사람들을 그래프로 연결할 때 2중 for 문으로 i, j 연결하기 때문에
// i -> j, j -> i는 for문에서 각각 연결이 된다. 그런데 착각해서 양방향으로 한다고 i-j할때 j->i도 같이 연결해버리면
// 양방향이 2중으로 연결이 되어 불필요한 연산을 더 하게 되어 맞게 해도 시간초과가 발생한다!!!
// 제한시간 1초 중 32ms(5,040KB)가 소요되었다.
// 맞은사람 13/179로 상위 7.26%에 rank되었다.

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
int g_maxFlow = 0; // 최대 유량
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

	for (int i = 1; i < n + 1; i++) { // S, A그룹 연결/ B, T그룹 연결
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
	// 나머지 정점들끼리 연결
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < n + 1; j++) {
			cin >> in;
			g_flow[i][j].capacity = in;
			if (i != j) {
				g_graph[i].push_back(j); // j -> i는 다음번 for에서 연결하기 때문에 중복해서 여기서 j -> i 연결해줄 필요없다!
			}
		}
	}
	// run Dinic Algorithm
	dinic();
	cout << g_maxFlow << "\n";
	// 정점 그룹 분리(minumum-cut)
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