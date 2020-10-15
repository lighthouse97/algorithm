// 1904.cpp

#include "pch.h"
#include <iostream>
//#include <cstdio>
//#include <utility> // pair
//#include <vector> // vector
//#include <algorithm> // sort
//#include <string>

using namespace std;

unsigned int num_list[1000001] = { 0, };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N;
	cin >> N;
#if 0
	num_list[1] = 1;
	num_list[2] = 2;
	if (N >= 3) {
		for (int i = 3; i <= N; i++) {
			num_list[i] = (num_list[i-1] + num_list[i-2])%15746;
		}
	}
	cout << num_list[N] << "\n";
#else
	int sum = 0, pre = 1, ppre = 0;
	for (int i = 0; i < N; i++) {
		sum = (pre + ppre > 15746) ? (pre + ppre) - 15746 : pre + ppre;
		ppre = pre;
		pre = sum;
	}
	cout << sum << "\n";
#endif
}