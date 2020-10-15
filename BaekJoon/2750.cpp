// 2750.cpp
// 삽입정렬
// O(n^2) : 삽입정렬, 버블정렬
// O(nlogn) : 힙정렬, 병합정렬

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

int nums[1001] = { 0, };

void ins_sort(int n)
{
	int temp;
	for (int i = 1; i < n; i++) {
		for (int j = i; j > 0; j--) {
			if (nums[j - 1] > nums[j]) {
				temp = nums[j - 1];
				nums[j - 1] = nums[j];
				nums[j] = temp;
			}
		}
	}
}

int main()
{
	int N, num;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", &num);
		nums[i] = num;
	}
	ins_sort(N);

	for (int i = 0; i < N; i++)
		printf("%d ", nums[i]);
	printf("\n");
}