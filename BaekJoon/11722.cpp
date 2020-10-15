// 11722.cpp
// 가장 긴 감소하는 부분 수열
// 동적 프로그램이므로 점화식을 만들어야 한다.
// 11053의 가장 긴 증가하는 부분수열의 반대로 응용하면 된다.

#include "pch.h"
#include <iostream>
//#include <vector>
#include <algorithm> // max

using namespace std;

int DP[1001] = { 0, };
int AR[1001] = { 0, };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N, maxval = 1;
	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> AR[i];
		DP[i] = 1;
		for (int j = 1; j < i; j++) {
			if (AR[j] > AR[i]) {
				DP[i] = max(DP[j] + 1, DP[i]);
			}
		}
		maxval = max(DP[i], maxval);
	}
	cout << maxval << "\n";
}