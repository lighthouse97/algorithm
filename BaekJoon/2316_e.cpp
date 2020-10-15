// 2316_e.cpp
// ���� �պ��ϱ� 2
// ���� 2316���� g_graph�� g_flow�� �ϳ��� ��ġ�� edge��� ����ü�� �ʿ��� ������ �� ���Ƴ־Ƽ� �ҽ���
// �� �� ����ȭ ���״�.
// ����ȭ �������� 12ms�� �ð��� �� �ɷȴ�.
// ���� 8ms -> ����ȭ �� 12ms
// �־��� �������� ����, ������ ������ ���� �Ը� �̻��� �Ǿ�� edge����ü�� ����ȭ��Ų�� �� ���� �� ����.

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
	int to;
	int capacity;
	int rev; // �����(to)���� ��(from)�� ���° vector ���������� ���� index�����̴�.
	int flow;
	edge(int t, int c, int r) : to(t), capacity(c), rev(r), flow(0) {}
};

struct pre {
	int v; // �ڽ��� previous ����
	int index; // �ڽ��� previous �������� �ڽ��� index. // vector �����̶� ������ �ʿ��ϴ�.
	pre(int v, int i) : v(v), index(i) {}
};

vector<vector<edge>> g_graph;
vector<pre> g_prev;
int g_S = 0, g_T = 0, g_N = 0; // start, sink(terminal), number of vertex
int g_maxFlow = 0; // �ִ� ����
const int g_INF = 987654321;

void edmond_karp()
{
	int current;	
	queue<int> myq;
	while (true) {
		fill(g_prev.begin(), g_prev.end(), pre(-1, -1));
		myq.push(g_S);
		while (!myq.empty() && g_prev[g_T].v == -1) {
			current = myq.front();
			myq.pop();
			for (int i = 0; i < (int)g_graph[current].size(); i++) {
				edge next = g_graph[current][i];
				if (g_prev[next.to].v != -1) continue; // �̰� ���� Ž������ �̹� ���� ������ ���� ���� �����ִ� ������ �Ѵ�.
															 // ���� �� Ž�������� �ٽ� �ʱ�ȭ �ȴ�.
				if (next.capacity - next.flow > 0) { // �� �긱 �� �ִ� flow�� ���� ������ ã�´�.
					g_prev[next.to].v = current;
					g_prev[next.to].index = i;
					myq.push(next.to);
				}
			}
		}
		while (!myq.empty()) myq.pop(); // clear the queue
		// flow update!
		if (g_prev[g_T].v == -1) break; // '��� -> ������'���� ��� ��� Ž���ϰ� �� Ž���� �ʿ� ���� ����̴�!		
		for (int i = g_T; i != g_S; i = g_prev[i].v) { // sink -> source���� ������ �Ž��� �´�.
			edge& e = g_graph[g_prev[i].v][g_prev[i].index];
			e.flow += 1;
			g_graph[e.to][e.rev].flow -= 1; // // �˰��� Ư�� �� ������ flow ���			
		}		
		g_maxFlow += 1;
	}
}

int main()
{
	FAST;

	int n, p;
	cin >> n >> p;
	g_N = 2 * n;
	g_graph.resize(2 * n + 1);
	g_prev.resize(2 * n + 1, { -1, -1 });
	
	// ���� v -> v'�� ���⼺ ������ �����.(v(2*i-1) -> v'(2*i))
	for (int i = 1; i < n + 1; i++) {	
		g_graph[2 * i - 1].push_back(edge(2 * i, 1, g_graph[2 * i].size()));
		g_graph[2 * i].push_back(edge(2 * i - 1, 0, g_graph[2 * i - 1].size() - 1)); // V -> V'���� flow�� �ܓ����̶� �׷��� ������ü�� ������� �´�. �� ������ ���� �ٸ� �������� �� �� �־�� �Ѵ�.
	}
	g_S = 1 * 2;
	g_T = 2 * 2 - 1;
	int from, to;
	for (int i = 0; i < p; i++) {
		cin >> from >> to;						
		g_graph[2 * from].push_back(edge(2 * to - 1, 1, g_graph[2 * to - 1].size())); // ���� �ߺ��湮�� �ȵǱ� ������ ������ capacity�� 1�� �д�
		g_graph[2 * to - 1].push_back(edge(2 * from, 0, g_graph[2 * from].size() - 1)); // ������ flow
		g_graph[2 * to].push_back(edge(2 * from - 1, 1, g_graph[2 * from - 1].size())); 
		g_graph[2 * from - 1].push_back(edge(2 * to, 0, g_graph[2 * to].size() - 1)); // ������ flow
	}
	edmond_karp(); // edmonds-karp algorithm
	cout << g_maxFlow << "\n";
}