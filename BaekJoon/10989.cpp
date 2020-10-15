// 10989.cpp
// 병합정렬
// O(n^2) : *삽입정렬, 버블정렬 (2750)
// O(nlogn) : 힙정렬, *병합정렬 (2751)
// O(n) : *카운트정렬 (10989) --> 단순해서 속도는 가장 빠르지만 메모리 낭비가 커서 최대값이 작은 경우에 주로 사용한다.

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

void count_sort(int nums[], int count, int max)
{
	int* sort = new int[count];
	int* calc = new int[max+1];
	for (int i = 0; i <= max; i++) calc[i] = 0;
	// 정렬할 배열 각 항목의 갯수를 calc 배열에 저장한다.
	for (int i = 0; i < count; i++) {
		calc[nums[i]]++;
	}
	// calc 배열 각 항목의 누적값을 계산한다.
	for (int i = 2; i <= max; i++) {
		calc[i] = calc[i - 1] + calc[i];
	}
	// sorting한다.
	for (int i = count - 1; i >= 0; i--) {
		sort[--calc[nums[i]]] = nums[i];
	}
	// sortng된 결과를 nums배열에 복사한다.
	for (int i = 0; i < count; i++) {
		nums[i] = sort[i];
	}

	delete sort;
	delete calc;
}

int main()
{
	int N, num;
	int max = 0;
	scanf("%d", &N);
	int* nums = new int[N];

	for (int i = 0; i < N; i++) {
		scanf("%d", &num);
		nums[i] = num;
		max = (max < num) ? num : max;
	}
	count_sort(nums, N, max);
	for (int i = 0; i < N; i++) {
		printf("%d\n", nums[i]);
	}
}