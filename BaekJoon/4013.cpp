// 4013.cpp
// ATM
// SCC를 제대로 응용하는 아주 어려운 문제이다.
// SCC를 만들고 SCC끼리 그래프를 만든 다음
// SCC 그래프에서 위상 정렬하여 최대값을 구하는 문제이다.
// 다음이 필요하다.
// 1) 각 교차로가 속하는 SCC 정보
// 2) SCC마다 찾을 수 있는 현금의 총합과 레스토랑 포함 유무
// 3) SCC 간의 그래프 구성
// 4) 3)을 이용한 위상 정렬
// 문제를 이해하지 못해서 치명적이었던 것이 있는데 레스토랑은 레스토랑이 있는 곳 까지의 모든 레스토랑의 cash 최대값을 말한다.
// 만일 레스토랑이 하나도 없으면 답은 0이고, 만일 끝까지 돈을 찾았을 때 100이라도 레스토랑이 중간에만 있으면 답은 100보다 작다.
// 특정 지점에서 레스토랑을 여러 개 거쳐오면 그 여러 개 까지 중 가장 큰 값을 구해야 한다.(경로랑은 전혀 상관없다)
// 그래프가 만날 때 레스토랑 유무에 따라 최대값 선택은 한참 자가 당착이었고 이 때는 무조건 큰 값을 선택해야 한다.
// 한번 틀렸다!
// SCC를 만드는 것은 start 지점부터 하고, SCC graph 만드는 것은 모든 지점에 대해 조사해서 만들었다.
// 이런 경우는 문제가 된다. 
// start지점에서 갈 수 없는 외부 지점에서 들어오는 SCC가 있을 경우 SCC를 만들 때는 해당 SCC 빠뜨리다가
// SCC 그래프 만들때는 모든 지점에 대해 조사하는 바람에 없던 SCC가 SCC id 0번(default)으로 갑자기 치고 들어와
// SCC 그래프로 위상 정렬할 때 문제를 만든다. (start부터 위상 정렬하면 의도치 않던 0번 SCC 때문에 indegree 0이 아닌 채로 계속
// 남아 있는 지점이 생긴다)
// 1) 따라서 모든 지점에 대해 SCC 만들고 모든 지점에 대해 SCC 그래프 만들어야 하는 게 맞다.
// 2) 그리고 위상 정렬 때 start SCC가 아닌 indegree가 0인 SCC부터 시작하되 start SCC가 아니면 cash 계산을 하지 않는다.
// 이를 위해 SCCFromStart[] 라는 배열을 만들어 start SCC에서 연결된 SCC만 true로 설정해서 cash 계산을 하도록 한다.
// 참고로 위상 정렬을 이용하지 않고 BFS로 풀면 실행 시간은 조금 더 걸리지만 복잡한거 고려할 필요 없이 구현이 간단해 진다.
// Olympiad > Asia-Pacific Informatics Olympiad > APIO 2009 3번
// 제한시간 2초 중 348ms(68,716KB)가 소요되었다.
// 맞은사람 17/368로 상위 4.61%에 rank되었다.

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
vector<int> g_visited_seq; // 방문순서
vector<bool> g_finished; // 역방향 판단
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