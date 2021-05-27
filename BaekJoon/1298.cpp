// 1298.cpp
// ��Ʈ���� ������ ã�Ƽ�
// �� ������ ���� �������� �̺� Ž��(�ִ� Ž��) �����̴�.
// �׳� N, M ������ ��Ī�ϸ� �ȴ�.
// ���ѽð� 2�� �� 0ms(2,156KB)�� �ҿ�Ǿ���.
// ������� 801/1157�� ���� 69.23%�� rank�Ǿ���.

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
		if (g_visited[to]) continue;
		else g_visited[to] = true;
		if (g_matched[to] == 0 || dfs(g_matched[to])) {
			g_matched[to] = from;
			return true;
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
	g_visited.resize(N + 1, false);
	g_matched.resize(N + 1, 0);

	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		g_graph[a].push_back(b);
	}

	int answer = 0;
	for (int i = 1; i < N + 1; i++) {
		g_visited = vector<bool>(N + 1, false);
		if (dfs(i)) answer++;
	}
	cout << answer << "\n";
}