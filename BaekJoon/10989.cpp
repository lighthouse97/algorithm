// 10989.cpp
// ��������
// O(n^2) : *��������, �������� (2750)
// O(nlogn) : ������, *�������� (2751)
// O(n) : *ī��Ʈ���� (10989) --> �ܼ��ؼ� �ӵ��� ���� �������� �޸� ���� Ŀ�� �ִ밪�� ���� ��쿡 �ַ� ����Ѵ�.

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
	// ������ �迭 �� �׸��� ������ calc �迭�� �����Ѵ�.
	for (int i = 0; i < count; i++) {
		calc[nums[i]]++;
	}
	// calc �迭 �� �׸��� �������� ����Ѵ�.
	for (int i = 2; i <= max; i++) {
		calc[i] = calc[i - 1] + calc[i];
	}
	// sorting�Ѵ�.
	for (int i = count - 1; i >= 0; i--) {
		sort[--calc[nums[i]]] = nums[i];
	}
	// sortng�� ����� nums�迭�� �����Ѵ�.
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