// 11051_1.cpp
// ���װ�� 2
// ���װ��(������ ��)�� ����� ����� �ƴ� �ݺ����� ���� ���غ���.
// DP(N, R)�� ���� ���� ������ N���� ��� ���Ѵ���(�Ľ�Į�� �ﰢ�� �̿�)
// DP(N, R) ��ġ�� ���� ����ϸ� �ȴ�.
// recursive�� �ϳ� �ݺ������� �ϳ� ����ð��� �Ȱ��� 4ms�� ���Դ�.
// �ݺ����� �� �� ����ȭ ���Ѿ� �ڴ�.
// �ݺ��������ϰ� DP�迭 �� �˰����� ����ȭ��Ű��,
// (5900KB, 4ms) ==> (1992KB, 0ms) ���� �����Ǿ���.

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

#if 0 // �ݺ������� ó��
int DP[1001][1001] = { {0,}, };
const int mod = 10007;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, K;
	cin >> N >> K;

	for (int i = 1; i <= N; i++) {
		for (int j = 0; j <= i; j++) {
			if (j == 0 || i == j) DP[i][j] = 1;
			else {
				DP[i][j] = DP[i - 1][j - 1] + DP[i - 1][j];
				DP[i][j] %= mod;
			}
		}
	}
	cout << DP[N][K] << "\n";
}
#else // �ݺ��� ����ȭ
int DP[1001] = { 0, };
const int mod = 10007;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, K;
	cin >> N >> K;
	DP[0] = 1;
	for (int i = 1; i <= N; i++)
		for (int j = i; j >= 1; j--)
			DP[j] = (DP[j - 1] + DP[j]) % mod;
	
	cout << DP[K] << "\n";
}

#endif
