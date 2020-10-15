// 17404.cpp
// RGB거리(1149) 2
// 앞의 RGB거리를 참고로하여 동적프로그램으로 풀어보자!
// 좀 더 응용해야 하는데 86명밖에 못 푼 문제를 드디어 내 힘으로 풀었다!!!
// 방법은 다음과 같다.
// 기존 RGB거리 방법대로 기본적인 점화식은 다음과 같다.
// N개의 집 중에서 i번째 집까지 칠할 때 누적비용을 DP[i][0], DP[i][1], DP[i][2]라고 하고
// (각각 i번째 집을 R(0), G(1), B(2)로 칠할 때의 비용이다.)
// i번째 집을 R, G, B로 칠할 때의 비용을 각각 COST[i][0], COST[i][1], COST[i][2]라고 하면,
// DP[i][0] = min(DP[i-1][1], DP[i-1][2]) + COST[i][0]
// DP[i][1] = min(DP[i-1][0], DP[i-1][2]) + COST[i][1]
// DP[i][2] = min(DP[i - 1][0], DP[i - 1][1]) + COST[i][2]
// 가 되고 min(DP[N][0], DP[N][1], DP[N][2])가 최종적인 최소 비용이 된다.
// 그리고 DP[1][0], DP[1][1], DP[1][2]는 미리 구해 놓는다.
// 그런데, 마지막과 처음이 같으면 안되는 조건이 붙기 때문에 추가로 더 고려해야 한다.
// 최초에 R로 시작할 때로 고정하면 DP[1][1] = MAX, DP[1][2] = MAX로 설정하고 기존대로 풀다가 마지막에 DP[N][0] = MAX로 설정한다.
// 최초에 G로 시작할 때로 고정하면 DP[1][0] = MAX, DP[1][2] = MAX로 설정하고 기존대로 풀다가 마지막에 DP[N][1] = MAX로 설정한다.
// 최초에 B로 시작할 때로 고정하면 DP[1][0] = MAX, DP[1][1] = MAX로 설정하고 기존대로 풀다가 마지막에 DP[N][2] = MAX로 설정한다.
// 각각 1번씩 총 3번 함수 호출하여 각각의 함수호출 결과 중에서 가장 작은 값이 최종적인 최소 비용이 된다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <cstdlib> // abs
#include <vector>
#include <algorithm> // max, min, sort
//#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair
//#include <stack> // stack
//#include <bitset> // bitmask

using namespace std;

const int MAX_VAL = 987654321;
int N;
vector<vector<int>> COST;
vector<vector<int>> DP;

int calc_cost(int first)
{
	// i == 1
	for (int i = 0; i <= 2; i++) {
		if (i == first) DP[1][i] = COST[1][i];
		else DP[1][i] = MAX_VAL;
	}
	// i == 2 ~ N
	for (int i = 2; i <= N; i++) {
		DP[i][0] = min(DP[i - 1][1], DP[i - 1][2]) + COST[i][0];
		DP[i][1] = min(DP[i - 1][0], DP[i - 1][2]) + COST[i][1];
		DP[i][2] = min(DP[i - 1][0], DP[i - 1][1]) + COST[i][2];
	}
	// i == N
	if(DP[N][first] < MAX_VAL) DP[N][first] = MAX_VAL;
	
	return min({DP[N][0], DP[N][1], DP[N][2]});
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int temp = MAX_VAL;
	cin >> N;
	COST.resize(N + 1, vector<int>(3, 0));
	DP.resize(N + 1, vector<int>(3, 0));
	for (int i = 1; i <= N; i++)
		cin >> COST[i][0] >> COST[i][1] >> COST[i][2];

	// R first
	temp = min(temp, calc_cost(0));
	// G first
	temp = min(temp, calc_cost(1));
	// B first
	temp = min(temp, calc_cost(2));
	cout << temp << "\n";
}