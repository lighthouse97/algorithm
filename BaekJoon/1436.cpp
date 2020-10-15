// 1436.cpp
// 영화감독 숌 (전형적인 brute force 문제이다)
// 5666 다음에 6666이 아니라 6660, 6661, ... 이런 경우를 고려해야 한다.

#include "pch.h"
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
	string snum;
	int N;
	scanf("%d", &N);

	for (int i = 666; ; i++) {
		snum = to_string(i);
		if (snum.find("666") != string::npos) N--;
		if (N == 0) {
			printf("%d\n", i);
			break;
		}
	}
}