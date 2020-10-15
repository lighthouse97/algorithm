// 2004.cpp
// 조합 0의 갯수
// 조합의 원리를 살펴보면 N!/(M!*(N-M)!) 이므로,
// N(2,5의 갯수) - M(2,5의 갯수) - (N-M)(2,5의 갯수)
// 2, 5 중 작은 수를 택한다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair

using namespace std;

int countNum2(int N)
{
	int num = N, count = 0;
	while (num) {
		count += num / 2;
		num /= 2;
	}
	return count;
}

int countNum5(int N)
{
	int num = N, count = 0;
	while (num) {
		count += num / 5;
		num /= 5;
	}
	return count;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m, count;
	cin >> n >> m;
	count = min(countNum2(n) - countNum2(m) - countNum2(n-m),
		countNum5(n) - countNum5(m) - countNum5(n - m));

	cout << count << "\n";
}