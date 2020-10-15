// 3036.cpp
// 링
// 최대공약수를 구하면 쉽게 구할 수 있는 문제이다.
// 첫번째 수와 두번째 ~ N번째 수까지 GCF를 구해서
// 각각의 GCF로 나눠서 분수 형태(A/B)로 표기한다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair

using namespace std;

int GCF(int A, int B)
{
	int large = A, small = B;
	int temp;
	if (A < B) {
		large = B;
		small = A;
	}
	while (small) {
		temp = large % small;
		large = small;
		small = temp;
	}
	return large;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, first, num, gcf;
	cin >> N;

	cin >> first;
	for (int i = 0; i < N-1; i++) {
		cin >> num;
		gcf = GCF(first, num);
		cout << (first / gcf) << "/" << (num / gcf) << "\n";
	}
}