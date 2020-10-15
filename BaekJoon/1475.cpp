// 1475.cpp
// ���ȣ
// max N�� �������� 1,000,000�̹Ƿ� �ִ� 7���� ��Ʈ���� �� ��Ʈ�� 0~9, 10(��Ʈ��뿩��)��
// ǥ���ϴ� �迭�� �̸� ����� �ξ� �Է¹�ȣ�� �°� üũ�Ѵ�.
// �������� ��Ʈ 7�� �迭�� 11��° �ε����� ���� 1�� ��Ʈ�� ������ ���� �ȴ�.

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