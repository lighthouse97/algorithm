// 1152_1.cpp
// �ܾ��� ����
// ���ڿ� split �Լ��� ������ �ʰ� �丸 �������� �� �� ������ ó���ϵ��� �Ͽ���.
// �տ��� �ߴ� ����� 11,848KB�� 16ms �ɷȴ� �Ϳ� ����,
// �� ����� 3,680KB�� 8ms �ɷȴ�.

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