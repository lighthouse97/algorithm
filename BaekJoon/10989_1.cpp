// 10989.cpp
// 병합정렬
// O(n^2) : *삽입정렬, 버블정렬 (2750)
// O(nlogn) : 힙정렬, *병합정렬 (2751)
// O(n) : *카운트정렬 (10989) --> 단순해서 속도는 가장 빠르지만 메모리 낭비가 커서 최대값이 작은 경우에 주로 사용한다.
// --> 카운트 정렬 알고리즘 원칙대로 하면 입력되는 숫자 모두를 배열에 저장해야 하는데, 최대갯수 10,000,000개를 모두 int type
//     으로 저장하면 40MByte가까운 메모리 공간이 소모되어 메모리 제약 사항 8MB를 넘어버린다.
//     따라서, 입력숫자 모두를 저장하지 않는 변형된 카운트 정렬 알고리즘을 사용한다.

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

const int MAX = 10000;
int count[MAX + 1] = { 0, };

int main()
{
	int N, num;
	int max = 0, cnt = 0;
	char result[10];
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", &num);
		count[num]++;
		max = (max < num) ? num : max;
	}
	for (int i = 0; i <= max; i++) {
		if (count[i]) {
			//for (int j = 0; j < count[i]; j++)
			//	printf("%d\n", i);
			// printf가 반복되는 출력에 시간이 걸려 puts로 대치
			sprintf(result, "%d", i);
			cnt = count[i];
			while (cnt--) puts(result);
		}
	}
}