// 11055.cpp
// 가장 큰 증가 부분 수열
// 가장 긴 증가하는 부분 수열(11053.cpp)의 응용이다.
// 이중 for문을 사용한 가장 긴 증가하는 부분 수열 방법을 응용해서
// 수가 증가할 때마다 길이 값이 아닌 누적된 크기를 저장해서
// 가장 큰 값을 출력한다.
// EX :
// 10 20 30 01 02
// 10
// 10 30
// 10 30 60
// 10 30 60
// 10 30 60 01 03

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
		DP[i] = AR[i];
		for (int j = 1; j < i; j++) {
			if (AR[j] < AR[i]) {
				DP[i] = max(DP[j] + AR[i], DP[i]);
			}
		}
		maxval = max(DP[i], maxval);
	}
	cout << maxval << "\n";
}