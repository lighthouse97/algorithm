// 5977.cpp
// Mowing the Lawn
// Olympiad > USA Computing Olympiad > 2010-2011 Season > USACO US Open 2011 Contest > Gold 1번
// 문제의 "Mowing the Lawn" 문제이다. DP 문제가 다 그렇듯이 알고 보면 간단한 건데 그 간단한 아이디어 조차
// 내지 못하고 감조차 잡지 못해서 결국 포기한 문제이다.
// DP문제는 머리가 아주 좋던지 아니면 관련 문제를 많이 외워 두는 수 밖에 없을 거 같다.
// 이것도 아니고 저것도 아니면 아예 단서에 접근조차 하지 못한다.
// 이 문제는 동적 프로그래밍과 deque 2 가지를 사용해야 풀 수 있는 문제이다.
// 그리고 2중 for문으로 풀면 O(N^2)이 되어 TLE가 발생한다. 잘 생각해서 하나의 for문과 deque를 활용해서 풀어야 한다.
// 일단 DP에서 점화식은 DP[i] = max(SUM[i] - SUM[j] + DP[j - 1]) , i - (K + 1) + 1 <= j <= i
// max 구할 때 sum[i]는 고정이므로 점화식을 다시 쓰면,
// DP[i] = SUM[i] - min(SUM[j] - DP[j - 1])
// SUM[j] - DP[j - 1]에서 j를 i로 고정시키면 i에서 i - (K + 1) + 1 범위까지에서 가장 작은 값을 구하면 된다.(K+1 범위에서 가장 작은 값)
// 즉 앞의 11003 문제에서 deque를 사용하여 최소값 구하는 것과 같은 패턴이다.
// 식을 전개해서 따져보면 이렇게 된다는 것을 알 수 있다.
// vector를 사용하지 않고 단순 배열로 구현하면 처리 시간이 좀 더 빨라질 것으로 예상된다.
// 제한시간 1초 중 64ms(2,800KB)가 소요되었다.
// 맞은사람 70/76로 상위 92.10%에 rank되었다.

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
#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

typedef pair<long long, int> pli;

int main()
{
	int N, K, e;
	long long sum = 0;
	vector<long long> DP;
	deque<pli> mydq;

	cin >> N >> K;
	DP.resize(N + 1, 0);

	long long minval;
	for (int i = 1; i < N + 1; i++) {
		cin >> e;
		sum += e;
		minval = sum - DP[i - 1];
		if (!mydq.empty() && mydq.front().second <= i - K - 1) mydq.pop_front();
		while (!mydq.empty() && mydq.back().first > minval) mydq.pop_back();
		mydq.push_back({ minval, i });

		DP[i] = (i <= K) ? sum : sum - mydq.front().first;
	}
	cout << DP[N] << "\n";
}