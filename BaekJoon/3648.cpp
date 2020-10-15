// 3648.cpp
// 아이돌
// 2-SAT을 그대로 응용하는 문제이다.
// 각 심사위원의 투표한 두 표가 2-SAT CMF의 각각의 clause가 된다.
// 왜냐하면 심사위원이 행사한 두 표 중 적어도 하나는 심사위원이 투표한 것과 같아야 하므로
// (xi | xj)의 결과가 true가 되어야 하기 때문이다. 따라서 전체 CNF의 결과도 true가 되어야 한다.
// 만일 이 조건을 만족하지 못하면 (xi | xj)가 false가 되어 심사위원이 의심하게 되므로 의도한 결과가
// 나타나지 않게 된다.
// 또한 1번 참가자가 무조건 다음 경연에 참가해야 하므로 1번 참가자의 값은 true가 되어야 한다.
// 따라서 2-SAT 식에 (X1 | X1) 조건을 추가시켜 주면 된다.(첫번째 X1이 항상 참이어야 한다는 조건을 표시함)
// (X1 | X1) 조건을 추가시켜 주는 것은 아이디어가 떠오르지 않아서 다른 사람이 푼 것을 잠깐 참고하다가
// 알게 되었다.
// ICPC > Regionals > Europe > Northwestern European Regional Contest > NWERC 2012 I번
// 제한시간 10초 중 20ms(2,268KB)가 소요되었다.
// 맞은사람 51/204로 상위 25.00%에 rank되었다.

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
	while(cin >> n) {
		cin >> m;
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
		a = MK_N(1);
		g_graph[MK_NOTN(a)].push_back(a); // add (x1 | x1)
		
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
		cout << (result ? "yes" : "no") << "\n";

		g_graph.clear();
		g_visited_seq.clear();
		g_finished.clear();
		g_sccId.clear();
		g_cnt = 0;
		g_scc_num = 0;
		result = true;
	}
}
