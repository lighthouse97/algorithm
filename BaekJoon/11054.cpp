// 11054.cpp
// 가장 바이토닉 부분 수열
// 동적 프로그램이고 11053의 가장 긴 증가하는 부분 수열과
// 가장 긴 감소하는 부분 수열의 짬뽕이다.
// 즉 i번째까지 증가하는 부분 수열과 i번째부터 감소하는 부분수열의 합이
// 가장 큰 것을 고른다. 합에서 peak값이 중복되므로 1을 빼야 한다.
// 앞에서 한 것을 응용한 것인데... 이 단순한 아이디어가 언제쯤 빠르게 떠오를까???

#include "pch.h"
#include <iostream>
//#include <cstdio>
//#include <utility> // pair
//#include <vector> // vector
#include <algorithm> // max
//#include <string>

using namespace std;

int UPDP[1001] = { 0, };
int DOWNDP[1001] = { 0, };
int AR[1001] = { 0, };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N, maxval = 1;
	cin >> N;

	// i번째의 증가하는 부분수열의 길이를 구한다.
	for (int i = 1; i <= N; i++) {
		cin >> AR[i];
		UPDP[i] = 1;
		for (int j = 1; j < i; j++) {
			if (AR[j] < AR[i]) {
				UPDP[i] = max(UPDP[j] + 1, UPDP[i]);
			}
		}
	}
	// i번째부터 감소하는 부분수열의 길이를 구한다.
	// i = N번째부터 i+1번째까지 증가하는 부분수열의 길이를 구한다.
	for (int i = N; i >= 1; i--) {
		DOWNDP[i] = 1;
		for (int j = N; j >= i+1; j--) {
			if (AR[j] < AR[i]) {
				DOWNDP[i] = max(DOWNDP[j] + 1, DOWNDP[i]);
			}
		}
	}

	for (int i = 1; i <= N; i++)
		maxval = max(maxval, UPDP[i] + DOWNDP[i]);

	// i번째가 UP, DOWN에서 중복되므로 1을 뺀다.
	cout << maxval - 1 << "\n";
}