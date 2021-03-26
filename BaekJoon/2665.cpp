// 2665.cpp
// �̷θ����
// Olympiad > �ѱ������ø��ǾƵ� > KOI 1997 > ���� 2��
// �� ������ 1261(�˰���) ������ �����ϴٰ� �� �� �ִ�.
// ���ѽð� 1�� �� 0ms(2,172KB)�� �ҿ�Ǿ���.
// ������� 1180/2121�� ���� 55.63%�� rank�Ǿ���.

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
		return d > rhs.d; // for increasing order(�������� ����)
	}
};

const int INF = 987654321;

int g_N;
int g_maze[51][51] = { {0, }, };
int g_dist[51][51];

void dijkstra()
{
	int adj[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
	priority_queue<room> mypq;
	mypq.push({ 1, 1, g_maze[1][1] });
	g_dist[1][1] = g_maze[1][1];
	while (!mypq.empty()) {
		room cur = mypq.top();
		mypq.pop();
		int ar, ac, dist;
		if (cur.d > g_dist[cur.r][cur.c]) continue; // queue�� ���� dist�� �� ���� ��
		for (int i = 0; i < 4; i++) {
			ar = cur.r + adj[i][0]; // ���� cell
			ac = cur.c + adj[i][1];
			if (ar < 1 || ac < 1 || ar > g_N || ac > g_N) continue;
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
	cin >> g_N;

	string s;
	for (int i = 1; i < g_N + 1; i++) {
		cin >> s;
		for (int j = 0; j < s.length(); j++) {
			g_maze[i][j + 1] = (s[j] - '0') ^ 1; // 0 -> 1, 1 -> 0
			g_dist[i][j + 1] = INF;
		}
	}
	dijkstra();
	cout << g_dist[g_N][g_N] << "\n";
}