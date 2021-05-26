// 9525.cpp
// 룩 배치하기
// ICPC > Regionals > Latin America > Latin America Regional Contests 2013 A번
// '2570 비숍2'와 한세트로 같이 풀어보는 문제이다.
// 이분 매칭자체는 간단한데 이분 매칭을 위해 이분 그래프 구성해야 하는데 체스판을 보고 이분 그래프 구성하는 작업이
// 문제 해결의 85%를 차지한다고 보면 된다.
// '2570 비숍2'은 대각선 방향이고 이 문제의 룩은 수평/수직 방향인 점만 다르고 나머지는 동일하다.
// 그룹 만들 때, 그룹의 시작이 'X'(pawn)이면 '.'이 나올 때 까지 그룹 카운트 증가하지 않도록 하는 것이 중요하다.
// 제한시간 1초 중 12ms(2,492KB)가 소요되었다.
// 맞은사람 131/269로 상위 48.69%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
//#include <list>
//#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_graph;
vector<bool> g_visited;
vector<int> g_matched;

bool dfs(int from)
{
	for (int to : g_graph[from]) {
		if (g_visited[to]) continue;
		else g_visited[to] = true;
		if (g_matched[to] == 0 || dfs(g_matched[to])) {
			g_matched[to] = from;
			return true;
		}
	}
	return false;
}

struct group {
	int g1, g2; // group1, group2
	bool barrier; // 장애물 여부
	group() : g1(0), g2(0), barrier(false) {}
	group(int g1, int g2, bool b) : g1(g1), g2(g2), barrier(b) {}
};

int main()
{
	FAST;
	int N;
	cin >> N;
	vector<vector<group>> chess(N + 1, vector<group>(N + 1, { 0, 0, false }));
	string cm; // chessman
	for (int i = 1; i < N + 1; i++) { // 체스판 pawn 위치 입력		
		cin >> cm;
		for (int j = 0; j < cm.length(); j++)
			if (cm[j] == 'X') chess[i][j + 1].barrier = true;
	}

	// 수평 그룹 입력
	bool gflag = false;
	int g1cnt = 0;
	for (int i = 1; i < N + 1; i++) {
		gflag = false; if (!chess[i][1].barrier) g1cnt++;
		for (int j = 1; j < N + 1; j++) {
			if (chess[i][j].barrier) gflag = true;
			else {
				if (gflag) { gflag = false; g1cnt++; }
				chess[i][j].g1 = g1cnt;
			}
		}
	}
	// 수직 그룹 입력
	int g2cnt = 0;
	for (int j = 1; j < N + 1; j++) {
		gflag = false; if (!chess[1][j].barrier) g2cnt++;
		for (int i = 1; i < N + 1; i++) {
			if (chess[i][j].barrier) gflag = true;
			else {
				if (gflag) { gflag = false; g2cnt++; }
				chess[i][j].g2 = g2cnt;
			}
		}
	}

	// 이분 그래프 만들기
	g_graph.resize(g1cnt + 1);
	g_visited.resize(g2cnt + 1, false);
	g_matched.resize(g2cnt + 1, 0);
	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < N + 1; j++) {
			if (!chess[i][j].barrier) g_graph[chess[i][j].g1].push_back(chess[i][j].g2);
		}
	}
	int answer = 0;
	for (int i = 1; i < g1cnt + 1; i++) {
		g_visited = vector<bool>(g2cnt + 1, false);
		if (dfs(i)) answer++;
	}
	cout << answer << "\n";
}