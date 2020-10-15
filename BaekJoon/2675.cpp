// 2675.cpp

#include "pch.h"
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

int main()
{
	string alpha = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ\\$%*+-./:";
	int N;
	char arr[22];
	int repeat;

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> repeat;
		if (repeat >= 1 && repeat <= 8) {
			cin >> arr;

			for (int i = 0; i < 22; i++) {
				if (alpha.find(arr[i]) != string::npos) {
					for (int j = 0; j < repeat; j++)
						cout << arr[i];
				}
				else break;
			}
			cout << "\n";
		}
	}
}