// 2193.cpp
// ��ģ��
// ��õ���� �ƴϵ� ��ģ��!!!
// ������ �� ���� �Ѵ�.
// DP[N]�� 0�� ������ DP[N-1]�� ��ü ����
// DP[N]�� 1�� ������ DP[N-1]�� 0�� ����
// �Ǵ� DP[i]�� �ɰ��� �ʰ� DP[N-1] + DP[N-2]�� �����ص� �ȴ�!
// ���ѽð� 2�� �� 0ms(1984KB)�� �ҿ�Ǿ���.
// ������� 6496/12115�� ���� 53.61%�� rank�Ǿ���.

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

	int N;
	long long answer;
	vector<vector<long long>> DP;
	DP.resize(91, vector<long long>(2, 0));
	DP[1][0] = 0;
	DP[1][1] = 1;
	for (int i = 2; i <= 90; i++) {
		DP[i][0] = DP[i - 1][0] + DP[i - 1][1];
		DP[i][1] = DP[i - 1][0];
	}
	cin >> N;
	answer = DP[N][0] + DP[N][1];
	cout << answer << "\n";
}