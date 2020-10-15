// 7568.cpp
// µ¢Ä¡

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

int phy[50][2] = { {0,} };
int ranks[50] = { 0, };

int main()
{
	int N;
	int x, y;
	int rank = 1;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d %d", &x, &y);
		phy[i][0] = x;
		phy[i][1] = y;
	}

	for (int i = 0; i < N; i++) {
		rank = 1;
		for (int j = 0; j < N; j++) {
			if (i == j) continue;
			if ((phy[i][0] < phy[j][0]) && (phy[i][1] < phy[j][1])) rank++;
		}
		ranks[i] = rank;
	}
	for(int i=0; i < N; i++)
	  printf("%d ", ranks[i]);
	printf("\n");
}