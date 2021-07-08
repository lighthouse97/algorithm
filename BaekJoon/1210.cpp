// 1210.cpp
// 마피아
// Olympiad > Baltic Olympiad in Informatics > BOI 2008 0번
// Network Flow, Maximum Flow Minumum Cut
// 정점 분리
// 여기까지는 쉬운데, maximum flow를 구한 다음에 막는 점을 찾는것이 아주 어렵다.
// 1) 정점을 막으므로 정점분리, 분리된 정점끼리는 단방향에 주어진 capacity저장, 정점끼리는 양방향에 capacity는 INF
// 2) 최대유량을 구한 후 source --> sink까지 BFS 탐색하면서 flow == capacity인 정점을 모두 찾아서 오름차순 정렬한다.
// 3) 2) 에서 조건이 한 경로에 여러개 있으면 이 중 하나만 골라야 한다. 그래서 첫번째 거를 골랐는데 계속 틀린다!
// 4) 구사과 블로거를 참조는 했지만, 이 방식하고 내가 했던 방식의 차이점, 
//    즉 내가 한 방식에서의 반례를 도저히 찾지를 못해 이 문제는 일단 포기(GIVE UP) 상태이다!!!
// AC가 나온 방식은, source에서부터 BFS 탐색해서, 방문하지 않았고 잔여용량(residual capacity) > 0인 정점을 큐에 넣고 visit처리한다.
// 이후 정점 1 ~ N까지 탐색하면서 IN(i)가 visit하였고 OUT(i)가 visit 하지 않은 i 정점만 출력한다.
// 그런데... 이거하고 3)하고 어디가 차이가 있는지 도저히 알 수가 없다!!!
// 제한시간 2초 중 4ms(3,876KB)가 소요되었다.
// 맞은사람 22/164로 상위 13.41%에 rank되었다.

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
	g_level[g_S] = 0; // 0 level 부터 시작
	myq.push(g_S);
	while (!myq.empty()) {
		cur = myq.front();
		myq.pop();
		for (edge& next : g_graph[cur]) { // 다음 정점이 비어 있고, 잔여용량 > 0 이면,
			if (g_level[next.to] == -1 && next.space()) {
				g_level[next.to] = g_level[cur] + 1;
				myq.push(next.to);
			}
		}
	}
	return (g_level[g_T] > -1); // sink까지 경로 만들어지면 return
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
				g_graph[next.to][next.revi].flow -= ret; // 유량의 대칭성
				return ret;
			}
		}
	}
	return 0;
}

void dinic()
{
	int flow;
	while (bfs()) { // level graph를 만든다.
		g_edge.assign(g_N + 1, 0); // g_graph 정점의 간선 index는 0부터 시작
		while (true) {
			flow = dfs(g_S, INF);
			if (flow == 0) break; // 증가경로를 더 찾지 못하면...
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
	g_N = n * 2; // because of 정점분리
	g_graph.resize(g_N + 1);
	int s, t;
	cin >> s >> t;
	g_S = s * 2 - 1; g_T = t * 2;
	int c;
	for (int i = 1; i < n + 1; i++) { // 정점들 분리
		cin >> c;
		addEdge(i * 2 - 1, i * 2, 0, c);
	}
	for (int i = 0; i < m; i++) { // 정점 사이에 간선 연결(양방향)
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