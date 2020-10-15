// 5622.cpp

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
	
	char word[17];
	char dial[200] = { 0, };
	int duration = 0;
	dial['A'] = 2; dial['B'] = 2; dial['C'] = 2;
	dial['D'] = 3; dial['E'] = 3; dial['F'] = 3;
	dial['G'] = 4; dial['H'] = 4; dial['I'] = 4;
	dial['J'] = 5; dial['K'] = 5; dial['L'] = 5;
	dial['M'] = 6; dial['N'] = 6; dial['O'] = 6;
	dial['P'] = 7; dial['Q'] = 7; dial['R'] = 7; dial['S'] = 7;
	dial['T'] = 8; dial['U'] = 8; dial['V'] = 8;
	dial['W'] = 9; dial['X'] = 9; dial['Y'] = 9; dial['Z'] = 9;

	cin >> word;
	for (int i = 0; i < 26; i++) {
		if (word[i] < 'A' || word[i] > 'Z') break;
		duration += dial[word[i]] + 1;
	}

	cout << duration << "\n";
}
