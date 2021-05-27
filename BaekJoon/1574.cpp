// 1574.cpp
// 룩 어택
// 이것도 체스판을 이용한 이분매칭(최대매칭) 문제이다.
// 앞에서 푼 1760 'N-Rook'문제에서 벽을 제외하고 구멍만 있는 경우로 보면 된다.
// 빈칸(구멍에 해당)도 같은 그룹으로 잡되, 이분 그래프 구성할 때, 빈칸 있는 부분은 매칭을 하지 않으면 된다.
// 제한시간 2초 중 16ms(3,744KB)가 소요되었다.
// 맞은사람 175/261로 상위 67.04%에 rank되었다.

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
	int option; // 장애물 타입, 0 : 가능한 칸, 1 : 빈칸
	group() : g1(0), g2(0), option(0) {}
	group(int g1, int g2, bool o) : g1(g1), g2(g2), option(o) {}
};

int main()
{
	FAST;
	int R, C, N;
	cin >> R >> C >> N;
	vector<vector<group>> chess(R + 1, vector<group>(C + 1, { 0, 0, 0 }));
	int a, b;
	for (int i = 0; i < N; i++) {
		cin >> a >> b;
		chess[a][b].option = 1;
	}

	// 수평 그룹 입력
	bool gflag = false;
	int g1cnt = 0;
	for (int i = 1; i < R + 1; i++) {
		g1cnt++;
		for (int j = 1; j < C + 1; j++) chess[i][j].g1 = g1cnt;
	}
	// 수직 그룹 입력
	int g2cnt = 0;
	for (int j = 1; j < C + 1; j++) {
		g2cnt++;
		for (int i = 1; i < R + 1; i++) chess[i][j].g2 = g2cnt;
	}

	// 이분 그래프 만들기
	g_graph.resize(g1cnt + 1);
	g_visited.resize(g2cnt + 1, false);
	g_matched.resize(g2cnt + 1, 0);
	for (int i = 1; i < R + 1; i++) {
		for (int j = 1; j < C + 1; j++) {
			if (!chess[i][j].option) g_graph[chess[i][j].g1].push_back(chess[i][j].g2);
		}
	}
	int answer = 0;
	for (int i = 1; i < g1cnt + 1; i++) {
		g_visited = vector<bool>(g2cnt + 1, false);
		if (dfs(i)) answer++;
	}
	cout << answer << "\n";
}