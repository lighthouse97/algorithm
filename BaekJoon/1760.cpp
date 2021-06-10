// 1760.cpp
// N-Rook
// Olympiad > Central European Olympiad in Informatics > CEOI 2002 5번
// 체스판을 이용한 이분탐색, 이분매칭 문제이다.
// '9525 룩배치'와 동일한 문제인데, 구멍이 하나 더 추가된 점만 다르다.
// 구멍의 속성은 같은 그룹에 속하나 매칭에는 사용될 수 없다는 점이다.
// 그래서 매칭 시 양쪽 중 하나라도 구멍이면 매칭에서 제외시키면 된다.
// 제한시간 2초 중 0ms(2,332KB)가 소요되었다.
// 맞은사람 67/281로 상위 23.84%에 rank되었다.

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
//#include <string> // string, stoi
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
	int option; // 장애물 타입, 0 : 빈칸, 1 : 구멍, 2 : 벽
	group() : g1(0), g2(0), option(0) {}
	group(int g1, int g2, bool o) : g1(g1), g2(g2), option(o) {}
};

int main()
{
	FAST;
	int N, M;
	cin >> N >> M;
	vector<vector<group>> chess(N + 1, vector<group>(M + 1, { 0, 0, 0 }));
	for (int i = 1; i < N + 1; i++) { // chess판 option 입력
		for (int j = 1; j < M + 1; j++)
			cin >> chess[i][j].option;
	}

	// 수평 그룹 입력
	bool gflag = false;
	int g1cnt = 0;
	for (int i = 1; i < N + 1; i++) {
		gflag = false; if (chess[i][1].option == 0 || chess[i][1].option == 1) g1cnt++;
		for (int j = 1; j < M + 1; j++) {
			if (chess[i][j].option == 2) gflag = true;
			else {
				if (gflag) { gflag = false; g1cnt++; }
				chess[i][j].g1 = g1cnt;
			}
		}
	}
	// 수직 그룹 입력
	int g2cnt = 0;
	for (int j = 1; j < M + 1; j++) {
		gflag = false; if (chess[1][j].option == 0 || chess[1][j].option == 1) g2cnt++;
		for (int i = 1; i < N + 1; i++) {
			if (chess[i][j].option == 2) gflag = true;
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
			if (chess[i][j].option == 0) g_graph[chess[i][j].g1].push_back(chess[i][j].g2);
		}
	}
	int answer = 0;
	for (int i = 1; i < g1cnt + 1; i++) {
		g_visited = vector<bool>(g2cnt + 1, false);
		if (dfs(i)) answer++;
	}
	cout << answer << "\n";
}