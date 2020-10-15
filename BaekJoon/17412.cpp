// 17412.cpp
// ���� �պ��ϱ�1
// ���� �⺻���� Network Flow�����̴�.
// �� �־��� �׷������� ��������� ���������� maximum flow, �� ���� ū ������ ���ϴ� �����̴�.
// �� ������ Ǯ������ ��ǥ���� �˰������ �ִµ�,
// �� �߿��� BFS�� Ȱ���� Edmonds-Karp algorithm�� ����Ͽ� �����Ͽ���.�̴� Ford-Fulkerson algorithm�� �⺻���� BFS�� ������ ���̴�.
// �� �� Ǯ���!
// ������ ��!
// �ܹ����̶� ������ �����̳� �������� capacity�� ����� �Ѵ�.(����� ������ ���� �ִ�. ����� 0�� �ȴ�. ���� ����� Ʋ����.)
// �˰��� Ư���� �����⿡ ���� flow ���� �׻� �����ؾ� ����� ���� ã�ư� �� �ִ�.
// network flow�� �� �������� ���� ���¿��� ����� ������ Ǫ�� �������� �ð��� ���� ��ƸԾ���!!!
// ���ѽð� 2�� �� 4ms(3,308KB)�� �ҿ�Ǿ���.
// ������� 60/206�� ���� 29.12%�� rank�Ǿ���.

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
int g_S = 0, g_T = 0, g_N = 0; // start, sink(terminal), number of vertex
int g_maxFlow = 0; // �ִ� ����

void edmond_karp()
{
	int current;
	int maxval = 10000;
	queue<int> myq;
	while (true) {
		//g_prev = vector<int>(g_prev.size(), -1);
		fill(g_prev.begin(), g_prev.end(), -1);		
		myq.push(g_S);
		while (!myq.empty() && g_prev[g_T] == -1) {
			current = myq.front();
			myq.pop();			
		   for(int next = 1; next < g_N + 1; next++) {				
				if (g_prev[next] != -1) continue; // �̰� ���� Ž������ �̹� ���� ������ ���� ���� �����ִ� ������ �Ѵ�.
				                                  // ���� �� Ž�������� �ٽ� �ʱ�ȭ �ȴ�.
				if (g_flow[current][next].capacity - g_flow[current][next].flow > 0) { // �� �긱 �� �ִ� flow�� ���� ������ ã�´�.
					g_prev[next] = current;
					myq.push(next);					
				}
			}
		}
		while (!myq.empty()) myq.pop(); // queue clear
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
	g_N = n;
	g_flow.resize(n + 1, vector<vertex>(n + 1, { 0, 0 }));
	g_prev.resize(n + 1, -1);

	g_S = 1;
	g_T = 2;
	int from, to;
	for (int i = 0; i < p; i++) {
		cin >> from >> to;				
		g_flow[from][to].capacity++; // ���� �ߺ��湮�� �ȵǱ� ������ ������ capacity�� 1�� �д�		
	}
	edmond_karp(); // edmonds-karp algorithm
	cout << g_maxFlow << "\n";
}