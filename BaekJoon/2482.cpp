// 2482.cpp
// ����ȯ
// �������α׷������� Ǫ�µ� �������ؼ� Ǭ�� Ʋ�ȴ�!
// ��ȭ�� ���� ���� �ٸ� ����� Ǭ ���� �ôµ� ���� �ϴµ��� ���� �ɷȴ�.
// ��� ������ �� ���ذ� �Ȱ���.
// N���� ���󿡼� ���� �������� �ʰ� K���� ���� ����� ����
// DP[N][K]�� �����Ѵٸ�
// DP[N][K] = DP[N-2][K-1] + DP[N-1][K] �� �ȴ�.
// DP[N-2][K-1] : ���Ƿ� �ϳ��� ���� ������ 1���� �����Ƿ� ��ü N-2���� �پ���, ���� ���߿��� K-1�� ����
// DP[N-1][K] : ���Ƿ� �ϳ��� ���� ������ ��ü N-1���� �پ���, ���� �� �߿��� K�� ����
// ���� ��� ���ظ� �Ϸ��� �ص� ���߸´� �ٴ� �͸� �� ��, ��Ȯ�� ���� �� ���� ������.
// ������ �ϳ� ������ �� �ص� �ᱹ K���� ������ �Ȱ���.(�̰��� ���� ��� ���� ���� �� �� �ִ�)

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <cstdlib> // abs
#include <vector>
//#include <algorithm> // max, min, sort
//#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair
//#include <stack> // stack
//#include <bitset> // bitmask

using namespace std;

const int MOD = 1000000003;
int N, K;
vector<vector<int>> DP;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> K;
	DP.resize(N + 1, vector<int>(N + 1, 0)); // 0���� �ʱ�ȭ!

	// N = 1 ~ 3 ���� ���
	for (int i = 1; i <= 3; i++)
		DP[i][1] = i;
	for (int i = 4; i <= N; i++) {
		for (int j = 1; j <= i / 2; j++) { // N/2 ���� ū ���� ������ ����� �� ��� 0
			if (j == 1) DP[i][j] = i;
			else
				DP[i][j] = (DP[i - 2][j - 1] + DP[i - 1][j]) % MOD;
		}
	}
	cout << DP[N][K] << "\n";
}