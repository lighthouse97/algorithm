// 11660.cpp
// ���� �� ���ϱ� 5
// 2���� �迭�� �������� ���ϴ� �����̴�.
// �迭�� ���� �߰��� �ٲ��� �����Ƿ� DP�� ����ؼ� Ǯ �� �ִ�.
// ������ ������ '���� �� ���ϱ� 3'�� �߰��� ���� ��� �ٲ�Ƿ�
// 2���� �迭�� ���� ���׸�Ʈ Ʈ���� ����ϴ� ����� �����̴�.
// ���� ���α׷����� ��ȭ���� ������ ����.
// DP[i, j] = DP[i-1, j] + DP[i, j-1] - DP[i-1, j-1] + NUM[i, j]
// �������� ���� ������ ����.
// SUM[x1, y1, x2, y2] = DP[x2, y2] - DP[x2, y1-1] - DP[x1-1, y2] + DP[x1-1, y1-1]
// �׷��� ����� ������ �ƴѵ� ���� ����µ� �ð��� ���� �ɷȴ�!
// ���ѽð� 1�� �� 132ms(6,228KB)�� �ҿ�Ǿ���.
// ������� 85/2152�� ���� 3.94%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs, ceil, log2
#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <functional> // less, greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_DP;

int main()
{
	FAST;

	int n, m, num, x1, x2, y1, y2, sum;
	cin >> n >> m;
	g_DP.resize(n + 1, vector<int>(n + 1, 0));

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> num;
			g_DP[i][j] = g_DP[i - 1][j] + g_DP[i][j - 1] - g_DP[i - 1][j - 1] + num;
		}
	}

	for (int i = 0; i < m; i++) {
		cin >> x1 >> y1 >> x2 >> y2;
		sum = g_DP[x2][y2] - g_DP[x2][y1 - 1] - g_DP[x1 - 1][y2] + g_DP[x1 - 1][y1 - 1];
		cout << sum << "\n";
	}
}