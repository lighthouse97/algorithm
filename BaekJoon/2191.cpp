// 2191.cpp
// 들쥐의 탈출
// 이분 매칭 문제인데 약간의 응용이 추가되어 dfs로 매칭시 간선뿐아니라 간선의 시간까지 고려해야 한다.
// 간선의 도달 시간은 간선간 '거리 / 속도'로 구하는데 두 x, y 좌표간의 거리는 hypot() 함수를 이용한다.
// 문제를 잘 읽어보면 살아남은 쥐가 아니라 잡아 먹히는 쥐를 구한다. 이거 제대로 안읽어서 WA 2번 발생했다!!!
// '1348 주차장'문제 풀기 전에 먼저 풀어봐야 할 문제이다.
// 실수가 있었다. 들쥐 - 구멍 시간 입력 부분에서 i, j loop만 있으면 되는데 실수로 i loop 밖에 i loop를 하나 더 넣고 돌렸다.
// 우연찮게 AC는 났지만 쓸데없이 loop를 많이 돌려 수행 시간이 더 걸려 순위가 거의 꼴찌로 나왔다!!!
// 이를 다시 바로 잡으니 시간이 16ms(2,176KB) -> 0ms(2,176KB) 으로 줄어들었다.
// 제한시간 2초 중 16ms(2,176KB)가 소요되었다.
// 맞은사람 291/314로 상위 92.67%에 rank되었다.
// ---> 다시!!
// 제한시간 2초 중 0ms(2,176KB)가 소요되었다.
// 맞은사람 244/316로 상위 77.21%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
#include <cmath> // pow, sqrt, fabs. ceil, hypot
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
vector<vector<double>> g_time; // 좌표에 도달하는 시간

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

struct loc {
	double x, y;
	loc() : x(0.0), y(0.0) {}
	loc(double x, double y) : x(x), y(y) {}
};

int main()
{
	FAST;
	int N, M, S, V;
	cin >> N >> M >> S >> V;
	g_graph.resize(N + 1);
	g_visited.resize(M + 1, false);
	g_matched.resize(M + 1, 0);
	g_time.resize(N + 1, vector<double>(M + 1, 0.0));
	vector<loc> rat(N + 1, { 0.0, 0.0 });
	vector<loc> hole(M + 1, { 0.0, 0.0 });
	double x, y;
	for (int i = 1; i < N + 1; i++) { cin >> x >> y; rat[i] = { x, y }; }// 들쥐 좌표 입력
	for (int i = 1; i < M + 1; i++) { cin >> x >> y; hole[i] = { x, y }; }; // 구명 좌표 입력	
	for (int i = 1; i < N + 1; i++) { // 들쥐 - 구멍 시간 입력
		for (int j = 1; j < M + 1; j++)
			g_time[i][j] = hypot(hole[j].x - rat[i].x, hole[j].y - rat[i].y) / V;
	}
	for (int i = 1; i < N + 1; i++) { // graph 만들기
		for (int j = 1; j < M + 1; j++)
			if (g_time[i][j] <= S) g_graph[i].push_back(j); // 시간내에 도착하는 구멍끼리만 매칭한다.
	}
	int answer = 0;
	for (int i = 1; i < N + 1; i++) {
		g_visited = vector<bool>(M + 1, false);
		if (dfs(i)) answer++;
	}
	cout << N - answer << "\n"; // 잡아먹히게 되는 수를 구한다.
}