// 1181.cpp
// 단어정렬

#include "pch.h"
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
//#include <cstdio>
//#include <utility> // pair
//#include <vector> // vector
#include <algorithm> // sort
#include <string>

using namespace std;

bool compare(string a, string b)
{
	if (a.length() < b.length())
		return true;
	else if (a.length() > b.length())
		return false;
	return a < b;
}

int main()
{
	ios_base::sync_with_stdio(false);
	string words[20000];
	int N;
	cin >> N;
	//vector<string> words(N);
	for (int i = 0; i < N; i++)
		cin >> words[i];
	sort(words, words+N, compare);

	for (int i = 0; i < N; i++) {
		if (i > 0 && words[i - 1] == words[i])
			continue;
		cout << words[i] << "\n";
	}
}