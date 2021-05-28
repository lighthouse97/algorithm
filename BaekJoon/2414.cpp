// 2414.cpp
// 게시판 구멍 막기
// Olympiad > USA Computing Olympiad > 2004-2005 Season > USACO January 2005 Contest > Gold 1번
// '9525 룩 배치하기'와 동일한 문제이다.
// 테이프로 막을 구멍이 있는 위치만 가로, 세로로 그룹을 만들어 2개의 그룹을 가지고 이분매칭(최대매칭) 돌리면 된다.
// 9525 copy & paste 하는 과정에서 N, M을 제대로 처리하지 않아서 두번 WA가 나왔다. 잘 보고 하자!!!
// 제한시간 2초 중 0ms(2,164KB)가 소요되었다.
// 맞은사람 212/372로 상위 69.23%에 rank되었다.

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
	int N, M;
	cin >> N >> M;
	vector<vector<group>> chess(N + 1, vector<group>(M + 1, { 0, 0, false }));
	string ss;
	for (int i = 1; i < N + 1; i++) {
		cin >> ss;
		for (int j = 0; j < ss.length(); j++)
			if (ss[j] == '.') chess[i][j + 1].barrier = true;
	}

	// 수평 그룹 입력
	bool gflag = false;
	int g1cnt = 0;
	for (int i = 1; i < N + 1; i++) {
		gflag = false; if (!chess[i][1].barrier) g1cnt++;
		for (int j = 1; j < M + 1; j++) {
			if (chess[i][j].barrier) gflag = true;
			else {
				if (gflag) { gflag = false; g1cnt++; }
				chess[i][j].g1 = g1cnt;
			}
		}
	}
	// 수직 그룹 입력
	int g2cnt = 0;
	for (int j = 1; j < M + 1; j++) {
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
		for (int j = 1; j < M + 1; j++) {
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