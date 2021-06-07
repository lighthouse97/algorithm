// 13166.cpp
// 범죄 파티
// University > 전국 대학생 프로그래밍 대회 동아리 연합 여름 대회 > UCPC 2016 H번
// 이분 탐색 문제인데, '1348 : 주차장'과 비슷하게 풀면 된다.
// 이분 매칭 시에 조건 K를 두어 K를 만족하는 것만 매칭을 한다.
// 그리고 0 ~ K의 이분 탐색으로 다양한 K값을 넣어서 이분 매칭의 최대 매칭  수가 N이 되는 최소한의 K를 구하면 된다.
// 어떤 K를 넣어도 이분 매칭의 최대 매칭 결과가 N이 안나오면 -1을 출력한다.
// MLE 에러가 나와서 비용에 map을 사용했다.
// map을 사용하면 MLE는 안나오지만 TLE가 또 발생하였다.
// 자, 이 문제는 N의 범위가 200,000이나 되므로 일반적인 이분매칭 알고리즘(단순 dfs 사용)을 사용하면
// TLE가 발생할 수 밖에 없는 문제이다.
// 그렇다!!! 이 문제는 Hopcroft-Karp 알고리즘을 사용해야만 풀 수 있는 문제이다!!!
// Hopcroft-Karp 알고리즘을 사용해서 다시 풀어보자.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil, hypot
#include <vector>
//#include <list>
#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_graph;
vector<bool> g_visited;
vector<int> g_matched;
map<pair<int, int>, int> g_cost;
int g_N = 0, g_FN = 0; // 용의자의 수, 친구의 수

bool dfs_with_p(int from, int p)
{
	for (int to : g_graph[from]) {
		if (g_cost.find({ from, to }) == g_cost.end()) continue;
		if (g_cost[{from, to}] > p || g_visited[to]) continue;
		else g_visited[to] = true;
		if (g_matched[to] == 0 || dfs_with_p(g_matched[to], p)) {
			g_matched[to] = from;
			return true;
		}
	}
	return false;
}

int match(int t)
{
	int count = 0;
	g_matched.assign(g_FN + 1, 0);
	for (int i = 1; i < g_N + 1; i++) {
		g_visited.assign(g_FN + 1, false);
		if (dfs_with_p(i, t)) count++;
	}
	return count;
}

int main()
{
	FAST;
	cin >> g_N;
	g_graph.resize(g_N + 1);
	int f1, k1, f2, k2;
	int maxcost = 0;
	for (int i = 1; i < g_N + 1; i++) {
		cin >> f1 >> k1 >> f2 >> k2;
		g_graph[i].push_back(f1); // 친구 1		
		g_cost[{ i, f1 }] = k1;
		g_FN = max(g_FN, f1); // 친구의 최대 번호를 찾는다
		maxcost = max(maxcost, k1);
		g_graph[i].push_back(f2); // 친구 2		
		g_cost[{ i, f2 }] = k2;
		g_FN = max(g_FN, f2);
		maxcost = max(maxcost, k2);
	}

	int left = 0, mid = 0, right = maxcost;
	while (left < right) { // 이진 탐색, lower_bound
		mid = (left + right) / 2;
		if (match(mid) < g_N) left = mid + 1; // 시간 늘림
		else right = mid; // 시간 줄임
	}
	if (match(left) == g_N) cout << left << "\n";
	else cout << -1 << "\n";
}