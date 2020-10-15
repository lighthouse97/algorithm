// 2293.cpp
// 동전 1
// 동적프로그래밍에 보면 유사문제로 "동전2, 동전" 등이 있다.
// DP로 푼다.
// 예를 들어 10의 가치를 만드는데 1의 가치부터 10의 가치까지 순차적으로
// 증가시키면서 동전1만을 사용할때, 동전1,2만을 사용할때, 동전1,2,5만을 사용할때
// 각각의 경우에 대해서 점화식을 세우면 된다.
// 동전1만을 사용할 때는 1의가치 ~ 10의가치까지 경우의 수가 1가지씩만 있다.
// 동전2로 가치4를 만들려면 동전2에다 2가치(4-2)를 만드는 경우의 수가 2(2,11)이므로 2이고
// 동전1로 가치4를 만드는 경우가 1이므로 동전1,2로 가치4를 만드는 경우의 수는 1+2=3이된다.
// 이를 가지고 표를 만들면 최종 가치10을 만드는 모든 경우의 수가 10이 나온다.
// 점화식은 다음과 같다.
// 동전i로 j의 가치를 만들때 가능한 모든 경우의 수를 DP[i][j]라고 하면,
// DP[i][j] = DP[i-1][j] + DP[i][j - val[i]]
// j가치에 동전i가치를 뺀 나머지의 경우의 수에 이전의 동전(i-1)의 j가치까지의 경우의 수를 더한다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // max
//#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair

using namespace std;

int DP[10001] = { 0, };
int COIN[101] = { 0, };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, K;
	cin >> N >> K;
	DP[0] = 1;
	for (int i = 1; i <= N; i++) {
		cin >> COIN[i];
		for (int j = COIN[i]; j <= K; j++) {
			DP[j] = DP[j] + DP[j - COIN[i]];
		}
	}
	cout << DP[K] << "\n";
}