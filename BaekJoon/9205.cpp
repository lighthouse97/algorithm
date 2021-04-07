// 9205.cpp
// 맥주 마시면서 걸어가기
// ICPC > Regionals > Europe > Northwestern European Regional Contest > German Collegiate Programming Contest > GCPC 2013 D번
// Floyd-Warshall 문제이다.
// 편의점들과 출발점, 도착점이 모든 정점이 되며(N + 2), 모든 정점들 사이의 거리(맨해튼 거리)를 맥주 1박스(20개)로
// 갈 수 있는지 계산하여 갈 수 있으면 1, 갈 수 없으면 0으로 표시한다.
// 그리고 Floyd-Warshall 알고리즘을 돌리는데, 경로의 최소값을 구하는 것이 아니라 갈 수 있는 경로인지 아닌지를 산출해 낸다.
// 그래서 마지막으로 출발점에서 도착점까지 갈 수 있으면 "happy" 아니면 "sad"를 표시한다.
// 최소값을 구하는 것이 아니기 때문에,
// 예를 들어 경로 1->3이 0일때, 1->2, 2->3의 경로가 있으면 경로 1->3 = (1->2)*(2->3)으로 업데이트 된다.
// 만일 1->3이 1이면 갈 수 있는 경로가 우선이므로 더 업데이트 할 필요가 없다!!!
// 제한시간 1초 중 12ms(2,056KB)가 소요되었다.
// 맞은사람 1848/3515로 상위 52.57%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
#include <cstdlib> // abs
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
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int g_graph[103][103] = { {0, } };
int g_N; // 편의점의 수

struct point {
	int x, y;
	point() : x(0), y(0) {}
	point(int x, int y) : x(x), y(y) {}
	bool canGo(const point& rhs) {
		return (abs(x - rhs.x) + abs(y - rhs.y) > 1000 ? false : true); // 50 * 20 = 1000
	}
};

void floyd_warshall()
{
	for (int k = 1; k < g_N + 3; k++) {
		for (int i = 1; i < g_N + 3; i++) {
			for (int j = 1; j < g_N + 3; j++) {
				if (!g_graph[i][j]) // 갈 수 없는 경우만 따진다.
					g_graph[i][j] = g_graph[i][k] * g_graph[k][j];
			}
		}
	}
}

void doTest()
{
	cin >> g_N;
	int x, y;
	point loc[103];
	for (int i = 1; i < g_N + 3; i++) {
		cin >> x >> y;
		loc[i] = { x, y };
	}
	for (int i = 1; i < g_N + 3; i++) { // initialize g_graph
		for (int j = 1; j < g_N + 3; j++) {
			if (loc[i].canGo(loc[j])) { g_graph[i][j] = 1; g_graph[j][i] = 1; }
			else { g_graph[i][j] = 0; g_graph[j][i] = 0; }
		}
	}
	floyd_warshall();
	cout << (g_graph[1][g_N + 2] == 1 ? "happy" : "sad") << "\n";
}

int main()
{
	FAST;
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) doTest();
}