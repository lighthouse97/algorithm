// 2004.cpp
// ���� 0�� ����
// ������ ������ ���캸�� N!/(M!*(N-M)!) �̹Ƿ�,
// N(2,5�� ����) - M(2,5�� ����) - (N-M)(2,5�� ����)
// 2, 5 �� ���� ���� ���Ѵ�.

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