// 1152_1.cpp
// 단어의 개수
// 문자열 split 함수를 만들지 않고 답만 내기위해 좀 더 빠르게 처리하도록 하였다.
// 앞에서 했던 방식이 11,848KB에 16ms 걸렸던 것에 비해,
// 이 방식은 3,680KB에 8ms 걸렸다.

#include "pch.h"
#include <iostream>
#include <string>
//#include <vector>
//#include <sstream>
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

bool is_alpha(char c)
{
	bool result = false;
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		result = true;

	return result;
}

int main()
{
	FAST;

	string input_string;
	bool enable_count = true;
	int word_cnt = 0;

	getline(cin, input_string);
	for (int i = 0; i < input_string.length(); i++) {
		if (is_alpha(input_string[i])) {
			if (enable_count) {
				word_cnt++;
				enable_count = false;
			}
		}
		else if (input_string[i] == ' ') enable_count = true;
		else
			;
	}

	cout << word_cnt << '\n';
}