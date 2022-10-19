// 1152.cpp
// 단어의 개수
// 문자열 split 함수를 만들어서 처리하였다.
// 11,848KB에 16ms 걸렸다.

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<string> split(string input, char delimiter)
{
	vector<string> words;
	stringstream ss(input);
	string temp;

	while (getline(ss, temp, delimiter)) {
		if (!temp.empty()) words.push_back(temp);
	}

	return words;
}

int main()
{
	FAST;

	string input_string;
	vector<string> words;

	getline(cin, input_string);
	words = split(input_string, ' ');
	cout << words.size() << '\n';
}