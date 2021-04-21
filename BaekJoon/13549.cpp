// 13549.cpp
// 숨바꼭질 3
// 이것도 최단경로(다익스트라) 문제이다.
// 모든 정점에 대해 거리가 아닌 시간의 최단 경로를 dijkstra로 구하는 문제이다.
// 그런데 문제의 조건이 시간과 거리가 비례하는 조건이 아니기 때문에(예로 거리*2가 거리는 더 멀지만 시간은 오히려 늘어나지 않는다)
// 시간에 대해 priority queue를 넣으면 최단 경로 탐색에 더 효율적이지 않다는 것이다.
// 일반적인 dijkstra에서는 priority queue를 사용함으로써 queue에 들어가는 갯수를 더 줄여줄 수 있지만,
// 이 문제의 경우는 당장의 짧은 시간 우선으로 한다고 해서 이 정점의 시간이 최적이라고 보장을 못하는 것이다.
// 따라서 queue의 갯수를 줄여주는 데 별로 기여도 못하고 오히려 순서 정렬한다고 연산시간만 더 늘어날 뿐이다.
// 그래서 이 경우는 priority queue를 사용하지 않고 그냥 queue를 사용하는 것이 더 연산시간이 빠르다.
// 물론 다른 solution인 deque를 사용하면 O(N)시간내에 처리할 수 있으므로 더 빠르게 처리가 된다.
// 제한시간 1초 중 20ms(3,692KB)가 소요되었다.
// 맞은사람 2485/4034로 상위 61.60%에 rank되었다.
// 그냥 queue를 사용했을 경우,
// 20ms(3,692KB) -> 4ms(3,192KB) 로 줄었다. 1947/4263로 상위 45.67%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
//#include <vector>
#include <algorithm> // sort, max, min, copy, swap, unique, fill_n
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

struct go {
	int m, t;
	go() : m(0), t(0) {}
	go(int m, int t) : m(m), t(t) {}
	bool operator<(const go& rhs) const {
		return t > rhs.t; // 거리에 대해 오름차순 정렬
	}
};

int g_N, g_K;
int g_dist[200001]; // 100000에서 *2할 경우 고려해야 한다
const int INF = 987654321;

void dijkstra()
{
	priority_queue<go> mypq;
	mypq.push({ g_N, 0 });
	g_dist[g_N] = 0;
	if (g_N == g_K) return; // N == K이면 더 해볼 것도 없다.
	else if (g_N > g_K) {
		g_dist[g_K] = g_N - g_K;
		return;
	}
	go cur;
	bool stop = false;
	while (!mypq.empty() && !stop) {
		cur = mypq.top();
		mypq.pop();
		if (cur.t > g_dist[cur.m]) continue;
		for (int i = 0; i < 3; i++) {
			int dist = (i == 0) ? cur.m - 1 : (i == 1) ? cur.m + 1 : 2 * cur.m;
			if (dist < 0 || dist > 200000) continue; // 현재 위치가 '-' 일경우 더 가는 것은 의미없다. 200000이 넘는 경우 + or *2로 더 가는 것도 의미가 없다.			
			int tt = (i < 2) ? cur.t + 1 : cur.t;
			if (tt < g_dist[dist]) {
				//printf("dist = %d, tt = %d\n", dist, tt);
				g_dist[dist] = tt;
				mypq.push({ dist, tt });
				//if(dist == g_K) stop = true; // +,-,* 다 한다. 1, 2 일 경우 고려
			}
		}
	}
}

int main()
{
	FAST;
	cin >> g_N >> g_K;
	fill_n(g_dist, 200001, INF);
	dijkstra();
	cout << g_dist[g_K] << "\n";
}