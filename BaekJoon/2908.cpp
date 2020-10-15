// 2908.cpp

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
	cin >> a >> b;

	a = (a % 10) * 100 + ((a / 10) % 10) * 10 + a / 100;
	b = (b % 10) * 100 + ((b / 10) % 10) * 10 + b / 100;

	cout << ((a > b) ? a : b) << "\n";
}