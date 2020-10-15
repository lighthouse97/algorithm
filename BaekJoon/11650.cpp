// 11650.cpp
// 좌표정렬
// x, y 좌표가 모두 같은 두 점은 없다.
// qsort를 사용해야 한다.
// 단순 무식하게 기계적으로 풀려면 방법이 없다!

#include "pch.h"
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
//#include <iostream>
#include <cstdio>
#include <cstdlib> // qsort

using namespace std;

const int max_cnt = 100000;
int num_array[max_cnt][2] = { {0,0}, };

int comp_func(const void* a, const void* b)
{
	const int* e1 = (const int*)a;
	const int* e2 = (const int*)b;
	if (e1[0] > e2[0]) return 1; // a > b 일때, > 0 이면 오름차순
	else if (e1[0] == e2[0]) {
		return (e1[1] - e2[1]); // a < b 일때, < 0 이면 내림차순 
	}
	return -1;
}

int main()
{
	int N, numx, numy;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &numx, &numy);
		num_array[i][0] = numx;
		num_array[i][1] = numy;
	}
	qsort(num_array, N, sizeof(int) * 2, comp_func);
	for (int i = 0; i < N; i++)
		printf("%d %d\n", num_array[i][0], num_array[i][1]);
}