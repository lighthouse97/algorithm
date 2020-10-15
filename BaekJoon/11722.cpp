// 11722.cpp
// ���� �� �����ϴ� �κ� ����
// ���� ���α׷��̹Ƿ� ��ȭ���� ������ �Ѵ�.
// 11053�� ���� �� �����ϴ� �κм����� �ݴ�� �����ϸ� �ȴ�.

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
		DP[i] = 1;
		for (int j = 1; j < i; j++) {
			if (AR[j] > AR[i]) {
				DP[i] = max(DP[j] + 1, DP[i]);
			}
		}
		maxval = max(DP[i], maxval);
	}
	cout << maxval << "\n";
}