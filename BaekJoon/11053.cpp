// 11053.cpp
// ���� �� �����ϴ� �κ� ����
// ���� ���α׷��̹Ƿ� ��ȭ���� ������ �Ѵ�.
// DP[1] = 1
// DP[2] = 1(1�� �ʱ�ȭ)
// DP[2] = (AR[1] < AR[2]) ? DP[1] + 1 : DP[2]
// for(int iter=1; iter<=N, i++)
// DP[iter] = 1(1�� �ʱ�ȭ)
// DP[iter] = for(int i=1; i<iter; i++) { (AR[i] < AR[iter]) ? MAX(DP[i] + 1, DP[iter]) : DP[iter] }
// 1���� i-1��°���� ���������� ũ�⸦ �˻��Ѵ�.
// max_value = max(DP[iter], max_value); // DP[1]~DP[N]�� ���� ū ���� ���

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
			if (AR[j] < AR[i]) {
				DP[i] = max(DP[j] + 1, DP[i]);
			}
		}
		maxval = max(DP[i], maxval);
	}
	cout << maxval << "\n";
}
