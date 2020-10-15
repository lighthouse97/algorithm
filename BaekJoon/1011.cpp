// 1011.cpp
// 문제 이해를 못해서 NAVER 참고하였다.

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

int count(unsigned int goal)
{
	int unit = 1;
	long long dist = 1;
	int cnt = 1;
	int flag = 0;

	while (1) {
		for (int i = 0; i < 2; i++) {
			dist += unit;
			if (dist > goal) {
				flag = 1;
				break;
			}
			cnt++;
		}
		if (flag) break;
		unit++;
	}
	return cnt;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T;
	unsigned int x, y;
	int cnt = 0;

	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> x >> y;
		cnt = count(y-x);
		cout << cnt << "\n";
	}
}