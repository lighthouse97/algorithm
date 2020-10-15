// 2581.cpp
// find prime number II

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

	for (int i = 3; i*i <= n; i += 2) {
		if (n % i == 0) return false;
	}
	return true;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int M, N, sum = 0, min = 0;
	cin >> M >> N;

	min = N;
	for (int i = M; i <= N; i++) {
		if (is_prime_number(i)) {
			sum += i;
			min = (i < min) ? i : min;
		}		
	}
	if (sum == 0) cout << "-1\n";
	else {
		cout << sum << "\n";
		cout << min << "\n";
	}
}