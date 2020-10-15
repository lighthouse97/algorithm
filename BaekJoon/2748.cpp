// 2748.cpp
// 피보나치 수열
// 보통 recursive로 구현하는데 시간제한이 있으므로 배열을 사용하여 구현하였다.
// 배열을 이용해서 이전의 값을 저장하고 참고하는 의미에서 동적계획법이라고 볼 수 있다.

#include "pch.h"
#include <iostream>
//#include <cstdio>
//#include <utility> // pair
//#include <vector> // vector
//#include <algorithm> // sort
//#include <string>

using namespace std;

long long num_list[91] = { 0, };

void pibonacci(int n)
{
	num_list[0] = 0;
	num_list[1] = 1;
	if (n >= 2) {
	  for (int i = 2; i <= n; i++) {
		  num_list[i] = num_list[i-2] + num_list[i-1];
	  }
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	int N;
	cin >> N;
	pibonacci(N);
	cout << num_list[N] << "\n";
}