// 2252.cpp
// �� �����
// ���� ����(topological sort)�� �̿��ϴ� �����̴�.
// ���ͳݿ��� ���� ���� ������ �ڷ� ã�ƺ��� �����ؼ� �����Ͽ���.
// queue�� �̿��ϴ� ����� dfs�� �̿��ϴ� ����� �ִµ�
// queue�� �̿��ϴ� ����� ����Ͽ���.
// ���ѽð� 2�� �� 28ms(3904KB)�� �ҿ�Ǿ���.
// ������� 24/4132�� ���� 0.58%�� rank�Ǿ���.

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
#include <queue> // queue, priority_queue

using namespace std;

int g_N, g_M;
vector<vector<int>> g_graph;
vector<int> g_degree;

void topological_sort()
{
	queue<int> myq;
	int pick;
	for (int i = 1; i <= g_N; i++) {
		if (g_degree[i] == 0)
			myq.push(i);
	}
	while (!myq.empty()) {
		pick = myq.front();
		myq.pop();
		cout << pick << " ";
		for (int x : g_graph[pick]) {
			g_degree[x]--;
			if (g_degree[x] == 0)
				myq.push(x);
		}
	}
	cout << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int a, b;
	cin >> g_N >> g_M;
	g_graph.resize(g_N + 1);
	g_degree.resize(g_N + 1, 0);
	for (int i = 0; i < g_M; i++) {
		cin >> a >> b;
		g_graph[a].push_back(b);
		g_degree[b]++;
	}
	topological_sort();
}
