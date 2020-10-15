// 3665.cpp
// 최종 순위
// 위상 정렬의 기본 개념을 알면 풀 수 있는 문제인데,
// 제대로 이해를 못해서 한참 해메다가 풀이법을 보고 어떻게
// 푸는지 이해할 수 있게 되었다.
// 문제에서 순서의 모든쌍을 만든 다음 이 중에서 바뀌는 순서쌍만
// 찾아서 바꾼 다음에 이 것을 위상 정렬로 배열하면 된다.
// 위상 정렬 중에 결과가 2개 이상 또는 사이클이 생기는 경우를 구분해서
// 답을 해 준다.
// ICPC > Regionals > Europe > Northwestern European Regional Contest > NWERC 2010 E번
// 제한시간 1초 중 28ms(3644KB)가 소요되었다.
// 맞은사람 114/623로 상위 18.29%에 rank되었다.

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
#include <queue> // queue, priority_queue

using namespace std;

int g_N;
vector<vector<int>> g_graph;
vector<int> g_degree;
vector<int> g_result;

int topological_sort() // 1 : OK, 0 : multi case, -1 : cycle
{
	int result = 1, count = 0;
	queue<int> myq;
	int pick;
	for (int i = 1; i <= g_N; i++) {
		if (g_degree[i] == 0)
			myq.push(i);
	}
	while (!myq.empty()) {
		if (myq.size() > 1) result = 0;
		pick = myq.front();
		myq.pop();
		g_result.push_back(pick);
		count++;
		for (int x : g_graph[pick]) {
			g_degree[x]--;
			if (g_degree[x] == 0)
				myq.push(x);
		}
	}
	if (count < g_N) result = -1; // cycle

	return result;
}

void do_test()
{
	int m, a, b, result;
	vector<int> last_score;
	int change[501][501] = { {0, }, };
	cin >> g_N;
	last_score.resize(g_N + 1);
	g_graph.resize(g_N + 1);
	g_degree.resize(g_N + 1, 0);
	// 작년 순위 입력
	for (int i = 1; i <= g_N; i++)
		cin >> last_score[i];
	cin >> m;
	// 변동 순위 입력
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		change[a][b] = 1;
		change[b][a] = 1;
	}
	// 변동 순위 반영한 graph data 입력
	for (int i = 1; i <= g_N - 1; i++) {
		for (int j = i + 1; j <= g_N; j++) {
			if (change[last_score[i]][last_score[j]]) {
				g_graph[last_score[j]].push_back(last_score[i]);
				g_degree[last_score[i]]++;
			}
			else {
				g_graph[last_score[i]].push_back(last_score[j]);
				g_degree[last_score[j]]++;
			}
		}
	}
	// 위상 정렬
	result = topological_sort();
	if (result == 1) {
		for (int x : g_result)
			cout << x << " ";
		cout << "\n";
	}
	else
		cout << ((result == 0) ? "?" : "IMPOSSIBLE") << "\n";
	
	g_graph.clear();
	g_degree.clear();
	g_result.clear();
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int test_case;
	cin >> test_case;
	for (int i = 0; i < test_case; i++)
		do_test();
}