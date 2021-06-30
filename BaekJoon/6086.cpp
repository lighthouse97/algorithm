// 6086.cpp
// �ִ� ����
// Olympiad > USA Computing Olympiad > 2008-2009 Season > USACO January 2009 Contest > Silver 2��
// ���� ���̿� ������ ����� �Ǵ� ���� �� �ִ� ������ ����� ǥ�� �ڵ带 �����Ͽ���.
// g_graph�� ���� ���� �� flow, capacity ��� �� �����ְ� ������ ����̴�.
// ���� ��� ��� ���� �ð��� �״���̰� �ҿ� �޸� ������� �ణ �پ���.
// �� ������� �����ϸ� ���� �� ���� ���̿� ������ ���� �� ���ܵ� ���� ��ŭ �ߺ��ؼ� ����Ǳ� ������,
// ���� ��� ó�� �뷮(capacity)�� ������ �ʿ䰡 ���� �׷� ����� �� �ʿ䵵 ����!!!
// ���ѽð� 1�� �� 0ms(2,156KB)�� �ҿ�Ǿ���.
// ������� 1080/1430�� ���� 75.52%�� rank�Ǿ���.

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
		prev.assign(g_N + 1, { -1, -1 }); // �����ϱ� ���� prev�� ��� -1�� �ʱ�ȭ��Ų��.
		queue<int> myq;
		myq.push(g_S); // source -> queue
		prev[g_S].num = g_S;
		int cur;
		while (!myq.empty()) {
			cur = myq.front();
			myq.pop();
			for (int i = 0; i < g_graph[cur].size(); i++) {
				edge& next = g_graph[cur][i];
				if (prev[next.to].num == -1 && next.space()) { // ������ �湮���� �ʾƾ� �ϰ�, �� �긱 flow�� ���� ���, ���� �������� ����.
					prev[next.to].num = cur;
					prev[next.to].index = i;
					myq.push(next.to);
				}
			}
			if (prev[g_T].num != -1) break; // source -> sink���� ��� ã����!
		}
		if (prev[g_T].num == -1) break; // source -> sink ���� �帧�� ���� ��� flow�� �� ã�� ����̹Ƿ� �� ã�� �ʿ� ����.

		int minFlow = MAXVAL;
		for (int i = g_T; i != g_S; i = prev[i].num) { // �ܿ�(residual)������ ���� ���� �����θ� ��� �����ϴ�
			edge& link = g_graph[prev[i].num][prev[i].index];
			minFlow = min(minFlow, link.capa - link.flow);
		}
		for (int i = g_T; i != g_S; i = prev[i].num) {
			edge& link = g_graph[prev[i].num][prev[i].index];
			link.flow += minFlow; // �������� flow �����ְ�
			g_graph[link.to][link.revi].flow -= minFlow; // �������� flow ���ش�
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
		from = getIndex(a); // ���ĺ��� �ε����� ��ȯ�Ѵ�.
		to = getIndex(b);
		addEdge(from, to, 0, c);
		addEdge(to, from, 0, c); // ����� ���
	}
	edmond_karp();
	cout << g_maxFlow << "\n";
}