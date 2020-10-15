// 2588.cpp
// °ö¼À

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int a, b;
	int mul1, mul2, mul3, result = 0;

	cin >> a >> b;
	mul1 = (b % 10)*a;
	mul2 = ((b / 10) % 10)*a;
	mul3 = (b / 100)*a;
	result = mul3 * 100 + mul2 * 10 + mul1;
	cout << mul1 << "\n";
	cout << mul2 << "\n";
	cout << mul3 << "\n";
	cout << result << "\n";
}