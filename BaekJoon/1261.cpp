// 1261.cpp
// 알고스팟
// dijkstra algorithm 을 이용하여 최단 거리를 구하는 흔한 알고리즘 문제 중 하나이다.
// 참고로 전역변수 배열은 0만 자동으로 잡히고 나머지는 별도로 초기화 작업을 해주어야 한다.(fill_n() 같은...)
// 제한시간 1초 중 0ms(2,232KB)가 소요되었다.
// 맞은사람 2303/5508로 상위 41.81%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
//#include <vector>
//#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
#include <string> // string, stoi
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

struct room {
	int r, c, d; // row, column, distance
	room() : r(0), c(0), d(0) {}
	room(int r, int c, int d) : r(r), c(c), d(d) {}
	bool operator<(const room& rhs) const {
		return d > rhs.d; // for increasing order(오름차순 정렬)
	}
};

const int INF = 987654321;

int g_M, g_N;
int g_maze[101][101] = { {0, }, };
int g_dist[101][101];

void dijkstra()
{
	int adj[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
	priority_queue<room> mypq;
	mypq.push({ 1, 1, 0 });
	g_dist[1][1] = 0;
	while (!mypq.empty()) {
		room cur = mypq.top();
		mypq.pop();
		int ar, ac, dist;
		if (cur.d > g_dist[cur.r][cur.c]) continue; // queue의 값과 dist의 값 먼저 비교
		for (int i = 0; i < 4; i++) {
			ar = cur.r + adj[i][0]; // 인접 cell
			ac = cur.c + adj[i][1];
			if (ar < 1 || ac < 1 || ar > g_N || ac > g_M) continue;
			dist = cur.d + g_maze[ar][ac];
			if (dist < g_dist[ar][ac]) {
				g_dist[ar][ac] = dist;
				mypq.push({ ar, ac, dist });
			}
		}
	}
}

int main() {
	FAST;
	cin >> g_M >> g_N;

	string s;
	for (int i = 1; i < g_N + 1; i++) {
		cin >> s;
		for (int j = 0; j < s.length(); j++) {
			g_maze[i][j + 1] = s[j] - '0';
			g_dist[i][j + 1] = INF;
		}
	}
	dijkstra();
	cout << g_dist[g_N][g_M] << "\n";
}