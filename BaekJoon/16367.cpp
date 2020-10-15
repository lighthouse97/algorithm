// 16367.cpp
// TV Show Show Game
// 이 문제는 k개의 램프 중 모든 사람이 선택한 3개의 램프 중 적어도 2개이상의 램프 색깔을 맞출 수 있도록
// k개의 램프를 배치하는 문제이다.
// 각 램프를 xi라고 하고 xi를 R색 = T, ~xi = ~R = B색 = F라고 하면 이 문제를 2-SAT문제로 바꾸어 풀 수 있다.
// 즉 각 변수마다 R과 B를 정확하게 맞추면 T가 되고 맞추지 못하면 F가 되게 된다.
// 이렇게 해서 참가자가 선택한 3개의 램프 P, Q, R중 적어도 2개를 맞출려면 논리식이 (P & Q) | (Q & R) | (P & R)
// 가 되는데 이는 (P | Q) & (Q | R) & (P | R) 과 동치이고 이 식이 2-SAT을 만족하는 식이 된다.
// 위 2식이 동치라는 것이 직관적으로는 알 수 있는데, 논리식으로 풀어서 증명하려니 도저히 안되어서
// 진리표로 변수의 모든 값을 전개해서 확인해 보니 2식이 동치라는 것을 증명하였다.
// 논리식 전개로 증명하는 방법은 추후에 좀 더 알아봐야 겠다.
// 이 문제는 ICPC에 나왔던 문제인데, 문제 푼 사람들의 설명을 봐도 직관적으로 (P | Q) & (Q | R) & (P | R)로 2-SAT로
// 변형해서 푼다는 언급만 있지 더 자세한 설명은 없었다.
// ICPC > Regionals > Asia Pacific > Korea > Asia Regional - Seoul 2018 K번
// 제한시간 1초 중 8ms(3,220KB)가 소요되었다.
// 맞은사람 14/76로 상위 18.42%에 rank되었다.

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
vector<int> g_visited_seq; // 방문순서
vector<bool> g_finished; // 역방향 판단
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