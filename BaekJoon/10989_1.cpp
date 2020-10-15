// 10989.cpp
// ��������
// O(n^2) : *��������, �������� (2750)
// O(nlogn) : ������, *�������� (2751)
// O(n) : *ī��Ʈ���� (10989) --> �ܼ��ؼ� �ӵ��� ���� �������� �޸� ���� Ŀ�� �ִ밪�� ���� ��쿡 �ַ� ����Ѵ�.
// --> ī��Ʈ ���� �˰��� ��Ģ��� �ϸ� �ԷµǴ� ���� ��θ� �迭�� �����ؾ� �ϴµ�, �ִ밹�� 10,000,000���� ��� int type
//     ���� �����ϸ� 40MByte����� �޸� ������ �Ҹ�Ǿ� �޸� ���� ���� 8MB�� �Ѿ������.
//     ����, �Է¼��� ��θ� �������� �ʴ� ������ ī��Ʈ ���� �˰����� ����Ѵ�.

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
			// printf�� �ݺ��Ǵ� ��¿� �ð��� �ɷ� puts�� ��ġ
			sprintf(result, "%d", i);
			cnt = count[i];
			while (cnt--) puts(result);
		}
	}
}