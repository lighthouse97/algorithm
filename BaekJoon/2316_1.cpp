// 2316.cpp
// ���� �պ��ϱ� 2
// '���� �պ��ϱ�1' �� ���� �ִ� ������ ���Ѵ� �����̴�.
// �� �������� 1) ������ ������̰� 2) ������ �ѹ��� ������ �� �ִ� �̴�.
// 1) ������ ����� ������ ��������� �� �� �ִٴ� ������ ��� ���ϴ� ���� ����� �� ��
//    ��� �������� �������� ���Ĵ� �ܹ���� �����ϴ�.
//    ���� �ܹ���� �����ϰ� ���� ������ �뷮(capacity)�� ��������� �ָ� �ȴ�.
// 2) ������ �ѹ��� �������ٴ� ���� �ణ�� �ⱳ�� �ʿ��ѵ�,
//    ���� 3�̶�� 3'�� �ϳ� �� ����� 3->3'�� �뷮1�� �����ִ� ������ �߰��ϸ� �ȴ�.
//    ���� ���� ������ N�̸� N*2�� ������ ����� ����. (�������� ���)
// ������ ��!!
// from <-> to �� ������, ������ capacity �Է��� �� �����, ������ �����ؾ� �Ѵ�. �ƹ� �������� �����ߴٰ� Ʋ�ȴ�!!!
// ���ѽð� 2�� �� 132ms(7,040KB)�� �ҿ�Ǿ���.
// ������� 420/495�� ���� 84.84%�� rank�Ǿ���.
///
// ����� �׷����� ������ ���� ������ ���󰡼� ���� �ð��� �� �� ����ȭ ��ų �� �ִ�.
// �ܹ��� �׷����� ���������ε� �� �� �־�� �ϱ� ������ ���� �������� �� �� ���⿡ ��� ���� ���� c - f �� �����ؾ� �Ѵ�.
// �׷��� ���鶧 ������ ���� flow����� graph������ �ٸ��ٴ� ���̴�.
// flow�� v->v', v'->u, u'->v �̷��Ը� ���������� �׷����� v<->v', v'<->u, u'<->v ��� ���ῡ�� ����� �����ϴ�.
// ���ѽð� 2�� �� 8ms(7,304KB)�� �ҿ�Ǿ���. (132ms -> 8ms)
// ������� 182/495�� ���� 36.76%�� rank�Ǿ���.
// ���� �и����� �ʰ� ����� �׷����� Ǯ �� visit�迭�� ����Ͽ� �ѹ� �湮�ߴ� ������ üũ�ؼ� Ǯ ���� �ִ�.
// (������ �پ��� �� �� ������ ������ �ʹ�)

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
int g_maxFlow = 0; // �ִ� ����

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
				if (g_prev[next] != -1) continue; // �̰� ���� Ž������ �̹� ���� ������ ���� ���� �����ִ� ������ �Ѵ�.
															 // ���� �� Ž�������� �ٽ� �ʱ�ȭ �ȴ�.
				if (g_flow[current][next].capacity - g_flow[current][next].flow > 0) { // �� �긱 �� �ִ� flow�� ���� ������ ã�´�.
					g_prev[next] = current;
					myq.push(next);					
				}
			}
		}
		while (!myq.empty()) myq.pop(); // clear the queue
		// flow update!
		if (g_prev[g_T] == -1) break; // '��� -> ������'���� ��� ��� Ž���ϰ� �� Ž���� �ʿ� ���� ����̴�!
		int minFlow = maxval;
		for (int i = g_T; i != g_S; i = g_prev[i]) { // sink -> source���� ������ �Ž��� �´�.
			minFlow = min(minFlow, g_flow[g_prev[i]][i].capacity - g_flow[g_prev[i]][i].flow);
		}
		for (int i = g_T; i != g_S; i = g_prev[i]) {
			g_flow[g_prev[i]][i].flow += minFlow;
			g_flow[i][g_prev[i]].flow -= minFlow; // �˰��� Ư�� �� ������ flow ���			
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
	
	// ���� v -> v'�� ���⼺ ������ �����.(v(2*i-1) -> v'(2*i))
	for (int i = 1; i < n + 1; i++) {
		g_flow[2 * i - 1][2 * i].capacity++;
		g_graph[2 * i - 1].push_back(2 * i);
		g_graph[2 * i].push_back(2 * i - 1); // V -> V'���� flow�� �ܓ����̶� �׷��� ������ü�� ������� �´�. �� ������ ���� �ٸ� �������� �� �� �־�� �Ѵ�.
	}
	g_S = 1*2;
	g_T = 2*2 - 1;
	int from, to;
	for (int i = 0; i < p; i++) {
		cin >> from >> to;
		g_flow[2 * from][2 * to - 1].capacity++; // ���� �ߺ��湮�� �ȵǱ� ������ ������ capacity�� 1�� �д�
		g_flow[2 * to][2 * from - 1].capacity++; // ������̶� �����⿡�� capacity���� �ش�.		
		g_graph[2 * from].push_back(2 * to - 1); // flow�� �޸� �׷��� ���� ���� �� ���� �ʿ�(����� ��� ������ �����)
		g_graph[2 * to - 1].push_back(2 * from);
		g_graph[2 * to].push_back(2 * from - 1);
		g_graph[2 * from - 1].push_back(2 * to);
	}	
	edmond_karp(); // edmonds-karp algorithm
	cout << g_maxFlow << "\n";
}