// 13549.cpp
// 숨바꼭질 3
// 이것도 최단경로(다익스트라) 문제이다.
// 기존 dijkstra방식처럼 priority_queue를 사용하면 같은 t에 대해 순서가 뒤죽박죽이라
// queue가 빌때까지 모두 다 돌려봐야 한다. 어차피 dijkstra 방식은 queue가 빌 때까지 모두 다 돌려야 한다.
// 중간에 target에 도착했을 때 빠져나오게 하려면 priority queue를 사용하면 안되고 순서대로 쌓이는 그냥 queue나 deque를 사용해야 한다.
// -> 출발점부터 점점 값을 키워가면서 도착했는지 여부를 따지게 하면 되므로 중간에 빠져나와도 가장 빠른 시간이 될 수 있다.
// 즉 dijkstra 방식과 꼭 같은 문제는 아니고, 비슷하게 따라 가면서 응용하는 문제이다. 오히려 bfs문제에 더 가까와 보인다.
// 제한시간 1초 중 20ms(3,692KB)가 소요되었다.
// 맞은사람 2485/4034로 상위 61.60%에 rank되었다.

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