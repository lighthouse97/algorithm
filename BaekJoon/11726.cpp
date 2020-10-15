// 11726.cpp
// 2Xn 타일링
// 너무나도 쉬운 동적 프로그래밍 문제이다.
// 동적프로그래밍의 특성상 일단 방향을 잘못 잡고나면 몇시간을 헤맬 수 있기 때문에
// 처음에 문제를 잘 읽고 첫단계부터 하나씩 꿰어 맞춰나가면 금방 풀 수 있다.
// 실제로 처음에 엉뚱하게 방향을 잡아서 한시간 넘게 헤맨거 같다!

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