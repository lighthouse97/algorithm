// 2637.cpp
// �峭�� ����
// Olympiad > �ѱ������ø��ǾƵ� > KOI 2000 > �ߵ�� 1��
// ���� �����ε� '1516 ���� ����'�� ���� �׷��� �ణ�� ������ �ʿ��ϴ�.
// ���ѽð� 1�� �� 0ms(2,160KB)�� �ҿ�Ǿ���.
// ������� 584/780�� ���� 74.87%�� rank�Ǿ���.

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
//#include <algorithm> // sort, max, min, copy, swap, unique
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

struct edge {
	int to, quantity;
	edge() : to(), quantity() {}
	edge(int t, int q) : to(t), quantity(q) {}
};

vector<vector<edge>> g_graph;
vector<int> g_degree;
int g_N = 0;
///
vector<vector<int>> g_parts;

void topological_sort()
{
	queue<int> myq;
	for (int i = 1; i < g_N + 1; i++)
		if (g_degree[i] == 0) {
			myq.push(i); g_parts[i][i] = 1;
		}
	int cur;
	while (!myq.empty()) {
		cur = myq.front(); myq.pop();
		for (edge& next : g_graph[cur]) {
			for (int i = 1; i < g_N + 1; i++) { // Ǫǰ�� ���� �ݿ�
				if (g_parts[cur][i])
					g_parts[next.to][i] += (g_parts[cur][i] * next.quantity);
			}
			g_degree[next.to]--;
			if (g_degree[next.to] == 0) myq.push(next.to);
		}
	}
}

int main()
{
	FAST;
	int N, M;
	cin >> N >> M;
	g_graph.resize(N + 1);
	g_degree.resize(N + 1, 0);
	g_parts.resize(N + 1, vector<int>(N + 1, 0));
	g_N = N;
	int x, y, k;
	for (int i = 0; i < M; i++) {
		cin >> x >> y >> k;
		g_graph[y].push_back({ x, k });
		g_degree[x]++;
	}
	topological_sort();
	for (int i = 1; i < N + 1; i++)
		if (g_parts[N][i]) cout << i << " " << g_parts[N][i] << "\n";
}