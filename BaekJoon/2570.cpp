// 2570.cpp
// 비숍2
// Olympiad > 한국정보올림피아드 > 한국정보올림피아드시․도지역본선 > 지역본선 2007 > 중등부 5번
// 이분 매칭 문제인데... 체스판이라... 이분 그래프 구성하는 것이 문제의 핵심이다.
// 그리고 이분 그래프 구성하는 방법이 모르면 매우 어렵다. 대각선 방향이 /, \ 2가지 방향이 있는데,
// 각각의 방향에 대해 그룹을 만든다. 즉 하나의 그룹의 정점들은 동시에 놓여질 수 없고 하나만 선택이 되는데 이 하나만의 선택이 바로
// 다른 그룹의 정점 하나를 선택하는 셈이 된다. 이러한 방식이 바로 이분 매칭이고 이분 매칭에서 최대 매칭 수를 구하는 것이 문제의 요지이다.
// 이 문젠는 '9525 룩 배치하기'와 동일 선상에서 풀 수가 있다.(룩 배치하기는 대각선 방향이 아니고 수직/수평 방향이라 좀 더 쉽다.)
// 그리고 그룹을 구성할 때 대각선 방향으로 진행하다가 장애물이 나오면 동일 대각선상에서 그룹이 하나 더 증가한다. 장애물이 그룹을 분리시키는
// 역할을 하게 되는 셈이다.
// 대각선 방향에서 그룹을 구성하는 방법이 어려워서 시간이 많이 걸렸는데, 이것은 BOJ 2570 문제의 메모란에 따로 정리해 놓았다.
// 제한시간 1초 중 0ms(2,160KB)가 소요되었다.
// 맞은사람 175/428로 상위 40.88%에 rank되었다.

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
	bool barrier; // 장애물 여부
	group() : g1(0), g2(0), barrier(false) {}
	group(int g1, int g2, bool b) : g1(g1), g2(g2), barrier(b) {}
};

int main()
{
	FAST;
	int N, M;
	cin >> N >> M;
	vector<vector<group>> chess(N + 1, vector<group>(N + 1, { 0, 0, false }));
	int c, r;
	for (int i = 0; i < M; i++) {
		cin >> c >> r;
		chess[c][r].barrier = true; // chess판에 장애물 표시
	}

	// '/'방향 그룹 생성
	bool gflag = false;
	int g1cnt = 0;
	for (int i = 1; i < 2 * N; i++) {
		r = i; c = 1; gflag = false; g1cnt++; // 새로운 대각선, gcnt 증가
		while (r >= 1 && c <= N) {
			if (r <= N) {
				if (chess[r][c].barrier) { gflag = true; }
				else {
					if (gflag) { gflag = false; g1cnt++; }
					chess[r][c].g1 = g1cnt;
				}
			}
			r--; c++;
		}
	}

	// '\' 방향 그룹 생성
	int g2cnt = 0;
	for (int i = 1; i < 2 * N; i++) {
		r = i, c = N; gflag = false; g2cnt++; // 새로운 대각선, gcnt 증가
		while (r >= 1 && c >= 1) {
			if (r <= N) {
				if (chess[r][c].barrier) { gflag = true; }
				else {
					if (gflag) { gflag = false; g2cnt++; }
					chess[r][c].g2 = g2cnt;
				}
			}
			r--; c--;
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