// 9020.cpp
// ∞ÒµÂπŸ»Â¿« √ﬂ√¯

#include "pch.h"
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

bool is_prime_number(int n)
{
	if (n == 1) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;

	for (int i = 3; i*i <= n; i += 2) {
		if (n % i == 0) return false;
	}
	return true;
}

int numbers[10000] = { 0, };

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T, N;
	for (int i = 2; i <= 10000; i++) {
		if (is_prime_number(i)) numbers[i] = 1;
	}

	scanf("%d", &T);
	for (int i = 0; i < T; i++) {
		cin >> N;
		for (int j = N / 2; j >= 2; j--) {
			if (j != 2 && j % 2 == 0) continue;
			if (numbers[j] && numbers[N - j]) {
				printf("%d %d\n", j, N - j);
				break;
			}
		}
	}
}