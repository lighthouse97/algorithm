// 2660.cpp
// 회장 뽑기
// Olympiad > 한국정보올림피아드 > KOI 1997 > 초등부 3번
// 역시 Floyd-Warshall 응용문제이다.
// 친구사이라 양방향으로 잡고 최단 거리를 구한다.
// 회원 i에 대해 모든 친구와의 거리가 가장 큰 값이 그 회원 점수가 된다.
// 이중 점수가 가장 작은 회원을 찾고 가장 작은 값과 이 값을 가진 회원의 갯수, 그리고 이 회원을 오름차순으로 출력하는 것이 관건이다.
// deque를 사용하면 되겠다.
// 제한시간 1초 중 0ms(2,020KB)가 소요되었다.
// 맞은사람 731/1848로 상위 39.55%에 rank되었다.

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
#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_graph;
int g_N;
const int INF = 987654321;

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

int main()
{
	FAST;
	cin >> g_N;
	g_graph.resize(g_N + 1, vector<int>(g_N + 1, INF));
	for (int i = 1; i < g_N + 1; i++) g_graph[i][i] = 0;
	int a, b;
	while (1) {
		cin >> a >> b;
		if (a == -1 && b == -1) break;
		g_graph[a][b] = 1;
		g_graph[b][a] = 1;
	}
	floyd_warshall();

	vector<int> score(g_N + 1, 0);
	int maxval;
	for (int i = 1; i < g_N + 1; i++) {
		maxval = 0;
		for (int j = 1; j < g_N + 1; j++) {
			if (g_graph[i][j] > maxval)
				maxval = g_graph[i][j];
		}
		score[i] = maxval;
	}
	deque<pair<int, int>> dq;
	dq.push_back({ 1, score[1] });
	for (int i = 2; i < g_N + 1; i++) {
		while (!dq.empty() && dq.back().second > score[i]) // 가장 작은 것만 앞으로 모은다.
			dq.pop_back();
		if (!dq.empty() && dq.back().second < score[i]) continue;
		dq.push_back({ i, score[i] });
	}
	cout << dq.front().second << " " << dq.size() << "\n";
	while (!dq.empty()) {
		cout << dq.front().first << " ";
		dq.pop_front();
	}
	cout << "\n";
}