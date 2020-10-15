// 11050,cpp
// 이항계수 1
// 조합(nCr)을 구하는 문제이다.

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

int factorial(int n)
{
	int result = 1;
	for (int i = n; i >= 1; i--)
		result *= i;
	return result;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, K;
	cin >> N >> K;

	cout << factorial(N) / (factorial(K)*factorial(N - K)) << "\n";
}