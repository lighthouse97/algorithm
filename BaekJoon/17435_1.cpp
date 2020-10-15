// 17435_1.cpp
// �ռ��Լ��� ����
// �տ��� Ǭ ���� �ð��� ��������� ���� �ɷ��� ����ȭ ���Ѻ��Ҵ�.
// ���� ����� �����̾���. ���͸� �迭�� �ٲٴ�
// ���ѽð� 1�� �� 292ms(16828KB)�� �ҿ�Ǿ���.
// ������� 69/123�� ���� 56.09%�� rank�Ǿ���.
// �׸��� dp[][] �迭�� ������ �ٲپ� log index�� i���� �տ� �����ϰ� ���� n�� ���� �ڿ�
// ���� �ϸ� 244(16828KB)�� 48ms�� �ð��� �����Ͽ���.(�� 16% ����)
// �̷��� �ϸ� 37/123���� ���� 30.08%�� rank�ȴ�.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
//#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const int g_max_i = 18;
int dp[g_max_i + 1][200001] = { {0, }, };

int main()
{
	FAST

	int m, q, n, x;
	//vector<vector<int>> dp;
	cin >> m;
	//dp.resize(m + 1, vector<int>(g_max_i + 1, 0));
	// initialise
	for (int i = 1; i <= m; i++)
		cin >> dp[0][i];
	for (int j = 1; j <= g_max_i; j++) {
		for (int i = 1; i <= m; i++) {
			dp[j][i] = dp[j - 1][dp[j - 1][i]];
		}
	}
	// find the result
	cin >> q;
	while (q--) {
		cin >> n >> x;
		for (int i = 0; i <= g_max_i; i++) {
			if (n & (1 << i)) x = dp[i][x];
		}
		cout << x << "\n";
	}
}