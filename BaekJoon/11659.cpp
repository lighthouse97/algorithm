// 11659.cpp
// 구간 합 구하기 4
// 세그먼트 트리(Segment Tree)를 사용하기 전에 세그먼트 트리에 대한 이해를 돕기 위해
// 일종의 맛보기로 풀어보는 문제이다. 주어진 수열의 부분 합을 구하는 문제인데,
// 동적프로그래밍으로 처음부터 마지막까지 누적합을 모두 구한 다음에 부분합을 구해주면 된다.
// 제한시간 1초 중 40ms(2,376KB)가 소요되었다.
// 맞은사람 170/3650로 상위 4.65%에 rank되었다.

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