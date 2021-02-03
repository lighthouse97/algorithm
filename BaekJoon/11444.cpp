// 11444.cpp
// 피보나치 수 6
// 동적 프로그래밍으로 풀 수 도 있지만 TLE 우려가 있어, 행렬의 거듭제곱으로 푼다.
// 거듭제곱이므로 분할 정복의 영역에 속한다.
// n = 2일 때 2 X 2 행렬인 [ 0 1 / 1 1 ]을 한번 곱하고
// n = 3일 때 2번곱하고... n일 때 [ 0 1 / 1 1 ]을 n - 1번 곱하면 (r = 2, c = 2)번째 원소가 n번째 피보나치 수가 된다.
// 이를 행렬의 거듭제곱 원리를 이용해서 풀어본다.
// 제한시간 1초 중 0ms(2,016KB)가 소요되었다.
// 맞은사람 709/1181로 상위 60.03%에 rank되었다.

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