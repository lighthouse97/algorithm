// 11280.cpp
// 2-SAT-3
// 2-SAT(2-Satisfiable) 기본 문제이다.
// 2-SAT는 논리곱 표준형, CNF(Conjunctive Normal Form)의 논리합 부분인
// 각 절(clause)이 최대 2개의 변수로 이루어진 것으로서
// 이 CNF를 true로 만드는 논리변수들의 조합이 있는지를 검사하는 것이다.
// 예로 하나의 절이 (A | B)라면 이 식은 (~A->B) AND (~B->A)를 만족해야 한다
// CNF식의 각 절을 위와 같이 고친다음에 그래프로 만들어서
// SCC로 분류한 다음에 같은 SCC내에 A->~A 또는 ~A->A가 존재하면 어떠한 값을 대입해도 CNF식을 true로
// 만들수가 없다. 증명하자면 A->~A에서 한 SCC에 A가 true이면 ~A가 false라 결국 false이고,
// A가 false이면 ~A는 true라 true이지만 또다른 SCC에 ~A->A가 있고 여기서 true -> false가 되어 false가
// 되므로 모두 AND 연산인 clause 중 하나가 무조건 false가 되어 전체가 false가 되게 된다.
// 즉 한 SCC내에 A와 ~A가 공존하면 CNF식 전체를 true로 만들 수가 없다.
// 제한시간 1초 중 32ms(5,404KB)가 소요되었다.
// 맞은사람 33/343로 상위 9.62%에 rank되었다.

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
}
