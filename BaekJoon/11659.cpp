// 11659.cpp
// ���� �� ���ϱ� 4
// ���׸�Ʈ Ʈ��(Segment Tree)�� ����ϱ� ���� ���׸�Ʈ Ʈ���� ���� ���ظ� ���� ����
// ������ ������� Ǯ��� �����̴�. �־��� ������ �κ� ���� ���ϴ� �����ε�,
// �������α׷������� ó������ ���������� �������� ��� ���� ������ �κ����� �����ָ� �ȴ�.
// ���ѽð� 1�� �� 40ms(2,376KB)�� �ҿ�Ǿ���.
// ������� 170/3650�� ���� 4.65%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
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

int main()
{
	FAST;

	int n, m, num, s, e;
	vector<int> dp;

	cin >> n >> m;
	dp.resize(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		cin >> num;
		dp[i] = dp[i - 1] + num;
	}

	for (int i = 0; i < m; i++) {
		cin >> s >> e;
		cout << dp[e] - dp[s - 1] << "\n";
	}
}