// 3295.cpp
// �ܹ��� ��ũ ��Ʈ��ũ
// ICPC > Regionals > Asia Pacific > Korea > Nationwide Internet Competition > Daejeon Nationalwide Internet Competition 2013 H��
// �̺� ��Ī �����ε�, �̺� �׷��� �����ϱ���� ���� �ɷȴ�.
// Ư�� ���� ���ذ� �� �ȵǾ�, ������ �о�ôµ�, �ᱹ ���� �״�� ������ ���� ������ �̺� �׷��� �����,
// �ִ� ��Ī�� ���ϸ� �ȴ�. ���̸� ������ ������ ������ ������ ����(k), �����̸� ���� - 1�� ������ ����(k-1)��
// �Ǿ� �������� �����ϴ� �Ͱ� ����.
// Ư�� ������ 0�� ���ԵǱ� ������, g_matched�� -1�� �ʱ�ȭ ���Ѿ� �Ѵ�.
// ���ѽð� 1�� �� 44ms(2,432KB)�� �ҿ�Ǿ���.
// ������� 27/270�� ���� 10.00%�� rank�Ǿ���.

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
		if (g_matched[to] == -1 || dfs(g_matched[to])) {
			g_matched[to] = from;
			return true;
		}
	}
	return false;
}

void doTest()
{
	int n, m;
	cin >> n >> m;
	g_graph.resize(n);
	int u, v;
	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		g_graph[u].push_back(v);
	}

	int count = 0;
	g_matched.assign(n, -1);
	for (int i = 0; i < n; i++) {
		g_visited.assign(n, false);
		if (dfs(i)) count++;
	}
	cout << count << "\n";
	g_graph.clear();
}

int main() {
	FAST;
	int T;
	cin >> T;
	for (int i = 0; i < T; i++) doTest();
}