// 4485.cpp
// ��� �� ���� �ְ� ������?(������ : Obstacle Course)
// ICPC > Regionals > North America > Pacific Northwest Regional > 2008 Pacific Northwest Region Programming Contest D��
// �� ������...��ǻ� 1261(�˰��� ������ �����ϴ�)
// �׷��� �˰��� ������ �״�� Ȱ���� ����� �Ѵ�.
// ���ѽð� 1�� �� 4ms(2,272KB)�� �ҿ�Ǿ���.
// ������� 571/3053�� ���� 18.70%�� rank�Ǿ���.

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

struct cave {
	int r, c, tr; // row, column, thief rupee
	cave() : r(0), c(0), tr(0) {}
	cave(int r, int c, int t) : r(r), c(c), tr(t) {}
	bool operator<(const cave& rhs) const {
		return tr > rhs.tr; // for increasing order(�������� ����)
	}
};

const int INF = 987654321;

int g_N;
int g_cave[126][126] = { {0, }, };
int g_cost[126][126];

void dijkstra()
{
	int adj[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
	priority_queue<cave> mypq;
	mypq.push({ 1, 1, g_cave[1][1] });
	g_cost[1][1] = g_cave[1][1];
	while (!mypq.empty()) {
		cave cur = mypq.top();
		mypq.pop();
		int ar, ac, cost;
		if (cur.tr > g_cost[cur.r][cur.c]) continue; // queue�� ���� dist�� �� ���� ��
		for (int i = 0; i < 4; i++) {
			ar = cur.r + adj[i][0]; // ���� cell
			ac = cur.c + adj[i][1];
			if (ar < 1 || ac < 1 || ar > g_N || ac > g_N) continue;
			cost = cur.tr + g_cave[ar][ac];
			if (cost < g_cost[ar][ac]) {
				g_cost[ar][ac] = cost;
				mypq.push({ ar, ac, cost });
			}
		}
	}
}

bool doTest(int t) {
	cin >> g_N;
	if (g_N == 0) return false;

	for (int i = 1; i < g_N + 1; i++) {
		for (int j = 1; j < g_N + 1; j++) {
			cin >> g_cave[i][j];
			g_cost[i][j] = INF;
		}
	}
	dijkstra();
	cout << "Problem " << t << ": " << g_cost[g_N][g_N] << "\n";
	return true;
}

int main()
{
	FAST;
	int t = 1;
	while (doTest(t++)) {}
}