// 1436.cpp
// ��ȭ���� �� (�������� brute force �����̴�)
// 5666 ������ 6666�� �ƴ϶� 6660, 6661, ... �̷� ��츦 ����ؾ� �Ѵ�.

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

int main()
{
	string snum;
	int N;
	scanf("%d", &N);

	for (int i = 666; ; i++) {
		snum = to_string(i);
		if (snum.find("666") != string::npos) N--;
		if (N == 0) {
			printf("%d\n", i);
			break;
		}
	}
}