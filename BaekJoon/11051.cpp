// 11051.cpp
// 이항 계수 2
// 이항 계수 1에서와 같이 Factorial을 이용해서 풀면 수의 범위가 커서 시간초과가 발생한다.
// 이 때는 파스칼의 삼각형을 이용한 다음의 공식을 이용한다. (재귀함수로 푼다.)
// nCr = (n-1)C(r-1) + (n-1)Cr
// 동시에 이전 값을 저장하는 동적프로그래밍을 이용한다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair

using namespace std;

int DP[1001][1001] = { {0,}, };
const int mod = 10007;

int combination(int n, int r)
{
	if (r == 0 || n == r) return 1;
	if (DP[n][r] != 0) return DP[n][r];
	DP[n][r] = combination(n - 1, r - 1) + combination(n - 1, r);
	return (DP[n][r] % mod);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, K;
	cin >> N >> K;

	cout << combination(N, K) << "\n";
}