// 11726.cpp
// 2Xn Ÿ�ϸ�
// �ʹ����� ���� ���� ���α׷��� �����̴�.
// �������α׷����� Ư���� �ϴ� ������ �߸� ����� ��ð��� ��� �� �ֱ� ������
// ó���� ������ �� �а� ù�ܰ���� �ϳ��� ��� ���糪���� �ݹ� Ǯ �� �ִ�.
// ������ ó���� �����ϰ� ������ ��Ƽ� �ѽð� �Ѱ� ��ǰ� ����!

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	vector<int> dp;
	cin >> n;
	dp.resize(n + 1, 0);
	dp[1] = 1;
	dp[2] = 2;
	for (int i = 3; i <= n; i++)
		dp[i] = (dp[i - 1] + dp[i - 2]) % 10007;
	cout << dp[n] << "\n";
}