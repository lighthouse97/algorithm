// 14002.cpp
// 가장 긴 증가하는 부분 수열 4
// 가장 긴 증가하는 부분 수열(11053)에서 수열의 길이 및 부분 수열도 출력한다.
// ex :
// AR[i] 10 20 30 25 20
// DP[i] 01 02 03 03 02 일 때,
// DP가 가장 큰 값에서부터 하나씩 감소하면서 해당 index의 AR값을 저장하여 출략한다.
// 25 20 10
// 10 20 25 (위 vector의 reverse 출력)

#include "pch.h"
#include <iostream>
//#include <cstdio>
//#include <utility> // pair
#include <vector> // vector
#include <algorithm> // max, reverse
//#include <string>

using namespace std;
int DP[1001] = { 0, };
int AR[1001] = { 0, };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N, maxval=1, index=1, comp;
	vector<int> subset;
	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> AR[i];
		DP[i] = 1;
		for (int j = 1; j < i; j++) {
			if (AR[j] < AR[i]) {
				DP[i] = max(DP[j] + 1, DP[i]);
			}
		}

		if (maxval < DP[i]) {
			maxval = DP[i];
			index = i;
		}
	}
	cout << maxval << "\n";
	comp = maxval;
	for (int i = index; i >= 1; i--) {
		if (DP[i] == comp) {
			subset.push_back(AR[i]);
			comp--;
		}
	}
	reverse(subset.begin(), subset.end());
	for (int i = 0; i < subset.size(); i++) cout << subset[i] << " ";
	cout << "\n";
}