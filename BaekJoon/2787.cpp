// 2787.cpp
// 흔한 수열 문제
// 이분 매칭인데 이분 그래프 구성하는 방법을 몰라서 어떻게 풀었는지 참고하였다.
// 알고 나면 간단한데 이거 알기가 너무 어렵다.
// N개의 수열이 있으면 N*N개의 check[i][j]배열을 만든다.
// i번째 수가 j일 때 j가 올 수 있으면 true, 올 수 없는 경우면 false를 기록한다
// 예를 들어, 2,3번째 최대값이 3이고 4,5번째 최소값이 4라고 한다면,
// 2, 3번째 수에 4이상은 올 수 없으므로 check[2][4~5], check[3][4~5]는 false가 된다
// 4, 5번째 수에 3이하는 올 수 없으므로 check[4][1~3], check[5][1~3]은 false가 된다
// 그리고 공통으로 3은 2~3번째에만 4는 4~5번째에만 올 수 있으므로 1번째에는 3, 4가 올 수 없다
// 따라서 check[1][3], check[1][4]은 false이다.
// 이렇게 표시해 놓고 check에서 갈 수 있는 경로만 이분 그래프로 만들고
// 최대 매칭을 구한다. 최대 매칭의 수가 N이면 해당 수열을 출력한다.
// N이 아니면 -1을 출력한다.
// 제한시간 1초 중 148ms(2,292KB)가 소요되었다.
// 맞은사람 95/169로 상위 56.21%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil, hypot
#include <vector>
//#include <list>
#include <algorithm> // sort, max, min, copy, swap, unique, fill
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

const int MAXN = 201;
vector<vector<int>> g_graph;
bool g_visited[MAXN] = { false, };
int g_matched[MAXN] = { 0, };
int g_num[MAXN] = { 0, };

bool dfs(int from)
{
	for (int to : g_graph[from]) {
		if (g_visited[to]) continue;
		else g_visited[to] = true;
		if (g_matched[to] == 0 || dfs(g_matched[to])) {
			g_matched[to] = from;
			g_num[from] = to;
			return true;
		}
	}
	return false;
}

int main()
{
	FAST;
	int N, M;
	cin >> N >> M;
	g_graph.resize(N + 1);

	bool check[MAXN][MAXN]; // MSVC에서는 VLA(Variable Length Array)를 지원하지 않아서 N -> MAXN으로 고쳤다!
	fill(&check[0][0], &check[N][N + 1], true); // check 배열 초기화
	int t, x, y, v;
	for (int i = 0; i < M; i++) { // 수열에 대한 설명 입력
		cin >> t >> x >> y >> v;
		if (t == 1) { // v가 최대값
			for (int j = x; j <= y; j++) {
				for (int k = v + 1; k <= N; k++) check[j][k] = false;
			}
		}
		else { // v가 최소값
			for (int j = x; j <= y; j++) {
				for (int k = 1; k <= v - 1; k++) check[j][k] = false;
			}
		}
		for (int i = 1; i <= x - 1; i++) check[i][v] = false; // 공통, x~y번째에만 v가 올 수 있다.
		for (int i = y + 1; i <= N; i++) check[i][v] = false;
	}

	for (int i = 1; i < N + 1; i++) { // check[][] 배열을 기반으로 이분 그래프 구성
		for (int j = 1; j < N + 1; j++)
			if (check[i][j]) g_graph[i].push_back(j);
	}

	int count = 0; // 이분 매칭
	for (int i = 1; i < N + 1; i++) {
		fill(g_visited, g_visited + MAXN, false);
		if (dfs(i)) count++;
	}
	if (count == N) {
		for (int i = 1; i < N + 1; i++) cout << g_num[i] << " ";
		cout << "\n";
	}
	else cout << -1 << "\n";
}