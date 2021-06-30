// 6086.cpp
// 최대 유량
// Olympiad > USA Computing Olympiad > 2008-2009 Season > USACO January 2009 Contest > Silver 2번
// 정점 사이에 간선이 양방향 또는 여러 개 있는 경우까지 고려한 표준 코드를 적용하였다.
// g_graph에 간선 정보 및 flow, capacity 모두 다 때려넣고 구현한 방식이다.
// 기존 방식 대비 수행 시간은 그대로이고 소요 메모리 사이즈는 약간 줄었다.
// 이 방식으로 구현하면 같은 두 정점 사이에 간선이 여러 개 생겨도 생긴 만큼 중복해서 연결되기 때문에,
// 기존 방식 처럼 용량(capacity)을 누적할 필요가 없고 그럴 고민을 할 필요도 없다!!!
// 제한시간 1초 중 0ms(2,156KB)가 소요되었다.
// 맞은사람 1080/1430로 상위 75.52%에 rank되었다.

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
const int MAXN = 52;

struct edge {
	int to, flow, capa, revi;
	edge() : to(-1), flow(0), capa(0), revi(-1) {}
	edge(int t, int f, int c, int r) : to(t), flow(f), capa(c), revi(r) {}
	bool space() { return capa > flow; }
};

vector<vector<edge>> g_graph;
int g_N, g_S, g_T; // source, sink, n count
int g_maxFlow = 0;

void addEdge(int from, int to, int flow, int capa)
{
	g_graph[from].push_back({ to, flow, capa, (int)g_graph[to].size() });
	g_graph[to].push_back({ from, 0, 0, (int)g_graph[from].size() - 1 });
}

void edmond_karp()
{
	struct vt {
		int num, index;
		vt(int n, int i) : num(n), index(i) {}
	};
	vector<vt> prev;
	while (true) {
		prev.assign(g_N + 1, { -1, -1 }); // 시작하기 전에 prev를 모두 -1로 초기화시킨다.
		queue<int> myq;
		myq.push(g_S); // source -> queue
		prev[g_S].num = g_S;
		int cur;
		while (!myq.empty()) {
			cur = myq.front();
			myq.pop();
			for (int i = 0; i < g_graph[cur].size(); i++) {
				edge& next = g_graph[cur][i];
				if (prev[next.to].num == -1 && next.space()) { // 이전에 방문하지 않아야 하고, 더 흘릴 flow가 있을 경우, 다음 정점으로 진행.
					prev[next.to].num = cur;
					prev[next.to].index = i;
					myq.push(next.to);
				}
			}
			if (prev[g_T].num != -1) break; // source -> sink까지 경로 찾았음!
		}
		if (prev[g_T].num == -1) break; // source -> sink 까지 흐름이 없을 경우 flow를 다 찾은 경우이므로 더 찾을 필요 없다.

		int minFlow = MAXVAL;
		for (int i = g_T; i != g_S; i = prev[i].num) { // 잔여(residual)유량이 가장 작은 것으로만 통과 가능하다
			edge& link = g_graph[prev[i].num][prev[i].index];
			minFlow = min(minFlow, link.capa - link.flow);
		}
		for (int i = g_T; i != g_S; i = prev[i].num) {
			edge& link = g_graph[prev[i].num][prev[i].index];
			link.flow += minFlow; // 정방향은 flow 더해주고
			g_graph[link.to][link.revi].flow -= minFlow; // 역방향은 flow 빼준다
		}
		g_maxFlow += minFlow;
	}
}

int getIndex(char a)
{
	int index;
	if (a >= 'a') { // 'a' ~ 'z'
		index = a - 'a';
		index += 26;
	}
	else // 'A' ~ 'Z'
		index = a - 'A';

	return index;
}

int main()
{
	FAST;
	int N;
	cin >> N;
	g_S = 0; g_T = 25; g_N = 52; // 26 + 26
	g_graph.resize(g_N);
	char a, b;
	int c, from, to;
	for (int i = 0; i < N; i++) {
		cin >> a >> b >> c;
		from = getIndex(a); // 알파벳을 인덱스로 변환한다.
		to = getIndex(b);
		addEdge(from, to, 0, c);
		addEdge(to, from, 0, c); // 양방향 고려
	}
	edmond_karp();
	cout << g_maxFlow << "\n";
}