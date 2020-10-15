// 12738.cpp
// ���� �� �����ϴ� �κ� ����3
// 12015.cpp�� Ǫ�� ����� �����ϴ�.

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm> // lower_bound

using namespace std;

int AR[1000001] = { 0, };
vector<int> DP;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N;
	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> AR[i];
		if (i == 1) DP.push_back(AR[1]);
		else {
			if (DP.back() < AR[i]) DP.push_back(AR[i]);
			else
				DP[lower_bound(DP.begin(), DP.end(), AR[i]) - DP.begin()] = AR[i];
		}
	}
	cout << DP.size() << "\n";
}