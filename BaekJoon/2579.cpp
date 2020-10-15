// 2579.cpp
// 계단오르기

#include "pch.h"
#include <iostream>
//#include <cstdio>
//#include <utility> // pair
//#include <vector> // vector
#include <algorithm> // max
//#include <string>

using namespace std;

int dp[301] = { 0, };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N, stair, pstair;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> stair;
		if (i == 1) dp[i] = stair;
		else if (i == 2) dp[i] = stair + dp[i - 1];
		else if (i == 3) dp[i] = max(stair+pstair, stair+dp[i-2]);
		else dp[i] = max(dp[i-2] + stair, dp[i-3] + pstair + stair);
		pstair = stair;
	}
	cout << dp[N] << "\n";
}