// 12846.cpp
// 무서운 아르바이트
// University > 숭실대학교 > SCCC 2016 Summer Contest H번
// 앞에서 푼 히스토그램(6549, 1725) 문제와 동일한 문제로 보면 된다!!!
// 처음에 문제 이해를 못해서 질문란의 설명을 보고서야 이 문제가 히스토그램 문제와 같다는 것을 이해하게 되었다.
// 분할정복을 응용한 세그먼트 트리로 풀거나 스택을 이용해서 풀 수 있다.
// 스택을 이용해서 푸는 것이 더 간편해서 스택으로 문제를 풀기로 한다.
// 제한시간 1초 중 12ms(2,400KB)가 소요되었다.
// 맞은사람 23/323로 상위 7.12%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;
typedef long long ll;

ll do_maxPay()
{
	int N;
	ll maxval = 0;
	vector<int> pays;
	stack<int> myst;

	cin >> N;
	pays.resize(N + 1, 0);
	int left, height, right;
	ll area;
	for (int i = 1; i < N + 1; i++) {
		cin >> pays[i];
		if (myst.empty() || pays[myst.top()] <= pays[i]) myst.push(i);
		else {
			while (!myst.empty() && pays[myst.top()] > pays[i]) {
				right = i - 1;
				height = pays[myst.top()];
				myst.pop();
				left = myst.empty() ? 1 : myst.top() + 1;
				area = 1LL * (right - left + 1) * height;
				maxval = max(maxval, area);
			}
			myst.push(i);
		}
	}
	// 남은 스택 처리
	right = N;
	while (!myst.empty()) {
		height = pays[myst.top()];
		myst.pop();
		left = myst.empty() ? 1 : myst.top() + 1;
		area = 1LL * (right - left + 1) * height;
		maxval = max(maxval, area);
	}
	return maxval;
}

int main()
{
	FAST;

	cout << do_maxPay() << "\n";
}