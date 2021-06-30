// 2316.cpp
// 도시 왕복하기 2
// '도시 왕복하기1' 과 같이 최대 유량을 구한는 문제이다.
// 단 차이점이 1) 간선이 양방향이고 2) 정점을 한번만 지나갈 수 있다 이다.
// 1) 간선이 양방향 조건은 양방향으로 갈 수 있다는 것이지 경로 정하는 여러 경우의 수 중
//    어느 한쪽으로 정해지면 이후는 단방향과 동일하다.
//    따라서 단방향과 동일하게 가되 간선의 용량(capacity)을 양방향으로 주면 된다.
// 2) 정점을 한번만 지나간다는 것은 약간의 기교가 필요한데,
//    정점 3이라면 3'를 하나 더 만들어 3->3'의 용량1인 방향있는 간선을 추가하면 된다.
//    따라서 정점 갯수가 N이면 N*2의 정점이 만들어 진다. (정점분할 기법)
// 주의할 점!!
// from <-> to 의 정방향, 역방향 capacity 입력할 때 출발점, 도착점 주의해야 한다. 아무 생각없이 복붙했다가 틀렸다!!!
// 제한시간 2초 중 132ms(7,040KB)가 소요되었다.
// 맞은사람 420/495로 상위 84.84%에 rank되었다.
///
// 양방향 그래프라 정점의 인접 간선만 따라가서 수행 시간을 좀 더 최적화 시킬 수 있다.
// 단방향 그래프는 역방향으로도 갈 수 있어야 하기 때문에 인접 간선으로 갈 수 없기에 모든 점에 대해 c - f 를 조사해야 한다.
// 그래프 만들때 주의할 점은 flow방향과 graph방향이 다르다는 것이다.
// flow는 v->v', v'->u, u'->v 이렇게만 가능하지만 그래프는 v<->v', v'<->u, u'<->v 모든 연결에서 양방향 가능하다.
// 제한시간 2초 중 8ms(7,304KB)가 소요되었다. (132ms -> 8ms)
// 맞은사람 182/495로 상위 36.76%에 rank되었다.
// 정점 분리하지 않고 양방향 그래프로 풀 되 visit배열을 사용하여 한번 방문했던 정점을 체크해서 풀 수도 있다.
// (정점이 줄어들어 좀 더 빠르지 않을까 싶다)

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

struct vertex {
	int capacity;
	int flow;
};

vector<vector<vertex>> g_flow; // flow/capacity information
vector<int> g_prev;
vector<vector<int>> g_graph;
int g_S = 0, g_T = 0, g_N = 0; // start, sink(terminal), number of vertex
int g_maxFlow = 0; // 최대 유량

void edmond_karp()
{
	int current;
	int maxval = 20000;
	queue<int> myq;
	while (true) {		
		fill(g_prev.begin(), g_prev.end(), -1);
		myq.push(g_S);
		while (!myq.empty() && g_prev[g_T] == -1) {
			current = myq.front();
			myq.pop();			
			for(int next : g_graph[current]) {
				if (g_prev[next] != -1) continue; // 이게 현재 탐색에서 이미 갔던 곳으로 가는 것을 막아주는 역할을 한다.
															 // 다음 번 탐색에서는 다시 초기화 된다.
				if (g_flow[current][next].capacity - g_flow[current][next].flow > 0) { // 더 흘릴 수 있는 flow가 남은 간선을 찾는다.
					g_prev[next] = current;
					myq.push(next);					
				}
			}
		}
		while (!myq.empty()) myq.pop(); // clear the queue
		// flow update!
		if (g_prev[g_T] == -1) break; // '출발 -> 목적지'까지 모든 경로 탐색하고 더 탐색할 필요 없을 경우이다!
		int minFlow = maxval;
		for (int i = g_T; i != g_S; i = g_prev[i]) { // sink -> source까지 역으로 거슬러 온다.
			minFlow = min(minFlow, g_flow[g_prev[i]][i].capacity - g_flow[g_prev[i]][i].flow);
		}
		for (int i = g_T; i != g_S; i = g_prev[i]) {
			g_flow[g_prev[i]][i].flow += minFlow;
			g_flow[i][g_prev[i]].flow -= minFlow; // 알고리즘 특성 상 역방향 flow 고려			
		}
		g_maxFlow += minFlow;
	}
}

int main()
{
	FAST;

	int n, p;
	cin >> n >> p;
	g_N = 2*n;
	g_flow.resize(2*n + 1, vector<vertex>(2*n + 1, { 0, 0 }));
	g_prev.resize(2*n + 1, -1);
	g_graph.resize(2*n + 1);
	
	// 정점 v -> v'의 방향성 간선을 만든다.(v(2*i-1) -> v'(2*i))
	for (int i = 1; i < n + 1; i++) {
		g_flow[2 * i - 1][2 * i].capacity++;
		g_graph[2 * i - 1].push_back(2 * i);
		g_graph[2 * i].push_back(2 * i - 1); // V -> V'에서 flow는 단뱡향이라도 그래프 진행자체는 양방향이 맞다. 이 정점을 통해 다른 정점으로 갈 수 있어야 한다.
	}
	g_S = 1*2;
	g_T = 2*2 - 1;
	int from, to;
	for (int i = 0; i < p; i++) {
		cin >> from >> to;
		g_flow[2 * from][2 * to - 1].capacity++; // 간선 중복방문이 안되기 때문에 간선의 capacity는 1로 둔다
		g_flow[2 * to][2 * from - 1].capacity++; // 양방향이라 역방향에도 capacity값을 준다.		
		g_graph[2 * from].push_back(2 * to - 1); // flow와 달리 그래프 간선 만들 때 주의 필요(연결된 모든 방향이 양방향)
		g_graph[2 * to - 1].push_back(2 * from);
		g_graph[2 * to].push_back(2 * from - 1);
		g_graph[2 * from - 1].push_back(2 * to);
	}	
	edmond_karp(); // edmonds-karp algorithm
	cout << g_maxFlow << "\n";
}