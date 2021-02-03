// 11444.cpp
// �Ǻ���ġ �� 6
// ���� ���α׷������� Ǯ �� �� ������ TLE ����� �־�, ����� �ŵ��������� Ǭ��.
// �ŵ������̹Ƿ� ���� ������ ������ ���Ѵ�.
// n = 2�� �� 2 X 2 ����� [ 0 1 / 1 1 ]�� �ѹ� ���ϰ�
// n = 3�� �� 2�����ϰ�... n�� �� [ 0 1 / 1 1 ]�� n - 1�� ���ϸ� (r = 2, c = 2)��° ���Ұ� n��° �Ǻ���ġ ���� �ȴ�.
// �̸� ����� �ŵ����� ������ �̿��ؼ� Ǯ���.
// ���ѽð� 1�� �� 0ms(2,016KB)�� �ҿ�Ǿ���.
// ������� 709/1181�� ���� 60.03%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
//#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

typedef long long ll;
typedef vector<vector<int>> vvi;
int MOD = 1000000007;

vvi BASE = { { 0, 0, 0 }, { 0, 0, 1}, { 0, 1, 1} };

vvi m_multi(const vvi& ma, const vvi& mb)
{
	vvi mc(3, vector<int>(3, 0));
	for (int i = 1; i < 3; i++)
		for (int k = 1; k < 3; k++)
			for (int j = 1; j < 3; j++) {
				mc[i][k] += (1LL * ma[i][j] * mb[j][k]) % MOD;
				mc[i][k] %= MOD;
			}
	return mc;
}

vvi fibo(ll n)
{
	if (n == 1) return BASE;
	if (n % 2) return m_multi(fibo(n - 1), BASE);
	else {
		vvi a = fibo(n / 2);
		return m_multi(a, a);
	}
}

int main()
{
	FAST;
	ll N;
	cin >> N;
	if (N <= 2) cout << (N == 0 ? BASE[1][1] : N == 1 ? BASE[1][2] : BASE[2][2]) << "\n";
	else {
		vvi mr = fibo(N - 1);
		cout << mr[2][2] << "\n";
	}
}