// 1238.cpp
// 파티
// Olympiad > USA Computing Olympiad > 2006-2007 Season > USACO February 2007 Contest > Silver 3번
// 최단 경로 중 다익스트라(dijkstra) 알고리즘을 이용하는 응용문제이다.
// X -> N은 주어진 그래프에서 다익스트라 돌리면 되고(X에서 출발)
// N -> X는 주어진 그래프를 뒤집어서 다익스트라 돌리면 된다.(역시 X에서 출발)
// 제한시간 1초 중 0ms(2,420KB)가 소요되었다.
// 맞은사람 348/5174로 상위 6.72%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
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

struct town {
	int c, t;
	town() : c(0), t(0) {}
	town(int c, int t) : c(c), t(t) {}
	bool operator<(const town& rhs) const {
		return t > rhs.t; // 오름차순
	}
};

vector<vector<town>> g_graph1, g_graph2;
vector<int> g_dist1, g_dist2;
const int INF = 987654321;

void dijkstra(int s, int type)
{
	vector<vector<town>>* graph = (type == 0) ? &g_graph1 : &g_graph2;
	vector<int>* dist = (type == 0) ? &g_dist1 : &g_dist2;
	priority_queue<town> mypq;
	mypq.push({ s, 0 });
	(*dist)[s] = 0;
	town cur;
	while (!mypq.empty()) {
		cur = mypq.top();
		mypq.pop();
		if (cur.t > (*dist)[cur.c]) continue;
		for (town& x : (*graph)[cur.c]) {
			int tt = cur.t + x.t;
			if (tt < (*dist)[x.c]) {
				(*dist)[x.c] = tt;
				mypq.push({ x.c, tt });
			}
		}
	}
}

int main()
{
	FAST;
	int N, M, X;
	cin >> N >> M >> X;
	g_graph1.resize(N + 1);
	g_graph2.resize(N + 1);
	g_dist1.resize(N + 1, INF);
	g_dist2.resize(N + 1, INF);

	int s, e, t;
	for (int i = 0; i < M; i++) {
		cin >> s >> e >> t;
		g_graph1[s].push_back({ e, t });
		g_graph2[e].push_back({ s, t });
	}
	dijkstra(X, 1); // N -> X
	dijkstra(X, 0); // X -> N
	int maxval = 0, sum;
	for (int i = 1; i < N + 1; i++) {
		if (i == X) continue;
		sum = g_dist1[i] + g_dist2[i];
		if (sum > maxval) maxval = sum;
	}
	cout << maxval << "\n";
}