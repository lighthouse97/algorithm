// 1157.cpp

#include "pch.h"
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

const int maxc = 1000002;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	char arr[maxc] = { 0, };
	int alpha[26] = { 0, };
	int mcount = 0;
	char found;

	fgets(arr, maxc, stdin);

	for (int i = 0; i < maxc; i++) {
		if (arr[i] >= 'a' && arr[i] <= 'z') arr[i] = arr[i] - 32;
		else if (arr[i] < 'A' || arr[i] > 'Z') break;
		alpha[arr[i] - 'A']++;
	}

	for (int j = 0; j < 26; j++) {
		if (alpha[j] > mcount) {
			mcount = alpha[j];
			found = j + 'A';
		}
	}

	for (int k = 0; k < 26; k++) {
		if ((alpha[k] == mcount) && (k + 'A' != found)) {
			found = '?';
			break;
		}
	}

	cout << found << "\n";
}