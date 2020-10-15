// 10809.cpp

#include "pch.h"
#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	char arr[102] = { 0, };
	int occur[26];
	int i = 0;
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	for (i = 0; i < 26; i++) occur[i] = -1;

	fgets(arr, 102, stdin);

	for (i = 0; i < 102; i++) {
		if (arr[i] < 'a' || arr[i] > 'z') break;
		if (occur[arr[i] - 'a'] == -1) occur[arr[i] - 'a'] = i;
	}
	for (i = 0; i < 26; i++)
		cout << occur[i] << " ";
	cout << "\n";
}
