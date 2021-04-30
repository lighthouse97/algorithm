// 7562.cpp
// 나이트의 이동
// University > Tu-Darmstadt Programming Contest > TUD Contest 2001 3번
// BFS 연습 문제이다.
// 문제에서 현재 위치에서 퀀의 이동 가능 방향이 모두 8 방향이다.
// 제한시간 1초 중 24ms(2,416KB)가 소요되었다.
// 맞은사람 2406/8798로 상위 27.34%에 rank되었다.

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
#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct point {
	int r, c;
	point() : r(0), c(0) {}
	point(int r, int c) : r(r), c(c) {}
};

int g_N;
vector<vector<int>> g_visited;

void bfs(const point& start, const point& end)
{
	int dr[8] = { +2, +2, +1, +1, -2, -2, -1, -1 };
	int dc[8] = { +1, -1, +2, -2, +1, -1, +2, -2 };
	queue<point> myq;
	myq.push(start);
	g_visited[start.r][start.c] = 0;
	point cur;
	int nr, nc;
	while (!myq.empty()) {
		cur = myq.front();
		myq.pop();
		if (cur.r == end.r && cur.c == end.c) break;
		for (int i = 0; i < 8; i++) {
			nr = cur.r + dr[i];
			nc = cur.c + dc[i];
			if (nr < 0 || nc < 0 || nr > g_N - 1 || nc > g_N - 1) continue;
			if (!g_visited[nr][nc]) {
				g_visited[nr][nc] = g_visited[cur.r][cur.c] + 1;
				myq.push(point(nr, nc));
			}
		}
	}
}

void doTest()
{
	cin >> g_N;
	g_visited.resize(g_N, vector<int>(g_N, 0));
	point s, e;
	cin >> s.r >> s.c;
	cin >> e.r >> e.c;
	bfs(s, e);
	cout << g_visited[e.r][e.c] << "\n";
	g_visited.clear();
}

int main()
{
	FAST;
	int t;
	cin >> t;
	while (t--) doTest();
}