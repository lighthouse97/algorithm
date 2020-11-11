// 11003_2.cpp
// 최솟값 찾기
// 이번에는 직접 동적 프로그래밍으로 풀어보았다.
// 역시 예상한 대로 시간초과(TLE : Time Limit Exceeded)가 발생하였다.

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>

#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
	FAST;

	const int maxval = 1111111111;
	int N, L;
	vector<int> A;
	vector<int> DP;

	cin >> N >> L;
	A.resize(N + 1, 0);
	DP.resize(L, 0);
	A[0] = maxval;
	for (int i = 1; i < N + 1; i++)
		cin >> A[i];

	for (int i = 0; i < N + 1; i++) {
		for (int j = L - 1; j >= 0; j--) {
			if (i == 0) DP[j] = maxval;
			else {
				DP[j] = (j == 0 ? A[i] : min(DP[j - 1], A[i]));
				if (j == L - 1) cout << DP[j] << " ";
			}
		}
	}
	cout << "\n";
}