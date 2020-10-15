// 2775.cpp
// 부녀회장, 피보나치 수열 응용

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

int count_func(int floor, int num)
{
	if (num == 1) return 1;
	if (floor == 0) return num;

	return (count_func(floor, num - 1) + count_func(floor-1, num));
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int floor, num, count;
	int T;
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> floor >> num;
		if ((floor >= 1 && floor <= 14) && (num >= 1 && num <= 14)) {
			count = count_func(floor, num);
			cout << count << "\n";
		}
	}
}
