// 1005.cpp
// ACM Craft
// ���� ������ �����ϴ� �����̴�.
// �̷� ������ ���̵� �绡�� �����ؾ� �ϴµ� ���� �����ϰ� ���̵�� �����ϴµ� �ð��� �ξ�ð� �ɷȴ�.
// ���� ���ķ� ���� �����鼭 �� ������ ���� �ð��� �����ϴٰ� Ư�� ������ �����ð���
// �������� �� �� ū �� �ϳ��� �����Ѵ�.
// ���� ������ ������ ��ǥ ������ ���� �ð��� ����ϸ� �ȴ�! -> ���������ϰ� �� �� ���� �̷��� �ϸ� �����ϴ�!!!
// �׷���, �ݵ�� 1������ �����ؾ� �Ѵٴ� ��Ģ�� ��𿡵� ����! �������� �ް��ȴµ�,
// �� ���� ����ؾ� �Ѵ�. ���� ������� �ʾƼ� �ѹ� Ʋ�ȴ�!!!
// ���ѽð� 1�� �� 160ms(2792KB)�� �ҿ�Ǿ���.
// ������� 99/3401�� ���� 2.91%�� rank�Ǿ���.

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
#include <queue> // queue, priority_queue

using namespace std;

int g_N, g_goal;
vector<vector<int>> g_graph;
vector<int> g_degree;
vector<vector<int>> g_cost;

int topological_sort()
{
	queue<int> myq;
	int pick;
	for (int i = 1; i <= g_N; i++) {
		if (g_degree[i] == 0) {
			g_cost[i][1] = g_cost[i][0];
			myq.push(i);
		}
	}
	while (!myq.empty()) {
		pick = myq.front();
		myq.pop();
		if (pick == g_goal) break;
		for (int x : g_graph[pick]) {
			g_cost[x][1] = max(g_cost[x][1], g_cost[pick][1] + g_cost[x][0]);
			g_degree[x]--;
			if (g_degree[x] == 0)
				myq.push(x);
		}
	}
	return g_cost[g_goal][1];
}

void do_test()
{
	int K, x, y, result;
	cin >> g_N >> K;
	g_graph.resize(g_N + 1);
	g_degree.resize(g_N + 1, 0);
	g_cost.resize(g_N + 1, vector<int>(2, 0));
	// cost �Է�
	for (int i = 1; i <= g_N; i++) 
		cin >> g_cost[i][0];
	// ��Ģ �Է�
	for (int i = 1; i <= K; i++) {
		cin >> x >> y;
		g_graph[x].push_back(y);
		g_degree[y]++;
	}
	// ��ǥ unit �Է�
	cin >> g_goal;
	result = topological_sort();
	cout << result << "\n";
	
	g_graph.clear();
	g_degree.clear();
	g_cost.clear();
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
		do_test();
}