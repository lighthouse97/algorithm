// 12865.cpp
// 평범한 배낭
// Knapsack 문제이고 DP를 이용해서 푼다.
// 물건들은 쪼갤 수 없고 하나씩만 있기 때문에 '0/1 Knapsack problem'이다.
// 재귀로 풀면 이해하기 더 쉽지만, 수행시간 고려하여 for loop로 풀기로 한다.
// 기본원리는 물건이 N개, 배낭이 W무게까지 담을 수 있으면,
// 물건1을 배낭에 넣을 때, 배낭의 빈 공간이 W ~ W-(물건1의무게)까지 각각 넣을 때
// 물건N을 배낭에 넣을 때, 배낭의 빈 공간이 W ~ W-(물건N의무게)까지 각각 넣을 때
// 의 모든 경우의 수(각각 가치의 최대값이 저장된다.)
// 점화식은 다음과 같다.
// DP[i][j]를 물건 i에 대해서 j만큼의 무게를 넣을 수 있을 때 가치의 최대값이라 하면,
// DP[i][j] = MAX(DP[i-1][j], DP[i][j - AR[i].w] + AR[i].v)
// (물건 i를 넣을 때의 가치에 남은 무게의 DP값을 더한다)
// 8ms, 2380KB 소요된다. 비교적으로 재귀함수를 이용한 방식(12865_1)은 72ms, 41440KB가 소요된다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
#include <algorithm> // max
//#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair

using namespace std;

int DP[100001] = { 0, };
int ITEM[101][2] = { {0, }, }; // 0 : weight, 1 : value

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, W;
	cin >> N >> W;
	//for (int i = 1; i <= N; i++)
	//	cin >> ITEM[i][0] >> ITEM[i][1];
		
	for (int i = 1; i <= N; i++) {
		cin >> ITEM[i][0] >> ITEM[i][1];
		for (int j = W; j >= ITEM[i][0]; j--) { // j를 오름차순으로하면 중복연산이라는데 그 이유는 잘 모르겠다.
			DP[j] = max(DP[j], DP[j - ITEM[i][0]] + ITEM[i][1]);
		}
	}
	cout << DP[W] << "\n";
}