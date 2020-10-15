// 17435.cpp
// �ռ��Լ��� ����
// �� ������ LCA ���� �� �Ϻο� ���� ���������̴�.
// LCA �˰��������� �� ����� 2^i �θ� ã�� ���� ��ȭ���� ����� ������ȹ������
// ã�´ٰ� �ߴµ� �� ����� ���� �����̴�.
// ����� ������ȹ�������� ��ȭ���� par[x][i] = par[par[x][i-1]][i-1] �̴�.
// �������� �־��� n�� max 500,000�� ��� �迭�� ������ �޸� �ʰ��� ����.
// �׶��׶� ����ؾ� �ڴ�.
// �׶� �׶� ����ϴ� �ð��ʰ� �߻�. ��...
// �ᱹ LCA������ ���� 2^i Ž���� �ʿ��ϴٴ� ���̴�!
// ���ѽð� 1�� �� 456ms(25416KB)�� �ҿ�Ǿ���.
// ������� 110/122�� ���� 90.16%�� rank�Ǿ���.(���� ����~~)
// �� �� ������ ����ȭ��ų ����� ������?
// ���Ͱ� �����̴�. ������ ���� ���� ���� ���ͺ��� ���� ������ �迭 �����ϴ� ���� �ξ� �� ������.
// ���͸� ���� ������ ������ �迭�� �ٲٰ� �����ϸ� 276ms(16828KB)�� �� 39.47%�� ����ð��� ���� �پ���.
// �� �� ����� 60/123���� ���� 48.78%�� rank�ȴ�.
// ���⼭ dp[][]���� n�� ���� log ���� ������ �ٲ��ָ� ó�� �ð��� �� ����ȴ�.(�׷��� ������ ������ ũ�� �ǹ̴� ���� ���δ�.)

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
int dp[200001][g_max_i + 1] = { {0, }, };

int main()
{
	FAST

	int m, q, n, x, depth;
	//vector<vector<int>> dp;
	cin >> m;
	//dp.resize(m + 1, vector<int>(g_max_i + 1, 0));
	// initialise
	for (int i = 1; i <= m; i++)
		cin >> dp[i][0];
	for (int j = 1; j <= g_max_i; j++) {
		for (int i = 1; i <= m; i++) {
			dp[i][j] = dp[dp[i][j-1]][j-1];
		}
	}
	// find the result
	cin >> q;
	while (q--) {
		cin >> n >> x;
		depth = n;
		for (int i = g_max_i; i >= 0; i--) {
			if (depth >= (1 << i)) {
				x = dp[x][i];
				depth -= (1 << i);
			}
		}
		cout << x << "\n";
	}
}