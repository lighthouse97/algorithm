// 6086.cpp
// �ִ� ����
// Olympiad > USA Computing Olympiad > 2008-2009 Season > USACO January 2009 Contest > Silver 2��
// �������� ��Ʈ��ũ �÷ο� �����̴�.
// Edmond-karp �˰���� Dinic �˰��� �� Edmond-Karp �˰����� ����Ͽ���.
// ġ������ �Ǽ��� �־���!!!
// �������� �������� ���ķ� ��ø�Ǹ� �뷮�� ��ĥ �� �ִٰ� �Ͽ���.
// �̸��� ���� ����� �������� ������ �� �� �ְ� �̷� ���� �� ������ �������� �뷮�� ���ľ� �Ѵ�.
// ���� ����� capacity�� ������ �� = ���� �Ҵ��ϸ� �ȵǰ�, += ���� �������Ѿ� �Ѵ�!!!
// �̰��� ���� ������ WA�� �¾Ҵ�!!!
// �������� �� ������ �ٸ��Ƿ� ������ �� �������� �Ѵ�.(capacity�� = ����, += ����...)
// ���ѽð� 1�� �� 0ms(2,160KB)�� �ҿ�Ǿ���.
// ������� 1074/1414�� ���� 75.94%�� rank�Ǿ���.

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
		g_prev.assign(MAXN, -1); // �����ϱ� ���� prev�� ��� -1�� �ʱ�ȭ��Ų��.
		queue<int> myq;
		myq.push(g_S); // source -> queue
		g_prev[g_S] = g_S;
		int cur;
		while (!myq.empty()) {
			cur = myq.front();
			myq.pop();
			for (int next : g_graph[cur]) { // ������ �湮���� �ʾƾ� �ϰ�, �� �긱 flow�� ���� ���, ���� �������� ����.
				if (g_prev[next] == -1 && g_flow[cur][next].cap - g_flow[cur][next].flo > 0) {
					g_prev[next] = cur;
					myq.push(next);
				}
			}
			if (g_prev[g_T] != -1) break; // source -> sink���� ��� ã����!
		}
		if (g_prev[g_T] == -1) break; // source -> sink ���� �帧�� ���� ��� flow�� �� ã�� ����̹Ƿ� �� ã�� �ʿ� ����.

		int minFlow = MAXVAL;
		for (int i = g_T; i != g_S; i = g_prev[i]) // �ܿ�(residual)������ ���� ���� �����θ� ��� �����ϴ�
			minFlow = min(minFlow, g_flow[g_prev[i]][i].cap - g_flow[g_prev[i]][i].flo);
		for (int i = g_T; i != g_S; i = g_prev[i]) {
			g_flow[g_prev[i]][i].flo += minFlow; // �������� flow �����ְ�
			g_flow[i][g_prev[i]].flo -= minFlow; // �������� flow ���ش�
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
	g_graph.resize(MAXN); // �빮�� 26 + �ҹ��� 26
	g_flow.resize(MAXN, vector<vertex>(MAXN, { 0, 0 }));
	g_prev.resize(MAXN, -1);
	char a, b;
	int c, from, to;
	for (int i = 0; i < N; i++) {
		cin >> a >> b >> c;
		from = getIndex(a); // ���ĺ��� �ε����� ��ȯ�Ѵ�.
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