// 2565.cpp
// ������
// A, B pair�� �迭�� ���� �� A�� �������� �������� ������ �ϰ�
// B ������ ���ؼ� LIS(Longest Increasing Sequence)�� ���ؼ�
// N - LIS�� ���ϴ� ���� �ȴ�.
// ���� �����ϴ� �������� ������ LIS = N�� �Ǿ� ���־� �ϴ� �������� ������ 0�� �ȴ�. 

#include "pch.h"
#include <iostream>
//#include <vector>
#include <algorithm> // max, sort
#include <utility> // pair

using namespace std;

int DP[101] = { 0, };
pair<int, int> AR[101];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N, maxval = 0;
	cin >> N;

	AR[0].first = AR[0].second = 0;
	for (int i = 1; i <= N; i++)
		cin >> AR[i].first >> AR[i].second;
	sort(&AR[1], &AR[1] + N);

	for (int i = 1; i <= N; i++) {
		DP[i] = 1;
		for (int j = 1; j < i; j++) {
			if (AR[j].second < AR[i].second) {
				DP[i] = max(DP[j] + 1, DP[i]);
			}
		}
		maxval = max(DP[i], maxval);
	}
	cout << N - maxval << "\n";
}