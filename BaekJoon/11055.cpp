// 11055.cpp
// ���� ū ���� �κ� ����
// ���� �� �����ϴ� �κ� ����(11053.cpp)�� �����̴�.
// ���� for���� ����� ���� �� �����ϴ� �κ� ���� ����� �����ؼ�
// ���� ������ ������ ���� ���� �ƴ� ������ ũ�⸦ �����ؼ�
// ���� ū ���� ����Ѵ�.
// EX :
// 10 20 30 01 02
// 10
// 10 30
// 10 30 60
// 10 30 60
// 10 30 60 01 03

#include "pch.h"
#include <iostream>
//#include <vector>
#include <algorithm> // max

using namespace std;

int DP[1001] = { 0, };
int AR[1001] = { 0, };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N, maxval = 1;
	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> AR[i];
		DP[i] = AR[i];
		for (int j = 1; j < i; j++) {
			if (AR[j] < AR[i]) {
				DP[i] = max(DP[j] + AR[i], DP[i]);
			}
		}
		maxval = max(DP[i], maxval);
	}
	cout << maxval << "\n";
}