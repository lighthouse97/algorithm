// 2458_1.cpp
// Ű ����
// Floyd-Warshall �˰������� Ǫ�� �����̳� dfs�� �̿��ϸ� �ξ� �� ���� Ǯ����.
// ������ dfs�� ������ dfs 2������ �̿��Ͽ���.
// ����ð��� Ȯ���� �پ�����.
// 132ms(3,080KB) -> 68ms(3,340KB) �� ������ ���Ǿ���.
// ������� 368/2826�� ���� 13.02%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
//#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int g_N;
vector<vector<int>> g_graph;
vector<vector<int>> g_igraph; // ������ �׷���
vector<bool> g_visit;
int g_cnt, g_icnt;

void dfs(int r)
{
	g_visit[r] = true;
	g_cnt++;
	for (int x : g_graph[r]) {
		if (!g_visit[x]) dfs(x);
	}
}

void idfs(int r) // ���������� Ž��
{
	g_visit[r] = true;
	g_icnt++;
	for (int x : g_igraph[r]) {
		if (!g_visit[x]) idfs(x);
	}
}

int main() {
	FAST;
	int m;
	cin >> g_N >> m;
	g_graph.resize(g_N + 1);
	g_igraph.resize(g_N + 1);
	g_visit.resize(g_N + 1, 0);
	int a, b;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		g_graph[a].push_back(b);
		g_igraph[b].push_back(a);
	}
	int answer = 0;;
	for (int i = 1; i < g_N + 1; i++) {
		g_cnt = g_icnt = 0;
		g_visit = vector<bool>(g_N + 1, false);
		dfs(i);
		g_visit = vector<bool>(g_N + 1, false);
		idfs(i);
		if (g_cnt + g_icnt - 1 == g_N) answer++;
	}
	cout << answer << "\n";
}