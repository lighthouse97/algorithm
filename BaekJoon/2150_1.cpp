// 2150_1.cpp
// Strongly Connected Component
// SCC �˰��� ���� �����̴�.
// Kosaraju algorithm�� Tarjan algorithm �� �̹�����
// Tarjan algorithm�� �̿��ؼ� Ǭ��.
// �����ϱ⿡�� Kosaraju algorithm�� �� ������
// ��ȸ������ DFS �ѹ��� ������ Tarjan algorithm�� �� ���� ����Ѵ�.
// Tarjan algorithm�� dfs�� �ѹ��� ������ �׷��� ����ð��� �� ���� �ɷȴ�.(28ms -> 24ms)
// �޸� ��뷮�� �� ������. (4332KB -> 3548KB)
// ���ѽð� 2�� �� 24ms(3548KB)�� �ҿ�Ǿ���.
// ������� 39/1160�� ���� 3.36%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy
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
vector<int> g_visited_seq; // �湮����
vector<bool> g_finished; // ������ �Ǵ�
stack<int> g_st;
vector<vector<int>> g_scc; // scc component
int g_cnt = 0;

bool mycompare(const vector<int>& a, const vector<int>& b) { return (a[0] < b[0]); }

int dfs(int current)
{
	int result, n;
	g_visited_seq[current] = ++g_cnt;
	g_st.push(current);
	result = g_visited_seq[current];
	for (int next : g_graph[current]) {
		if (g_visited_seq[next] == 0) {
			result = min(result, dfs(next));
		}
		else if (g_finished[next] == false) {
			result = min(result, g_visited_seq[next]);
		}
	}
	// make scc
	if (result == g_visited_seq[current]) {
		vector<int> scc;
		while (1) {
			n = g_st.top();
			g_st.pop();
			scc.push_back(n);
			g_finished[n] = true;
			if (n == current) break;
		}
		sort(scc.begin(), scc.end());
		g_scc.push_back(scc);
	}
	return result;
}

int main()
{
	FAST

	int v, e, a, b;
	cin >> v >> e;
	g_graph.resize(v + 1);
	g_visited_seq.resize(v + 1, 0);
	g_finished.resize(v + 1, false);
	
	for (int i = 0; i < e; i++) {
		cin >> a >> b;
		g_graph[a].push_back(b);
	}
	// do dfs with the graph
	for (int i = 1; i <= v; i++) {
		if (g_visited_seq[i] == 0) {
			dfs(i);
		}
	}
	// print scc
	sort(g_scc.begin(), g_scc.end(), mycompare);
	cout << g_scc.size() << "\n";
	for (vector<int> x : g_scc) { // faster than using index in for loop
		for (int n : x)
			cout << n << " ";
		cout << -1 << "\n";
	}
}