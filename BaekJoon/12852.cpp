// 12852.cpp
// 1�� ����� 2
// '1�� �����'(1463)�� �����Ѵ�.
// 1�� ����� ����� �ּҰ� �Ӹ� �ƴ϶� �� ��ε� �Բ� ����ؾ� �Ѵ�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <string>
//#include <vector>
//#include <cstdlib> // abs
//#include <cmath>
//#include <algorithm> // min, max

using namespace std;

int COUNT[1000001][2] = { { 0, } }; // N���� 0 index�� �ּҿ���Ƚ��, 1 index�� ���� �� index ��ġ

void make_one(int n)
{
	for (int i = 2; i <= n; i++) {
		COUNT[i][0] = COUNT[i - 1][0] + 1; // 1�� ���� ���
		COUNT[i][1] = i - 1;
		// 2�� ������ ���� ���
		if (i % 2 == 0 && COUNT[i / 2][0] + 1 < COUNT[i][0]) {
			COUNT[i][0] = COUNT[i / 2][0] + 1;
			COUNT[i][1] = i / 2;
		}
		// 3���� ������ ���� ���
		if (i % 3 == 0 && COUNT[i / 3][0] + 1 < COUNT[i][0]) {
			COUNT[i][0] = COUNT[i / 3][0] + 1;
			COUNT[i][1] = i / 3;
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, num;
	cin >> N;
	make_one(N);
	// �ּ� ���� Ƚ��
	cout << COUNT[N][0] << "\n";
	// 1�� ����� ���
	num = N;
	while (num) {
		cout << num << " ";
		num = COUNT[num][1];
	}
	cout << "\n";
}
