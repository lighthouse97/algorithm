// 2108.cpp
// ���

#include "pch.h"
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
//#include <iostream>
//#include <string>
//#include <vector>
#include <cstdio>
//#include <cstdlib> // abs
#include <cmath> // round
#include <algorithm> // sort, min, max

using namespace std;

int arr[500001] = { 0, };
int occur[8001] = { 0, };

int main()
{
	int N, num;
	int sum = 0;
	double avg = 0.;
	int maxval = 0, cnt = 0, repeat = 0;
	int mid;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &arr[i]);
		occur[arr[i] + 4000]++;
		sum += arr[i];
		num = occur[arr[i] + 4000];
		if (maxval < num) {
			maxval = num;
			cnt = 0;
		}
		else if (maxval == num) {
			cnt++; // �ֺ�� ���� ���� ���� �� �ִ� ���
		}
	}
	avg = (double)sum / N;
	avg = round(avg); // ���(�Ҽ����ڸ� �ݿø�)
	sort(arr + 1, arr + N + 1);
	mid = arr[N / 2 + 1]; // �߾Ӱ�
	printf("%d\n", (int)avg); // �ż���� ���
	printf("%d\n", mid); // �߾Ӱ� ���
   // �ֺ��
	for (int i = 0; i <= 8000; i++) {
		if (occur[i] == maxval) {
			repeat++;
			if (!cnt) {
				printf("%d\n", i - 4000); // �ֺ�� ���
				break;
			}
			else {
				if (repeat == 2) {
					printf("%d\n", i - 4000); // ���� �ֺ�� �������� 2��° �� ���
					break;
				}
			}
		}
	}
	printf("%d\n", arr[N] - arr[1]); // ���� ���
}