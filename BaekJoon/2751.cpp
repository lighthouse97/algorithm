// 2751.cpp
// 병합정렬
// O(n^2) : *삽입정렬, 버블정렬 (2750)
// O(nlogn) : 힙정렬, *병합정렬 (2751)
// O(n) : *카운트정렬 (10989)

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

const int SIZE = 1000001;
int numbers[SIZE] = { 0, };
int sort[SIZE] = { 0, };

void merge(int first, int last)
{
	int mid = (first + last) / 2;
	int m = mid + 1;
	int left = first;
	int right = last;
	int k = first;
	int i;
	// printf("first = %d, last = %d\n", first, last);

	while (left <= mid && m <= right) {
		if (numbers[left] > numbers[m]) { // right is smaller
			sort[k++] = numbers[m++];
		}
		else if (numbers[left] < numbers[m]) { // left is smaller
			sort[k++] = numbers[left++];
		}
		else { // right and left is same
			sort[k++] = numbers[left++];
			sort[k++] = numbers[m++];
		}
	}

	if (left > mid) { // left is done
	  for (i = m; i <= right; i++)
			sort[k++] = numbers[i];
	}
	else { // right is done
		for (i = left; i <= mid; i++)
			sort[k++] = numbers[i];
	}

	for (i = first; i <= last; i++)
		numbers[i] = sort[i];
}

void merge_sort(int first, int last)
{
	int mid = (first + last) / 2;
	if (first < last) { // recursive call이 끝나는 조건
		merge_sort(first, mid);
		merge_sort(mid + 1, last);
		merge(first, last);
	}
}

int main()
{
	int N, num;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", &num);
		numbers[i] = num;
	}
	merge_sort(0, N - 1);
	
	for (int i = 0; i < N; i++)
		printf("%d\n", numbers[i]);
}