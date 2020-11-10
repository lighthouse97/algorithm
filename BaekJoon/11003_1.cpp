// 11003_1.cpp
// 11003에서 priority_queue를 사용했는데,
// 원래 취지에 맞는 deque를 사용해서 시간을 좀 더 줄여보자.
// deque를 사용하니 수행시간이 더 줄어들었다.
// 제한시간 2.4초 중 1,540ms(63,116KB)가 소요되었다.
// 맞은사람 347/1600로 상위 21.68%에 rank되었다.

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
	FAST;

	int N, L;
	vector<int> answer;
	deque<pii> mydq;	

	cin >> N >> L;
	answer.resize(N + 1, 0);

	int a;
	for (int i = 1; i < N + 1; i++) {
		cin >> a;		

		if (!mydq.empty() && mydq.front().second <= i - L) mydq.pop_front();
		while(!mydq.empty() && mydq.back().first > a) mydq.pop_back();

		mydq.push_back({ a, i });
		answer[i] = mydq.front().first;
	}

	for (int i = 1; i < N + 1; i++)
		cout << answer[i] << " ";
	cout << "\n";
}