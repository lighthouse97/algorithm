// 16367.cpp
// TV Show Show Game
// �� ������ k���� ���� �� ��� ����� ������ 3���� ���� �� ��� 2���̻��� ���� ������ ���� �� �ֵ���
// k���� ������ ��ġ�ϴ� �����̴�.
// �� ������ xi��� �ϰ� xi�� R�� = T, ~xi = ~R = B�� = F��� �ϸ� �� ������ 2-SAT������ �ٲپ� Ǯ �� �ִ�.
// �� �� �������� R�� B�� ��Ȯ�ϰ� ���߸� T�� �ǰ� ������ ���ϸ� F�� �ǰ� �ȴ�.
// �̷��� �ؼ� �����ڰ� ������ 3���� ���� P, Q, R�� ��� 2���� ������� ������ (P & Q) | (Q & R) | (P & R)
// �� �Ǵµ� �̴� (P | Q) & (Q | R) & (P | R) �� ��ġ�̰� �� ���� 2-SAT�� �����ϴ� ���� �ȴ�.
// �� 2���� ��ġ��� ���� ���������δ� �� �� �ִµ�, �������� Ǯ� �����Ϸ��� ������ �ȵǾ
// ����ǥ�� ������ ��� ���� �����ؼ� Ȯ���� ���� 2���� ��ġ��� ���� �����Ͽ���.
// ���� ������ �����ϴ� ����� ���Ŀ� �� �� �˾ƺ��� �ڴ�.
// �� ������ ICPC�� ���Դ� �����ε�, ���� Ǭ ������� ������ ���� ���������� (P | Q) & (Q | R) & (P | R)�� 2-SAT��
// �����ؼ� Ǭ�ٴ� ��޸� ���� �� �ڼ��� ������ ������.
// ICPC > Regionals > Asia Pacific > Korea > Asia Regional - Seoul 2018 K��
// ���ѽð� 1�� �� 8ms(3,220KB)�� �ҿ�Ǿ���.
// ������� 14/76�� ���� 18.42%�� rank�Ǿ���.

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

#define MK_N(x)		(x << 1)
#define MK_NN(x)	(x << 1 | 1)
#define MK_NOTN(x)	(x ^ 1)
vector<vector<int>> g_graph;
vector<int> g_visited_seq; // �湮����
vector<bool> g_finished; // ������ �Ǵ�
stack<int> g_st;
vector<int> g_sccId;
int g_cnt = 0;
int g_scc_num = 0;

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
		g_scc_num++;
		while (1) {
			n = g_st.top();
			g_st.pop();
			g_sccId[n] = g_scc_num;
			g_finished[n] = true;
			if (n == current) break;
		}
	}
	return result;
}

int main()
{
	FAST;

	int k, n, l1, l2, l3;
	char c1, c2, c3;
	bool result;
	cin >> k >> n;
	g_graph.resize(2*k + 1 + 1);
	g_visited_seq.resize(2*k + 1 + 1, 0);
	g_finished.resize(2*k + 1 + 1, false);
	stack<int> g_st;
	g_sccId.resize(2*k + 1 + 1, 0);
	for (int i = 0; i < n; i++) {
		cin >> l1 >> c1 >> l2 >> c2 >> l3 >> c3;
		l1 = (c1 == 'R') ? MK_N(l1) : MK_NN(l1);
		l2 = (c2 == 'R') ? MK_N(l2) : MK_NN(l2);
		l3 = (c3 == 'R') ? MK_N(l3) : MK_NN(l3);
		g_graph[MK_NOTN(l1)].push_back(l2);
		g_graph[MK_NOTN(l2)].push_back(l1);
		g_graph[MK_NOTN(l2)].push_back(l3);
		g_graph[MK_NOTN(l3)].push_back(l2);
		g_graph[MK_NOTN(l1)].push_back(l3);
		g_graph[MK_NOTN(l3)].push_back(l1);
	}
	for (int i = 2; i <= 2 * k + 1; i++) {
		if (g_visited_seq[i] == 0)
			scc_dfs(i);
	}
	result = true;
	for (int i = 2; i <= 2 * k + 1; i++) {
		if (g_sccId[i] == g_sccId[MK_NOTN(i)]) {
			result = false;
			break;
		}
	}
	if (result) {
		for (int i = 1; i <= k; i++) {
			cout << (g_sccId[MK_N(i)] < g_sccId[MK_NN(i)] ? "R" : "B");
		}
		cout << "\n";
	}
	else
		cout << -1 << "\n";
}