// 13344.cpp
// 국제 체스대회
// 어려운 문제이다. 엉뚱한 방향에서 함참을 헤매다 힌트를 보고 감을 잡았다.
// 유니온 파인드. 같은 그룹끼리 위상정렬(indegree)해서 사이클이 나오면 inconsistent, 안나오면 consistent!
// 이렇게 풀면 된다!
// ICPC > Regionals > Europe > Northwestern European Regional Contest > Benelux Algorithm Programming Contest > BAPC 2016 Preliminaries B번
// 제한시간 5초 중 64ms(7176KB)가 소요되었다.
// 맞은사람 4/88로 상위 4.54%에 rank되었다.

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
#include <utility> // pair, swap
//#include <stack>
//#include <set>
#include <queue> // queue, priority_queue

using namespace std;

vector<int> g_DJS;
int g_N, g_Group;
vector<vector<int>> g_graph;
vector<int> g_degree;

int find_djs(int item)
{
	if (g_DJS[item] == item) return item;
	else
		return g_DJS[item] = find_djs(g_DJS[item]);
}

bool union_djs(int s1, int s2)
{
	int r1, r2;
	r1 = find_djs(s1);
	r2 = find_djs(s2);
	if (r1 == r2) return false; // already same set!
	else
		g_DJS[r2] = r1;
	return true;
}

bool topological_sort()
{
	queue<int> myq;
	int pick, cnt = 0;
	bool result;
	for (int i = 0; i < g_N; i++) {
		if (g_degree[i] == 0)
			myq.push(i);
	}
	while (!myq.empty()) {
		pick = myq.front();
		myq.pop();
		cnt++;
		for (int x : g_graph[pick]) {
			g_degree[x]--;
			if (g_degree[x] == 0)
				myq.push(x);
		}
	}
	if (cnt >= g_Group) result = true;
	else result = false; // cycle exist!
	return result;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M, K, L, gcnt = 0;
	char S;
	vector<pair<int, int>> match;
	cin >> N >> M;
	g_N = N;
	g_DJS.resize(N);
	for (int i = 0; i < N; i++)
		g_DJS[i] = i;
	// 그룹생성
	for (int i = 0; i < M; i++) {
		cin >> K >> S >> L;
		if (S == '=') union_djs(K, L);
		else if (S == '>') match.push_back({ K, L });
	}
	// 그룹 카운트
	g_graph.resize(N);
	g_degree.resize(N, -1);
	for (int i = 0; i < N; i++) {
		if (find_djs(i) == i) {
			gcnt++;
			g_degree[i] = 0;
		}
	}
	g_Group = gcnt;
	// 그래프 입력
	for (pair<int, int> x : match) {
		g_graph[find_djs(x.first)].push_back(find_djs(x.second));
		g_degree[find_djs(x.second)]++;
	}
	cout << (topological_sort() ? "consistent" : "inconsistent") << "\n";
}