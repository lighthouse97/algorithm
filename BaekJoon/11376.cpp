// 11376.cpp
// ������ȣ2
// �̺� ��Ī ���� ����.
// �� ������ ����, ������ �� ������ ���� dfs�� 2�� ������ �� �� ����!
// ���ѽð� 4�� �� 1348ms(6,096KB)�� �ҿ�Ǿ���.
// ������� 570/1171�� ���� 48.67%�� rank�Ǿ���.
// ���� Ǭ ���� �������� �ش���� ��� Hopcroft-Karp Algorithm(Dinic alogrithm�� ����)�� ����ؼ� �����Ͽ���.
// ���߿� �����ؼ� ������ �� ���� �ڴ�!!!

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs, hypot, round
#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_graph;
vector<bool> g_visited;
vector<int> g_matched;
int g_count = 0;

bool dfs(int from)
{
	for (int to : g_graph[from]) {
		if (!g_visited[to] && !g_matched[to]) {
			g_visited[to] = true;
			g_matched[to] = from;
			return true;
		}
	}
	for (int to : g_graph[from]) {
		if (!g_visited[to]) {
			g_visited[to] = true;
			if (!g_matched[to] || dfs(g_matched[to])) {
				g_matched[to] = from;
				return true;
			}
		}
	}
	return false;
}

int main()
{
	FAST;

	int n, m;
	cin >> n >> m;
	g_graph.resize(n + 1);
	g_visited.resize(m + 1, false);
	g_matched.resize(m + 1, 0);

	int cnt, job;
	for (int i = 1; i < n + 1; i++) {
		cin >> cnt;
		for (int j = 0; j < cnt; j++) {
			cin >> job;
			g_graph[i].push_back(job);
		}
	}

	for (int i = 1; i < n + 1; i++) {
		g_visited = vector<bool>(m + 1, false);
		for (int j = 0; j < 2; j++)
			if (dfs(i)) g_count++;
	}	
	cout << g_count << "\n";
}
