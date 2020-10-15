// 1932.cpp
// Á¤¼ö»ï°¢Çü

#include "pch.h"
#include <iostream>
//#include <cstdio>
//#include <utility> // pair
//#include <vector> // vector
#include <algorithm> // max, max_element
//#include <string>

using namespace std;

int dp[501] = { 0, };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N, value;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = i; j >= 1; j--) {
			cin >> value;
			dp[j] = max(dp[j]+value, dp[j-1]+value);
		}
	}
	cout << *max_element(dp + 1, dp + 1 + N) << "\n";
}