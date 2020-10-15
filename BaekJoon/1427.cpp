// 1427.cpp
// 소트 인사이드(문자열 정렬)

#include "pch.h"
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <cstdio>

using namespace std;

int counts[10] = { 0, };

int main()
{
	char numstr[20] = { 0, };
	scanf("%s", numstr);

	for (int i = 0; numstr[i] != 0; i++) {
		counts[numstr[i] - '0']++;
	}
	for (int i = 9; i >= 0; i--) {
		for (int j = counts[i]; j > 0; j--)
			printf("%d", i);
	}
	printf("\n");
}
