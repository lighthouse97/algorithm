// 1475.cpp
// 방번호
// max N이 문제에서 1,000,000이므로 최대 7개의 세트에서 각 세트당 0~9, 10(세트사용여부)를
// 표시하는 배열을 미리 만들어 두어 입력번호에 맞게 체크한다.
// 마지막에 세트 7개 배열의 11번째 인덱스의 값이 1인 세트의 갯수만 세면 된다.

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

int sets[7][11] = { {0, } };

void check_num(int num)
{
	int i;
	for (i = 0; i < 7; i++) {
		if (sets[i][num] == 0) {
			sets[i][num]++;
			if (sets[i][10] == 0) sets[i][10]++;
			break;
		}
		else {
			if (num == 6 && sets[i][9] == 0) {
				sets[i][9]++; break;
			}
			else if (num == 9 && sets[i][6] == 0) {
				sets[i][6]++; break;
			}
		}
	}
}

int main()
{
	int sum = 0;
	string N;
	cin >> N;
	for (unsigned int i = 0; i < N.length(); i++) {
		check_num(N[i] - '0');
	}
	for (int i = 0; i < 7; i++)
		sets[i][10] ? sum++ : sum;
	cout << sum << "\n";	
}