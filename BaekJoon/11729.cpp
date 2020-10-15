// 11729.cpp
// Hanoi Tower
// ������ �ϳ���ž�� ����Ǵ� ������ �����ؼ� ���⼭ ��Ģ�� ã�� �˰�����
// ������ �ϴµ�, �׳� ���̹��� �ڷḦ �˻��ؼ� �����Ͽ���.

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>

using namespace std;

void hanoi(int n, int from, int temp, int to)
{	
	if (n == 1) {
		cout << from << " " << to << "\n";
	}
	else {
		hanoi(n - 1, from, to, temp);
		cout << from << " " << to << "\n";
		hanoi(n - 1, temp, from, to);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	int count;
	cin >> N;
	if (N >= 1 && N <= 20) {
		count = (int)pow(2, N) - 1;
		cout << count << "\n";
		hanoi(N, 1, 2, 3);
	}
}