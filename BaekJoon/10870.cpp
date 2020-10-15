// 10870.cpp
// Fibonacci

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

int fibo[21] = { 0, };

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int i;
	int n;

	for (i = 0; i < 21; i++) {
		fibo[i] = (i == 0) ? 0 : (i == 1) ? 1 : fibo[i - 1] + fibo[i - 2];
	}

	cin >> n;
	if (n >= 0 && n <= 20)
		  cout << fibo[n] << "\n";
}