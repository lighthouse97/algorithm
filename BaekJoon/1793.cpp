// 1793.cpp
// Ÿ�ϸ�
// �������α׷���, 11727�� ���� �ٸ��� �𸣰ڴ�.
// �Ѱ��� �ٸ����̶�� �ſ� �ſ� ū���� long long���ε� ������ �ȵȴ�.
// ���� ����� string���� �����ϴ� �����̴�.
// ���� strng�Ⱦ��� 250���� �迭(�迭�� �迭)�� �ص� �ȴ�. string���� �ص� ó���ӵ��� ����ϴ�.
// ICPC > Regionals > North America > Rocky Mountain Regional > Alberta Collegiate Programming Contest > ACPC 2000 A��
// ���ѽð� 1�� �� 0ms(2116KB)�� �ҿ�Ǿ���.
// ������� 204/842�� ���� 24.22%�� rank�Ǿ���.


#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue

using namespace std;

string add_num(const string& a, const string& b)
{
	string l, s;
	int tmp, extra = 0;
	if (a.length() >= b.length()) {
		l = a;
		s = b;
		s.insert(0, string(a.length() - b.length(), '0'));
	}
	else {
		l = b;
		s = a;
		s.insert(0, string(b.length() - a.length(), '0'));
	}
	for (int i = (int)l.length() - 1; i >= 0; i--) {
		tmp = (l[i] - '0') + (s[i] - '0') + extra;
		extra = tmp / 10;
		tmp = tmp % 10;
		l[i] = tmp + '0';
	}
	if (extra) l.insert(l.begin(), extra + '0'); 
	return l;
}

string double_num(const string& a)
{
	return add_num(a, a);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	vector<string> dp(251);
	int num;
	dp[0] = "1";
	dp[1] = "1";
	dp[2] = "3";
	for(int i=3; i<=250; i++)
		dp[i] = add_num(dp[i - 1], double_num(dp[i - 2]));
	while (cin >> num)
		cout << dp[num] << "\n";
}
