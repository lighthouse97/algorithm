// 15678.cpp
// 연세워터파크
// University > 연세대학교 > 2018 연세대학교 컴퓨터과학과 프로그래밍 경진대회 L번
// 앞의 5977과 유사한 문제이다.
// 동적프로그래밍과 deque를 응용하면 된다.
// DP[i]가 index i에서 i-D까지 조건에 맞게 징검다리 건넜을 때의 가장 큰 점수라고 한다면,
// 점화식은
// DP[i] = max((max(DP[j]) + A[i]), A[i]), (i-D <= j <= i-1)
// max(DP[j])는 i-1부터 D개만큼(i-D까지) deque를 이용해서(앞에서 지금까지 했던 것 처럼...) 구하면 된다.
// 함 풀어보자!
// 제한시간 1초 중 16ms(3,740KB)가 소요되었다.
// 맞은사람 29/222로 상위 13.06%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy
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
	FAST;

	int N, D, k;
	long long ans;	
	deque<pli> mydq;

	cin >> N >> D;	

	long long maxval;
	cin >> maxval;
	mydq.push_back({ maxval, 1 });
	ans = maxval;
	for (int i = 2; i < N + 1; i++) {
		cin >> k;
		if (!mydq.empty() && mydq.front().second < i - D) mydq.pop_front();
		maxval = max(mydq.front().first + k, (1LL)*k);		
		ans = max(ans, maxval);
		if (i == N) break;
		while (!mydq.empty() && mydq.back().first < maxval) mydq.pop_back();
		mydq.push_back({maxval, i});						
	}
	cout << ans << "\n";
}