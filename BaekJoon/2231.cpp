// 2231.cpp
// 분해합(생성자)

#include "pch.h"
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>

using namespace std;

int main()
{
	int length=0, sum, temp, i;
	int result = 0;
	int N;
	scanf("%d", &N);

	/*
	while (1) {
		length++;
		if (N / (10*length) == 0) break;
	}
	*/

	//for (i = N - 9 * length; i <= N; i++) {
	for (i = N - 54; i <= N; i++) {
		if (N <= 0) continue;
		sum = temp = i;
		while (temp) {
			sum += temp % 10;
			temp /= 10;
		}
		if (sum == N) break;
	}
	if (sum == N) result = i;
	printf("%d\n", result);
}