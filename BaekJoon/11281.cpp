// 11281.cpp
// 2-SAT-4
// 2-SAT-3가 2-SAT CNF 식을 true로 만들 수 있는 해가 존재하는지 여부를 판단하는 문제였다면,
// 2-SAT-4는 2-SAT-3에 해가 존재할 경우 그 해까지 출력하는 문제이다.
// 이 문제는 xi와 ~xi가 서로 다른 SCC component에 있을 경우, SCC 구하는 알고리즘 상
// SCC component id값이 작은 값이 도착하는 값이고 큰 값이 출발하는 값(root에 가까운 값)이기 때문에
// xi의 SCC component id값이 ~xi의 SCC component id값보다 작으면 xi는 true이고 크면 false가 된다.
// 예를 들어 x1 -> ~x1 에서 ~x1이 id값이 작으므로 true, x1이 false가 된다.
// 제한시간 1초 중 36ms(5,404KB)가 소요되었다.
// 맞은사람 83/338로 상위 24.55%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min, copy
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
	FAST
	
	int n, m, a, b;
	bool result = true;
	cin >> n >> m;
	g_graph.resize(2*n + 1 + 1);
	g_visited_seq.resize(2*n + 1 + 1, 0);
	g_finished.resize(2*n + 1 + 1, false);
	g_sccId.resize(2*n + 1 + 1, 0);
	for(int i = 0; i < m; i++) {
		cin >> a >> b;
		a = (a < 0) ? MK_NN(-a) : MK_N(a);
		b = (b < 0) ? MK_NN(-b) : MK_N(b);
		g_graph[MK_NOTN(a)].push_back(b);
		g_graph[MK_NOTN(b)].push_back(a);
	}
	for(int i = 2; i <= 2*n + 1; i++) {
		if (g_visited_seq[i] == 0)
			scc_dfs(i);
	}
	for(int i = 2; i <= 2*n + 1; i++) {
		if(g_sccId[i] == g_sccId[MK_NOTN(i)]) {
			result = false;
			break;
		}
	}
	cout << (result ? 1 : 0) << "\n";
	if(result) {
		for(int i = 1; i <= n; i++) {
			cout << (g_sccId[MK_N(i)] < g_sccId[MK_NN(i)] ? 1 : 0) << " ";
		}
		cout << "\n";
	}
}
