// 5977.cpp
// Mowing the Lawn
// Olympiad > USA Computing Olympiad > 2010-2011 Season > USACO US Open 2011 Contest > Gold 1번
// 문제의 "Mowing the Lawn" 문제이다. DP 문제가 다 그렇듯이 알고 보면 간단한 건데 그 간단한 아이디어 조차
// 내지 못하고 감조차 잡지 못해서 결국 포기한 문제이다.
// DP문제는 머리가 아주 좋던지 아니면 관련 문제를 많이 외워 두는 수 밖에 없을 거 같다.
// 이것도 아니고 저것도 아니면 아예 단서에 접근조차 하지 못한다.
// 설명은 있다가 하고 일단 먼저 풀어보자!
// 이 문제는 동적 프로그래밍과 deque 2개를 사용해야 풀 수 있는 문제이다.

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

typedef pair<int, int> pii;

int main()
{
	int N, K, e;
	vector<int> sum;
	vector<int> DP;
	deque<pii> mydq;

	cin >> N >> K;
	sum.resize(N + 1, 0);
	DP.resize(N + 1, 0);

	for (int i = 1; i < K + 1; i++) {
		cin >> e;
		sum[i] = sum[i - 1] + e;
		DP[i] = sum[i];
		mydq.push_back({ 0, i });
	}

	int mm;
	for (int i = K + 1; i < N + 1; i++) {
		cin >> e;
		sum[i] = sum[i - 1] + e;
		for (int j = i - K + 1; j <= i; j++) {
			mm = sum[j] - DP[j - 1];
			if (!mydq.empty() && mydq.front().second <= i - K) mydq.pop_front();
			while (!mydq.empty() && mydq.back().first > mm) mydq.pop_back();

			mydq.push_back({ mm, i });
			DP[i] = sum[i] - mydq.front().first;
		}
	}
	cout << DP[N] << "\n";
}