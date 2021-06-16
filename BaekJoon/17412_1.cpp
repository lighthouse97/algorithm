// 17412_1.cpp
// ���� �պ��ϱ� 1
// Network Flow, Edmond-Karp algorithm
// Edmond-Karp �˰��� ���뿡 �־ ������ ������ �ܹ����̳� ������̳Ŀ� ����
// ���� �ٸ��� �����ߴµ�, 
// ������ ������ ��Ī���� �̿��Ͽ� ������ ������ Ž���� �ܹ����̳� ������̳� �������� ������ �ǹǷ�, 
// g_graph�� ��������� �������� ������ �ϰ�, 
// g_flow�� �������� capacity�� ������� c(c > 0)��, �ܹ����� 0���� �����Ѵ�.
// �̷��� ������ ���Ͻ��Ѽ� �ҽ��� �����ϵ��� �Ѵ�.(�ణ�� ����ð� ���ش� ������ ũ�� ����ġ �ʰڴ�!)
// ���ѽð� 2�� �� 8ms(3,348KB)�� �ҿ�Ǿ���.
// ������� 320/496�� ���� 64.51%�� rank�Ǿ���. 

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

const int MAXVAL = 10000;
struct vertex {
	int flo, cap;
	vertex() : flo(0), cap(0) {}
	vertex(int f, int c) : flo(f), cap(c) {}
};

vector<vector<int>> g_graph;
vector<vector<vertex>> g_flow;
vector<int> g_prev;
int g_N, g_S, g_T; // source, sink, n count
int g_maxFlow = 0;

void edmond_karp()
{
	while (true) {
		g_prev.assign(g_N + 1, -1); // �����ϱ� ���� prev�� ��� -1�� �ʱ�ȭ��Ų��.
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

int main()
{
	int N, P;
	cin >> N >> P;
	g_N = N;
	g_graph.resize(g_N + 1);
	g_flow.resize(g_N + 1, vector<vertex>(g_N + 1, { 0, 0 }));
	g_prev.resize(g_N + 1, -1);
	int a, b;
	for (int i = 1; i < P + 1; i++) {
		cin >> a >> b;
		g_graph[a].push_back(b);
		g_graph[b].push_back(a);
		g_flow[a][b].cap = 1;
	}
	g_S = 1; g_T = 2;
	edmond_karp();
	cout << g_maxFlow << "\n";
}