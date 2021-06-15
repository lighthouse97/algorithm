// 6086.cpp
// 최대 유량
// Olympiad > USA Computing Olympiad > 2008-2009 Season > USACO January 2009 Contest > Silver 2번
// 전형적인 네트워크 플로우 문제이다.
// Edmond-karp 알고리즘과 Dinic 알고리즘 중 Edmond-Karp 알고리즘을 사용하였다.
// 치명적인 실수가 있었다!!!
// 문제에서 파이프가 병렬로 중첩되면 용량을 합칠 수 있다고 하였다.
// 이말은 같은 경로의 파이프가 여러개 올 수 있고 이런 경우는 그 때마다 파이프의 용량을 합쳐야 한다.
// 따라서 경로의 capacity를 적용할 때 = 으로 할당하면 안되고, += 으로 누적시켜야 한다!!!
// 이것을 몰라서 여러번 WA를 맞았다!!!
// 문제마다 이 조건이 다르므로 문제를 잘 따져봐야 한다.(capacity를 = 인지, += 인지...)
// 제한시간 1초 중 0ms(2,160KB)가 소요되었다.
// 맞은사람 1074/1414로 상위 75.94%에 rank되었다.

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
struct vertex {
	int flo, cap;
	vertex() : flo(0), cap(0) {}
	vertex(int f, int c) : flo(f), cap(c) {}
};

vector<vector<int>> g_graph;
vector<vector<vertex>> g_flow;
vector<int> g_prev;
int g_S, g_T; // source, sink, n count
int g_maxFlow = 0;

void edmond_karp()
{
	while (true) {
		g_prev.assign(MAXN, -1); // 시작하기 전에 prev를 모두 -1로 초기화시킨다.
		queue<int> myq;
		myq.push(g_S); // source -> queue
		g_prev[g_S] = g_S;
		int cur;
		while (!myq.empty()) {
			cur = myq.front();
			myq.pop();
			for (int next : g_graph[cur]) { // 이전에 방문하지 않아야 하고, 더 흘릴 flow가 있을 경우, 다음 정점으로 진행.
				if (g_prev[next] == -1 && g_flow[cur][next].cap - g_flow[cur][next].flo > 0) {
					g_prev[next] = cur;
					myq.push(next);
				}
			}
			if (g_prev[g_T] != -1) break; // source -> sink까지 경로 찾았음!
		}
		if (g_prev[g_T] == -1) break; // source -> sink 까지 흐름이 없을 경우 flow를 다 찾은 경우이므로 더 찾을 필요 없다.

		int minFlow = MAXVAL;
		for (int i = g_T; i != g_S; i = g_prev[i]) // 잔여(residual)유량이 가장 작은 것으로만 통과 가능하다
			minFlow = min(minFlow, g_flow[g_prev[i]][i].cap - g_flow[g_prev[i]][i].flo);
		for (int i = g_T; i != g_S; i = g_prev[i]) {
			g_flow[g_prev[i]][i].flo += minFlow; // 정방향은 flow 더해주고
			g_flow[i][g_prev[i]].flo -= minFlow; // 역방향은 flow 빼준다
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

int main() {
	FAST;
	int N;
	cin >> N;
	g_graph.resize(MAXN); // 대문자 26 + 소문자 26
	g_flow.resize(MAXN, vector<vertex>(MAXN, { 0, 0 }));
	g_prev.resize(MAXN, -1);
	char a, b;
	int c, from, to;
	for (int i = 0; i < N; i++) {
		cin >> a >> b >> c;
		from = getIndex(a); // 알파벳을 인덱스로 변환한다.
		to = getIndex(b);
		g_graph[from].push_back(to);
		g_graph[to].push_back(from);
		g_flow[from][to].cap += c;
		g_flow[to][from].cap += c;
	}
	g_S = 0; g_T = 25; // source : 'A', Sink : 'Z'
	edmond_karp();
	cout << g_maxFlow << "\n";
}