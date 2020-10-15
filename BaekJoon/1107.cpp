// 1107.cpp
// �̰͵� �����ϰ� ����Ž��(brute force)�����̴�.
// ����Ž���� ������ ������ �ִ밪�� 500,000�� �ƴ� 1,000,000���� ��Ҵ�.
// 0~8 ��ư�� ������ ��� worst cast�� 999,999���� Ž���ؾ� �Ѵ�.

#include "pch.h"
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
//#include <string>
//#include <vector>
#include <cstdio>
#include <cstdlib> // abs
//#include <cmath>
#include <algorithm> // min, max

using namespace std;

const int MAXN = 1000000;
int xbtn[10] = { 0, }; // broken button

int digit_count(int num)
{
	int count = 0;
	do {
		count++;
		num /= 10;
	} while (num);

	return count;
}

int avalable(int num) 
{
	int tmp = num;
	do {
		if (xbtn[tmp % 10]) return 0;
		tmp /= 10;
	} while (tmp);
	return digit_count(num);
}

int main()
{
	int N;
	int wcnt, btn;
	int manual, tmp, digit, result = 0;
	int mincnt = 500000;
	scanf("%d", &N);
	scanf("%d", &wcnt);
	for (int i = 0; i < wcnt; i++) {
		scanf("%d", &btn);
		xbtn[btn] = 1;
	}
	manual = abs(N - 100);
	if (manual <= 2) { // +, -�� �� ���� ���
		printf("%d\n", manual);
		return 0;
	}
	else if (wcnt == 0) { // no broken button
		printf("%d\n", digit_count(N));
		return 0;
	}
	else if (wcnt == 10) { // all buttons broken
		printf("%d\n", manual);
		return 0;
	}
	
	/*
	for (int i = 0; i < MAXN; i++) {
		digit = avalable(i);
		if (digit) {
			tmp = digit + abs(i - N);
			mincnt = min(mincnt, tmp);
		}
	}
	*/
	for (int i = N; i <= MAXN; i++) {
		digit = avalable(i);
		if (digit) {
			tmp = digit + abs(i - N);
			mincnt = min(mincnt, tmp);
			break;
		}
	}
	for (int i = N; i >= 0; i--) {
		digit = avalable(i);
		if (digit) {
			tmp = digit + abs(i - N);
			mincnt = min(mincnt, tmp);
			break;
		}
	}
	result = min(manual, mincnt);
	printf("%d\n", result);
	return 0;
}