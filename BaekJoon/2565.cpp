// 2565.cpp
// 전깃줄
// A, B pair의 배열이 있을 때 A를 기준으로 오름차순 정렬을 하고
// B 수열에 대해서 LIS(Longest Increasing Sequence)를 구해서
// N - LIS가 구하는 값이 된다.
// 만일 교차하는 전깃줄이 없으면 LIS = N이 되어 없애야 하는 전깃줄의 갯수는 0이 된다. 

#include "pch.h"
#include <iostream>
//#include <vector>
#include <algorithm> // max, sort
#include <utility> // pair

using namespace std;

int DP[101] = { 0, };
pair<int, int> AR[101];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N, maxval = 0;
	cin >> N;

	AR[0].first = AR[0].second = 0;
	for (int i = 1; i <= N; i++)
		cin >> AR[i].first >> AR[i].second;
	sort(&AR[1], &AR[1] + N);

	for (int i = 1; i <= N; i++) {
		DP[i] = 1;
		for (int j = 1; j < i; j++) {
			if (AR[j].second < AR[i].second) {
				DP[i] = max(DP[j] + 1, DP[i]);
			}
		}
		maxval = max(DP[i], maxval);
	}
	cout << N - maxval << "\n";
}