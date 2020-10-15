// 1978.cpp
// find prime number

#include "pch.h"
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

	for (int i = 3; i*i<=n; i += 2) {
		if (n % i == 0) return false;
	}
	return true;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N, num, sum = 0;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> num;
		if (is_prime_number(num)) sum++;
	}
	cout << sum << "\n";
}