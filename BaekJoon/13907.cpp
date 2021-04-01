// 13907.cpp
// 세금(tax)
// University > 서강대학교 > 제12회 총장배 서강대학교 프로그래밍 대회 Champion H번
// University > 서강대학교 > 제12회 총장배 서강대학교 프로그래밍 대회 Master H번
// dijkstra or bellman-ford 둘 다 풀 수 있지만 dijkstra로 풀어보기로 한다.
// 세금에 따라 경로의 비용을 다르게 하고 각각 모두 dijkstra를 돌려보면 TLE가 발생한다.
// --- 틀린 방법!!! --------------------------------------------------------------------------------------------
// 목적지까지 경로의 수가 가장 작은 경로와 비용이 가장 작은 경로 2가지에 대해 각각 경로수, 비용을 저장한다.
// --> 이렇게 방향을 잡고 풀었는데 WA 발생! 처음부터 방향자체를 잘 못 잡았다. 이 두가지 중에 하나에서 가장 적은 비용이
//     나올거라고 방향을 잡은 것 자체가 잘못된 것이다. 따지고 보면 특정 세금에서 가장 적은 비용이 나오는 경로수는 하나하나
//     따져보지 않고는 어느 것일지 알 수가 없다 이다.
//     그렇다고 dijkstra를 K번 돌릴 수는 없으니 다른 방법을 찾아봐야 한다.
// ---------------------------------------------------------------------------------------------------------------
// 방법) dijkstra는 한번만 돌리되 dist 배열의 각 정점에서 0~N index의 배열을 만든다. index는 경로갯수, 값은 비용이 된다.
// 예를 들어, dist[2][3]은 정점 2에서 경로수 3을 거쳐왔을 때의 비용을 말한다.
// N개까지 만드는 이유는 최소 비용일 때의 경로수는 아무리 많아야 N - 1개이기 때문이다. N개이상부터는 중복 방문한다는 것인데,
// 간선의 비용이 0포함 양의정수인 이상 N개 이상부터는 최소 비용이 나올 수가 없기 때문이다.
// 출발점부터 dijkstra로 탐색할 때, 각 정점을 방문할 때마다 인접 정점의 dist배열에 거쳐온 경로수, 비용을 업데이트 한다.
// 그래서 기존에는 dist배열의 값에 최소비용 하나만 있었지만 여기에서는 방문 경로수별로 최소 비용이 여러개 저장이 되는 점이 다르다.
// 모든 정점에 대해 업데이트가 끝났으면 목적지 정점에 대해서,
// 여러 값중 가장 작은 값이 세금이 없을 때 최소 비용이다.
// 이후 K개의 세금에 대해서 각각의 누적값을 ai라고 하면, 목적지 모든 정점중 업데이트된 정점들에 대해서
// 'val[j] + j * ai'(j개의 경로수일때의 비용 + (j개의 경로 * ai))의 값들 중 가장 작은 값이 ai 세금에서의 최소 비용이 된다!!!!!
// 따져보면 그렇다! 세금 ai에서 목적지의 가능한 모든 경로수에서 하나씩 대입해서 가장 작은 값을 찾아낸다!
// 이렇게 하고 돌려보면 문제 없을 거 같지만 TLE가 발생한다. 다음의 추가 작업을 해 주어야 한다!
// 1) dist[i][j] 업데이트 할 때에, 정점 i에서 j경로수의 비용을 업데이트 한다는 것인데 현재 노드에서 j 경로수로 계산된 비용이
//    기존 dist[i][0] ~ dist[i][j]까지의 비용중 하나라도 더 크면 dist[i][j]는 업데이트할 필요가 없고 더 고려할 필요없이
//    queue에 추가하지 않는다. 왜? 더 적은 경로로 더 적은 비용이 있는데 굳이 더 많은 경로로 더 많은 비용을 추가한다는 것은
//    세금을 증가해도 최소 비용에 전혀 도움이 되지 않고 오히려 쓸데없는 연산만 늘어나기 때문이다.
//    그래서 dist[][] 업데이트하기 전에 이 부분을 반드시 적용해 주어야 한다!
// 2) dist[i][j] 업데이트 할 때에 j가 N까지 밖에 없으므로 '현재 노드의 경로수 + 1'로 j에 업데이트할 때 이값이 N을 넘지
//    않도록 체크해야 한다! 그럴리는 없겠지만 혹시 모를 안전장치로 넣어준다.
// 제한시간 2초 중 40ms(7,960KB)가 소요되었다.
// 맞은사람 43/304로 상위 14.14%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
#include <algorithm> // sort, max, min, copy, swap, unique
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

struct info {
	int num, cost, cnt; // next vertex(or count), cost
	info() : num(0), cost(0), cnt(0) {}
	info(int n, int c) : num(n), cost(c), cnt(0) {}
	info(int n, int c, int ct) : num(n), cost(c), cnt(ct) {}
	bool operator<(const info& rhs) const {
		return cost > rhs.cost;
	}
};

vector<vector<info>> g_graph; // to(city), cost
vector<vector<int>> g_cost; // N * (누적 경로 횟수(index), 누적 비용), g_cost[2][3] 은 노드2에서 누적경로수 3인 것의 누적비용이다.
vector<int> g_tax; // 누적 세금
int g_N, g_M, g_K; // 도시수, 도로수, 세금인상 횟수
int g_S, g_D; // 출발, 도착
const int INF = 999999999;
int g_minval = INF;

void dijkstra()
{
	priority_queue<info> mypq;
	mypq.push({ g_S, 0, 0 });
	g_cost[g_S][0] = 0;
	info cur; int val;
	while (!mypq.empty()) {
		cur = mypq.top();
		mypq.pop();
		bool noneed = false;
		for (int i = 0; i <= cur.cnt; i++) {
			if (cur.cost > g_cost[cur.num][i]) { noneed = true; break; }
		}
		if (noneed) continue;
		if (cur.num == g_D) { g_minval = min(g_minval, g_cost[cur.num][cur.cnt]); continue; } // 목표지점
		for (info& nex : g_graph[cur.num]) {
			val = g_cost[cur.num][cur.cnt] + nex.cost;
			if (cur.cnt + 1 <= g_N && val < g_cost[nex.num][cur.cnt + 1]) {
				g_cost[nex.num][cur.cnt + 1] = val;
				mypq.push({ nex.num, val, cur.cnt + 1 });
			}
		}
	}
}

int main() {
	FAST;
	cin >> g_N >> g_M >> g_K;
	cin >> g_S >> g_D;
	g_graph.resize(g_N + 1);
	g_cost.resize(g_N + 1, vector<int>(g_N + 1, INF));
	g_tax.resize(g_K, 0);
	int a, b, w;
	for (int i = 0; i < g_M; i++) {
		cin >> a >> b >> w;
		g_graph[a].push_back({ b, w }); // 양방향
		g_graph[b].push_back({ a, w });
	}
	for (int i = 0; i < g_K; i++) { // 세금 입력
		cin >> g_tax[i];
		if (i > 0) g_tax[i] += g_tax[i - 1];
	}
	dijkstra();

	cout << g_minval << "\n";
	int answer = INF;
	for (int x : g_tax) {
		answer = INF;
		for (int i = 0; i <= g_N; i++) {
			if (g_cost[g_D][i] != INF) {
				answer = min(answer, g_cost[g_D][i] + i * x); // i개의 경로수일때의 비용 + i개경로 * 세금
			}
		}
		cout << answer << "\n";
	}
}