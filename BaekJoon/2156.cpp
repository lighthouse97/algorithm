// 2156.cpp
// 포도주 시식
// 동적프로그래밍으로 푼다.(Dynamic Programming)
// 점화식을 만드는 것이 핵심인데 아직 직관이 부족해서 결국 남이 푼 것을 보고 이해밖에 하지 못했다.
// N=1) DP[1] = AR[1]
// N=2) DP[2] = AR[1] + AR[2]
// N=3) DP[3] = MAX(AR[2] + AR[3], AR[1] + AR[3]) (N=3일때부터 직관이 떠오르지 않았다!)
//      DP[3] = MAX(DP[2], DP[3]) ex) 30, 20 ,10
// N > 3 부터,
// N=i) DP[i] = MAX(DP[i-3] + AR[i-1] + AR[i], DP[i-2] + AR[i])
//      DP[i] = MAX(DP[i-1], DP[i])
       

#include "pch.h"
#include <iostream>
//#include <vector>
//#include <algorithm> // max

using namespace std;

int AR[10001] = { 0, };
int DP[10001] = { 0, };

int max(int a, int b)
{
	if (a >= b) return a;
	else return b;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N;
	cin >> N;

	for (int i = 1; i <= N; i++)
		cin >> AR[i];
	
	DP[1] = AR[1];
	DP[2] = AR[1] + AR[2];
	DP[3] = max(AR[2] + AR[3], AR[1] + AR[3]);
	DP[3] = max(DP[2], DP[3]);
	for (int i = 4; i <= N; i++) {
		DP[i] = max(DP[i - 3] + AR[i - 1] + AR[i], DP[i - 2] + AR[i]);
		DP[i] = max(DP[i - 1], DP[i]);
	}
	cout << DP[N] << "\n";
}