// 11051_1.cpp
// 이항계수 2
// 이항계수(조합의 수)를 재귀적 방법이 아닌 반복문에 의해 구해본다.
// DP(N, R)에 대해 낮은 값부터 N까지 모두 구한다음(파스칼의 삼각형 이용)
// DP(N, R) 위치의 값을 출력하면 된다.
// recursive로 하나 반복문으로 하나 수행시간은 똑같이 4ms가 나왔다.
// 반복문을 좀 더 최적화 시켜야 겠다.
// 반복문으로하고 DP배열 및 알고리즘을 최적화시키니,
// (5900KB, 4ms) ==> (1992KB, 0ms) 으로 개선되었다.

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

#if 0 // 반복문으로 처리
int DP[1001][1001] = { {0,}, };
const int mod = 10007;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, K;
	cin >> N >> K;

	for (int i = 1; i <= N; i++) {
		for (int j = 0; j <= i; j++) {
			if (j == 0 || i == j) DP[i][j] = 1;
			else {
				DP[i][j] = DP[i - 1][j - 1] + DP[i - 1][j];
				DP[i][j] %= mod;
			}
		}
	}
	cout << DP[N][K] << "\n";
}
#else // 반복문 최적화
int DP[1001] = { 0, };
const int mod = 10007;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, K;
	cin >> N >> K;
	DP[0] = 1;
	for (int i = 1; i <= N; i++)
		for (int j = i; j >= 1; j--)
			DP[j] = (DP[j - 1] + DP[j]) % mod;
	
	cout << DP[K] << "\n";
}

#endif
