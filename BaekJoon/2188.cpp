// 2188.cpp
// ��� ����
// �������� �̺� ��Ī(Bipartite matching)�����̴�.
// ����� �͵� ���� '11375 ������ȣ' ������ ���� ���� ���� �״�� �����ؼ� Ǯ�� �ȴ�.
// ���ѽð� 2�� �� 4ms(2,156KB)�� �ҿ�Ǿ���.
// ������� 1352/2406�� ���� 56.19%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
//#include <list>
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
	int N, M;
	cin >> N >> M;
	g_graph.resize(N + 1);
	g_visited.resize(M + 1, false);
	g_matched.resize(M + 1, 0);

	int cnt, place;
	for (int i = 1; i < N + 1; i++) { // �׷��� ���� �Է�
		cin >> cnt;
		for (int j = 0; j < cnt; j++) {
			cin >> place;
			g_graph[i].push_back(place);
		}
	}

	int answer = 0;
	for (int i = 1; i < N + 1; i++) { // ��Ī(matching)
		if (dfs(i)) answer++;
		g_visited = vector<bool>(M + 1, false);
	}
	cout << answer << "\n";
}