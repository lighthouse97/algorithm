// 3977.cpp
// �౸ ����
// SCC�� ���� Ȱ���ϴ� �����̴�.
// SCC�� ����� SCC���� ���������ؼ� root�� �ش�Ǵ� SCC�� ���ϸ� �ȴ�.
// SCC���� ������� �ʴ� ���� �� �Ѱ��� ������ Confused ó���ϸ� �ȴ�.
// �� �� ����غ��� ���� SCC���� ���� ���������� �ʿ���� SCC�� vector�� �߰��� ��
// ���� �������� �߰��Ǵ� SCC�� root�� �ش�Ǵ� SCC�̴�.(SCC ���� ��� ����� ���)
// �� �̹� ���� ������ �� ���·� SCC���� �߰��Ǵ� ���̴�.
// ���� �������� �߰��� SCC�� ������ �� ���Ҹ� ������ dfs������ ���� ��ȸ�ϸ� �ش� SCC�� ���̵ǰ�
// dfs���� ���� ��ȸ���� ���ϸ� Confused�� ����� ���̴�.
// ICPC > Regionals > Europe > Northwestern European Regional Contest > German Collegiate Programming Contest > GCPC 2010 D��
// ���ѽð� 1�� �� 216ms(12928KB)�� �ҿ�Ǿ���.
// ������� 21/229�� ���� 9.17%�� rank�Ǿ���.

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
vector<int> g_visited;

int scc_dfs(int current)
{
	int result, n;
	g_visited_seq[current] = ++g_cnt;
	g_st.push(current);
	result = g_visited_seq[current];
	for (int next : g_graph[current]) {
		if (g_visited_seq[next] == 0) {
			result = min(result, scc_dfs(next));
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

void dfs(int current)
{
	g_visited[current] = true;
	for (int next : g_graph[current]) {
		if(!g_visited[next])
			dfs(next);
	}
}

void do_test()
{
	int v, e, a, b;
	int root;
	bool result = true;
	cin >> v >> e;
	g_graph.resize(v);
	g_visited_seq.resize(v, 0);
	g_finished.resize(v, false);
	g_visited.resize(v, false);

	for (int i = 0; i < e; i++) {
		cin >> a >> b;
		g_graph[a].push_back(b);
	}
	// do dfs with the graph
	for (int i = 0; i < v; i++) {
		if (g_visited_seq[i] == 0) {
			scc_dfs(i);
		}
	}
	// �������� �߰��� SCC�� ��ü ���ᰡ������ �˻�
	root = g_scc.back()[0];
	dfs(root);
	for (int i = 0; i < v; i++) {
		if (!g_visited[i]) {
			result = false;
			break;
		}
	}
	if (result) {
		for (int x : g_scc.back())
			cout << x << "\n";
	}
	else
		cout << "Confused" << "\n";

	g_graph.clear();
	g_visited_seq.clear();
	g_finished.clear();
	g_scc.clear();
	g_visited.clear();
	g_cnt = 0;
}

int main()
{
	FAST;

	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		do_test();
		cout << "\n";
	}
}