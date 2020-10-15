// 10039.cpp

#include "pch.h"
#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int score[10] = { 0, };
	int i = 0, sum = 0;

	for (i = 0; i < 5; i++) {
		cin >> score[i];
		sum += ((score[i] < 40) ? 40 : score[i]);
	}

	cout << sum / 5 << "\n";
}