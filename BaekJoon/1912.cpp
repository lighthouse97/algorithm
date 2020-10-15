// 1912.cpp
// 연속합(연속된 수의 합 중 가장 큰 값을 구한다.)
// 역시 전형적인 DP문제이고 DP로 푼다.
// 점화식
// DP[1] = AR[1]
// DP[i] = max(DP[i-1] + AR[i], AR[i])
// DP[i] 중 가장 큰 값을 구한다.
// ex :
// AR[i] 10 -4 03 01 05 06 -35 12 21 -1
// DP[i] 10 06 09 10 15 21 -14 12 33 32
// maxval = 33

#include "pch.h"
#include <iostream>
//#include <cstdio>
//#include <utility> // pair
//#include <vector> // vector
#include <algorithm> // max
//#include <string>

using namespace std;
int DP[100001] = { 0, };
int AR[100001] = { 0, };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N, maxval = -2000;
	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> AR[i];
		if (i == 1) DP[i] = AR[i];
		else {
			DP[i] = max(DP[i - 1] + AR[i], AR[i]);
		}
		maxval = max(DP[i], maxval);
	}
	cout << maxval << "\n";
}