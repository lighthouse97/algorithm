// 1867.cpp
// ������ ����
// �� ������ �� �Ǵ� �� ��������
// ��� ������ ������ �� �ִ� �ּ��� ������ ������ ���ϸ� �ȴ�.
// "��� ������ ������ �� �ִ� �ּ��� ������ ����"��� ������ ����
// "�ּ� ���ؽ� Ŀ��"�� ������ ���ϴ� �����̰� �̴�
// ����� ������ ���� �̺� �׷������� �ִ� ��Ī ������ ���ϸ� �ȴ�.
// �� �� -> ���� �̺� �׷����� ����� ���⼭ �ִ� ��Ī�� ���ϸ� �ִ� ��Ī�� �ش�Ǵ�
// ������ �� �Ǵ� �� �������� ��� ����(���� ��ġ)�� �����ų �� �ִ�.
// ���� �������� �ִ� ��Ī�� �ش��ϴ� ���� (1,1), (2,2)�� �ȴµ�,
// (1, 1)���� ���� ������ (1, 3)�� ����ǰ�
// (2, 2)���� ���� ���� (3, 2)�� ������ �Ǿ� ��� ������ ������ �ȴ�.
// Olympiad > USA Computing Olympiad > 2005-2006 Season > USACO November 2005 Contest > Gold 1��
// ���ѽð� 2�� �� 0ms(2,120KB)�� �ҿ�Ǿ���.
// ������� 317/640�� ���� 49.53%�� rank�Ǿ���.

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

	int n, k;
	int answer = 0;

	cin >> n >> k;
	g_graph.resize(n + 1);
	g_visited.resize(n + 1, false);
	g_matched.resize(n + 1, false);

	int a, b;
	for (int i = 0; i < k; i++) {
		cin >> a >> b;
		g_graph[a].push_back(b);
	}
	for (int i = 1; i < n + 1; i++) {
		g_visited = vector<bool>(n + 1, false);
		if (dfs(i)) answer++;
	}
	cout << answer << "\n";
}