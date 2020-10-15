// 11051.cpp
// ���� ��� 2
// ���� ��� 1������ ���� Factorial�� �̿��ؼ� Ǯ�� ���� ������ Ŀ�� �ð��ʰ��� �߻��Ѵ�.
// �� ���� �Ľ�Į�� �ﰢ���� �̿��� ������ ������ �̿��Ѵ�. (����Լ��� Ǭ��.)
// nCr = (n-1)C(r-1) + (n-1)Cr
// ���ÿ� ���� ���� �����ϴ� �������α׷����� �̿��Ѵ�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair

using namespace std;

int DP[1001][1001] = { {0,}, };
const int mod = 10007;

int combination(int n, int r)
{
	if (r == 0 || n == r) return 1;
	if (DP[n][r] != 0) return DP[n][r];
	DP[n][r] = combination(n - 1, r - 1) + combination(n - 1, r);
	return (DP[n][r] % mod);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, K;
	cin >> N >> K;

	cout << combination(N, K) << "\n";
}