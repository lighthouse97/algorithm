// 1463.cpp
// dynamic programming beginners step

#include "pch.h"
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
//#include <iostream>
//#include <string>
//#include <vector>
#include <cstdio>
//#include <cstdlib> // abs
//#include <cmath>
//#include <algorithm> // min, max

using namespace std;

int count[1000001] = {0, };

void make_one(int n)
{
	for (int i = 2; i <= n; i++) {
		count[i] = count[i - 1] + 1;
		if(i % 2 == 0 && count[i] > count[i / 2] + 1) count[i] = count[i / 2] + 1;
		if(i % 3 == 0 && count[i] > count[i / 3] + 1) count[i] = count[i / 3] + 1;
	}
}

int main()
{
	int N;
	scanf("%d", &N);
	make_one(N);
	printf("%d\n", count[N]);
}
