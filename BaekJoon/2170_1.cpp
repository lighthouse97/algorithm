// 2170_1.cpp
// 앞에서 한 것과 거의 같은데 코드를 좀 더 간단히 고쳤다.
// 주어진 쌍에서 중복 구간을 제거하고 카운트 될 구간만 남겨서 그것만 카운트하게 하였다.
// 수행시간이 아주 조금 단축되었으나 크게 의미는 없다.
// 제한시간 1초 중 376ms(17,648KB)가 소요되었다.
// 맞은사람 130/1304로 상위 9.96%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy, swap
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

typedef pair<int, int> pii;
vector<pii> LINE;
vector<pii> FILTER;

int main()
{
	FAST;

	int N, sum = 0;
	cin >> N;
	LINE.resize(N);
	FILTER.reserve(N);

	int s, e;
	for (int i = 0; i < N; i++) {
		cin >> s >> e;
		LINE[i] = (s < e) ? pii(s, e) : pii(e, s);
	}

	sort(LINE.begin(), LINE.end());
	FILTER.push_back(LINE[0]);
	sum += (FILTER.back().second - FILTER.back().first);
	for (int i = 1; i < N; i++) {
		if (FILTER.back().second <= LINE[i].first) { // 떨여져 있는 경우
			FILTER.push_back(LINE[i]);
			sum += (FILTER.back().second - FILTER.back().first);
		}
		else if (FILTER.back().second > LINE[i].first &&
			FILTER.back().second < LINE[i].second) { // 걸쳐 있는 경우
			sum -= (FILTER.back().second - FILTER.back().first);
			FILTER.back().second = LINE[i].second;
			sum += (FILTER.back().second - FILTER.back().first);
		}
	}

	cout << sum << "\n";
}