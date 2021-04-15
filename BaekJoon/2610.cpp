// 2610.cpp
// 회의 준비
// Olympiad > 한국정보올림피아드 > 한국정보올림피아드시․도지역본선 > 지역본선 2004 > 중등부 3번
// Olympiad > 한국정보올림피아드 > 한국정보올림피아드시․도지역본선 > 지역본선 2004 > 고등부 3번
// floyd-warshall 응용 문제
// 1) 전체 구성원에 대해 floyd_warshall을 돌린다.
// 2) 각 구성원마다 도달할 수 있는 다른 구성원의 최단 경로 중 가장 큰 값을 배열에 저장한다.
// 3) DFS 돌려서 위원회 구성한다.
// 4) 구성한 위원회마다 2)의 값을 참고하여 위원회 멤버 중 가장 작은 값을 가진 멤버를 대표로 정하고 이를 배열에 저장한다.
// 5) 저장된 대표 리스트를 오름차순 정렬한다.
// 6) 5)의 대표의 수(= 위원회의 수)를 출력하고 5)의 정렬된 대표를 차례로 출력한다.
// 제한시간 1초 중 0ms(2,156KB)가 소요되었다.
// 맞은사람 688/1186로 상위 58.01%에 rank되었다.

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
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const int INF = 987654321;
int g_N;
vector<vector<int>> g_graph; // 전체 관계
vector<int> g_commit; // 개별 위원회
vector<int> g_maxr; // 각 구성원들의 최대 관계수
vector<bool> g_visited; // dfs 방문 여부

void floyd_warshall()
{
	for (int k = 1; k < g_N + 1; k++) {
		for (int i = 1; i < g_N + 1; i++) {
			for (int j = 1; j < g_N + 1; j++) {
				if (g_graph[i][k] + g_graph[k][j] < g_graph[i][j])
					g_graph[i][j] = g_graph[i][k] + g_graph[k][j];
			}
		}
	}
}

void dfs(int r)
{
	g_commit.push_back(r);
	g_visited[r] = true;
	for (int i = 1; i < g_N + 1; i++) {
		if (g_graph[r][i] != INF && !g_visited[i])
			dfs(i);
	}
}

int main()
{
	FAST;
	cin >> g_N;
	g_graph.resize(g_N + 1, vector<int>(g_N + 1, INF));
	g_maxr.resize(g_N + 1, 0);
	for (int i = 1; i < g_N + 1; i++) g_graph[i][i] = 0;
	int M, a, b;
	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		g_graph[a][b] = g_graph[b][a] = 1; // 양방향!
	}
	floyd_warshall();
	int maxval = 0;
	for (int i = 1; i < g_N + 1; i++) { // 각 구성원이 다른 구성원에 갈수있는 최단 경로 중 가장 긴 것을 구함
		maxval = 0;
		for (int j = 1; j < g_N + 1; j++) {
			if (g_graph[i][j] != INF) maxval = max(maxval, g_graph[i][j]);
		}
		g_maxr[i] = maxval;
	}
	g_visited.resize(g_N + 1, false);
	vector<int> leader;
	int minval = INF, candidate;
	for (int i = 1; i < g_N + 1; i++) { // 각 위원회 구함
		if (!g_visited[i]) {
			dfs(i);
			for (int x : g_commit) // 각 위원회 대표 구함
				if (g_maxr[x] < minval) { minval = g_maxr[x]; candidate = x; }
			leader.push_back(candidate);
			g_commit.clear();
			minval = INF;
		}
	}
	sort(leader.begin(), leader.end()); // 위원회 대표 정렬(오름차순)
	cout << leader.size() << "\n";
	for (int x : leader) cout << x << "\n";
}