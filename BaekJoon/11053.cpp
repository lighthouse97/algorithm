// 11053.cpp
// 가장 긴 증가하는 부분 수열
// 동적 프로그램이므로 점화식을 만들어야 한다.
// DP[1] = 1
// DP[2] = 1(1로 초기화)
// DP[2] = (AR[1] < AR[2]) ? DP[1] + 1 : DP[2]
// for(int iter=1; iter<=N, i++)
// DP[iter] = 1(1로 초기화)
// DP[iter] = for(int i=1; i<iter; i++) { (AR[i] < AR[iter]) ? MAX(DP[i] + 1, DP[iter]) : DP[iter] }
// 1부터 i-1번째까지 순차적으로 크기를 검사한다.
// max_value = max(DP[iter], max_value); // DP[1]~DP[N]중 가장 큰 값을 출력

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
			if (AR[j] < AR[i]) {
				DP[i] = max(DP[j] + 1, DP[i]);
			}
		}
		maxval = max(DP[i], maxval);
	}
	cout << maxval << "\n";
}
