// 12865_1.cpp
// 평범한 배낭
// Knapsack 문제이고 DP를 이용해서 푼다.
// 12865는 반복문을 이용해서 풀었고, 이번에는 재귀함수를 이용해서 푼다.
// 재귀적 방법이 잦은 함수호출로 시간은 더 걸리지만 이해하기가 보다 더 직관적이다.
// 점화식은 다음과 같다.
//  f(i,w)가 w무게 담을 수 있는 배낭에 물건 i를 넣을 때 가치의 최대값이라 한다면,
// f(i,w) = max(f(i+1, w - item[i].w) + item[i].v, f(i+1, w))
// max의 첫번째는 i를 넣고 다음번 물건을 넣을 때의 최대 가치
// 두번째는 i를 넣지 않고 다음번 물건을 넣을 때의 최대 가치
// 이를 재귀적으로 i가 N보다 클때까지 반복 호출한다.
// 72ms, 41440KB 소요된다. 반복문 방식은 8ms, 2380KB 소요된다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
#include <cstring> // memset
//#include <vector>
#include <algorithm> // max
//#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair

using namespace std;

int DP[101][100001];
int ITEM[101][2] = { {0, }, }; // 0 : weight, 1 : value

int N, W;

int function(int i, int w)
{
	int ret = 0;
	if (i > N) return 0;
	if (DP[i][w] >= 0) return DP[i][w];
	//else DP[i][w] = 0;

	if (ITEM[i][0] <= w) ret = max(function(i + 1, w - ITEM[i][0])  + ITEM[i][1], function(i + 1, w));
	else ret = function(i + 1, w);
	DP[i][w] = ret;
	return ret;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	memset(DP, -1, sizeof(DP));
	cin >> N >> W;
	for (int i = 1; i <= N; i++)
		cin >> ITEM[i][0] >> ITEM[i][1];

	cout << function(1, W) << "\n";
}