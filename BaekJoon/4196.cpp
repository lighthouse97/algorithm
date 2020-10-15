// 4196.cpp
// ���̳�
// �������� SCC ������ �ƴϰ� SCC�� ���� ����� �����ϴ� �����̴�.
// SCC ���� �� ó�� dfs Ž���ϸ鼭 stack�� �ִ� ���� ����.
// �� ������ Ž���� ���� �ʰ� stack�� ���� �� tree�� root�� stack�� ����������
// ����. �� ������ �̿��Ͽ� stack�� top����, �� tree�� root�� �켱����
// dfs Ž���Ͽ� dfs�� ������ ������ŭ tree�� ������ ������ �� tree�� ������
// ������ �ȴ�.
// ���ѽð� 1�� �� 128ms(12456KB)�� �ҿ�Ǿ���.
// ������� 27/479�� ���� 5.63%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <functional> // less, greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_graph;
vector<bool> g_visited;
stack<int> g_st;
int g_cnt = 0;

void dfs(int current, int type)
{
	g_visited[current] = true;
	for (int next : g_graph[current]) {
		if (g_visited[next]) continue;
		dfs(next, type);
	}
	if (!type) g_st.push(current);
}

void do_test()
{
	int n, m, x, y, num;
	cin >> n >> m;
	g_graph.resize(n + 1);
	g_visited.resize(n + 1, false);
	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		g_graph[x].push_back(y);
	}
	for (int i = 1; i <= n; i++) {
		if (!g_visited[i])
			dfs(i, 0);
	}
	g_visited = vector<bool>(n + 1, false);
	while (!g_st.empty()) {
		num = g_st.top();
		g_st.pop();
		if (g_visited[num]) continue;
		dfs(num, 1);
		g_cnt++;
	}
	cout << g_cnt << "\n";
	g_graph.clear();
	g_visited.clear();
	g_cnt = 0;
}

int main()
{
	FAST

	int t;
	cin >> t;
	for (int i = 0; i < t; i++)
		do_test();
}