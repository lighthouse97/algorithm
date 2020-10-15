// 2577.cpp

#include "pch.h"
#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int a, b, c;
	int multi = 0, i = 0;
	int arr[10] = { 0, };
	
	cin >> a >> b >> c;
	if ((a >= 100 && a < 1000) &&
		(b >= 100 && b < 1000) &&
		(c >= 100 && c < 1000)) {

		multi = a * b * c;
		while (multi) {
			arr[multi % 10]++;
			multi /= 10;
		}

		for (i = 0; i < 10; i++)
			cout << arr[i] << "\n";
	}
}