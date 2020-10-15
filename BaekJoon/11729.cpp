// 11729.cpp
// Hanoi Tower
// 원래는 하노이탑이 진행되는 순서를 전개해서 여기서 규칙을 찾아 알고리즘을
// 세워야 하는데, 그냥 네이버의 자료를 검색해서 구현하였다.

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