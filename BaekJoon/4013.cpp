// 4013.cpp
// ATM
// SCC�� ����� �����ϴ� ���� ����� �����̴�.
// SCC�� ����� SCC���� �׷����� ���� ����
// SCC �׷������� ���� �����Ͽ� �ִ밪�� ���ϴ� �����̴�.
// ������ �ʿ��ϴ�.
// 1) �� �����ΰ� ���ϴ� SCC ����
// 2) SCC���� ã�� �� �ִ� ������ ���հ� ������� ���� ����
// 3) SCC ���� �׷��� ����
// 4) 3)�� �̿��� ���� ����
// ������ �������� ���ؼ� ġ�����̾��� ���� �ִµ� ��������� ��������� �ִ� �� ������ ��� ��������� cash �ִ밪�� ���Ѵ�.
// ���� ��������� �ϳ��� ������ ���� 0�̰�, ���� ������ ���� ã���� �� 100�̶� ��������� �߰����� ������ ���� 100���� �۴�.
// Ư�� �������� ��������� ���� �� ���Ŀ��� �� ���� �� ���� �� ���� ū ���� ���ؾ� �Ѵ�.(��ζ��� ���� �������)
// �׷����� ���� �� ������� ������ ���� �ִ밪 ������ ���� �ڰ� �����̾��� �� ���� ������ ū ���� �����ؾ� �Ѵ�.
// �ѹ� Ʋ�ȴ�!
// SCC�� ����� ���� start �������� �ϰ�, SCC graph ����� ���� ��� ������ ���� �����ؼ� �������.
// �̷� ���� ������ �ȴ�. 
// start�������� �� �� ���� �ܺ� �������� ������ SCC�� ���� ��� SCC�� ���� ���� �ش� SCC ���߸��ٰ�
// SCC �׷��� ���鶧�� ��� ������ ���� �����ϴ� �ٶ��� ���� SCC�� SCC id 0��(default)���� ���ڱ� ġ�� ����
// SCC �׷����� ���� ������ �� ������ �����. (start���� ���� �����ϸ� �ǵ�ġ �ʴ� 0�� SCC ������ indegree 0�� �ƴ� ä�� ���
// ���� �ִ� ������ �����)
// 1) ���� ��� ������ ���� SCC ����� ��� ������ ���� SCC �׷��� ������ �ϴ� �� �´�.
// 2) �׸��� ���� ���� �� start SCC�� �ƴ� indegree�� 0�� SCC���� �����ϵ� start SCC�� �ƴϸ� cash ����� ���� �ʴ´�.
// �̸� ���� SCCFromStart[] ��� �迭�� ����� start SCC���� ����� SCC�� true�� �����ؼ� cash ����� �ϵ��� �Ѵ�.
// ����� ���� ������ �̿����� �ʰ� BFS�� Ǯ�� ���� �ð��� ���� �� �ɸ����� �����Ѱ� ����� �ʿ� ���� ������ ������ ����.
// Olympiad > Asia-Pacific Informatics Olympiad > APIO 2009 3��
// ���ѽð� 2�� �� 348ms(68,716KB)�� �ҿ�Ǿ���.
// ������� 17/368�� ���� 4.61%�� rank�Ǿ���.

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
#include <queue> // queue, priority_queue
//#include <functional> // less, greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct cross {
	int cash;
	bool meal;
	int scc;
	cross() {}
	cross(int c, bool m, int s) : cash(c), meal(m), scc(s) {}
};

struct scc_info {
	int sum;
	bool meal;
	scc_info() {}
	scc_info(int s, bool m) : sum(s), meal(m) {}
};

struct scc_info2 {
	int indegree;
	int max_val;
	bool fromStart;
	scc_info2(int i, int m, bool f) : indegree(i), max_val(m), fromStart(f) {}
};

vector<vector<int>> g_graph;
vector<int> g_visited_seq; // �湮����
vector<bool> g_finished; // ������ �Ǵ�
stack<int> g_st;
int g_cnt = 0;
int g_sccId = 0;
vector<cross> g_cross;
vector<scc_info> g_scc; // scc component
vector<vector<int>> g_scc_graph;
vector<scc_info2> g_scc_cal; // scc calculation

int scc_dfs(int current)
{
	int result, n;
	int sum = 0;
	bool meal;
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
		g_sccId++;
		sum = 0; meal = false;
		while (1) {
			n = g_st.top();
			g_st.pop();
			g_cross[n].scc = g_sccId;
			sum += g_cross[n].cash;
			if (g_cross[n].meal) meal = true;
			g_finished[n] = true;
			if (n == current) break;
		}
		g_scc[g_sccId] = { sum, meal };
	}
	return result;
}

int topological_sort(int start)
{
	queue<int> myq;
	int pick, scc_start, result = 0;
	for (int i = 1; i <= g_sccId; i++) {
		if (g_scc_cal[i].indegree == 0)
			myq.push(i);
	}
	scc_start = g_cross[start].scc;
	g_scc_cal[scc_start].fromStart = true;
	g_scc_cal[scc_start].max_val = g_scc[scc_start].sum;
	
	while (!myq.empty()) {
		pick = myq.front();
		myq.pop();
		if (g_scc[pick].meal) result = max(result, g_scc_cal[pick].max_val);
		for (int x : g_scc_graph[pick]) {
			if (g_scc_cal[pick].fromStart) {
				g_scc_cal[x].max_val = max(g_scc_cal[x].max_val, g_scc_cal[pick].max_val + g_scc[x].sum);
				g_scc_cal[x].fromStart = true;
			}
			g_scc_cal[x].indegree--;
			if (g_scc_cal[x].indegree == 0)
				myq.push(x);
		}
	}
	return result;
}

int main()
{
	FAST;

	int n, m, s, e;
	int start, rn, r;
	cin >> n >> m;
	g_graph.resize(n+1);
	g_visited_seq.resize(n+1, 0);
	g_finished.resize(n+1, false);
	g_cross.resize(n + 1, { 0, false, 0 });
	g_scc.resize(n + 1, { 0, false });
	for (int i = 0; i < m; i++) {
		cin >> s >> e;
		g_graph[s].push_back(e);
	}
	for (int i = 1; i <= n; i++)
		cin >> g_cross[i].cash;
	cin >> start >> rn;
	for (int i = 0; i < rn; i++) {
		cin >> r;
		g_cross[r].meal = true;
	}
	// make scc
	for (int i = 1; i <= n; i++) {
		if (g_visited_seq[i] == 0) scc_dfs(i);
	}
	g_scc_graph.resize(g_sccId + 1);
	g_scc_cal.resize(g_sccId + 1, { 0, 0, false });
	// make scc graph
	for (int i = 1; i <= n; i++) {
		for (int next : g_graph[i]) {
			int from = g_cross[i].scc, to = g_cross[next].scc;			
			if (from == to) continue;
			g_scc_graph[from].push_back(to);
			g_scc_cal[to].indegree++;
		}
	}
	cout << topological_sort(start) << "\n";
}