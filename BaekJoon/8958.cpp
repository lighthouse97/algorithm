// 8958.cpp

#include "pch.h"
#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	int index = 0, sum = 0, total = 0;
	char arr[82] = { 0, };
	int n;
	cin >> n;
	cin.ignore();
	if (n > 0) {
		for (int i = 0; i < n; i++) {
			sum = total = index = 0;
			fgets(arr, 82, stdin);
			while (arr[index]) {
				if (arr[index] == 'O') sum++;
				else sum = 0;
				total += sum;
				index++;
			}
			cout << total << "\n";
		}
	}
}