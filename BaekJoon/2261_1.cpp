// 2261_1.cpp
// 가장 가까운 두 점
// 2261에서 했던 방식으로 풀면 line sweeping 방식이지만 시간초과가 발생한다.
// candidate 검색 방식을 좀 더 최적화 시켜야 한다.
// candidate 검색 방식을 최적화 시켜서 문제를 푸니 3844KB에 56ms가 걸렸다.(O(NlogN))

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
#include <set>
#include <cmath> // sqrt

using namespace std;

struct point {
	int x;
	int y;
	point() : x(0), y(0) {}
	point(int x, int y) : x(x), y(y) {}
	bool operator < (const point& A) const {
		if (y == A.y) return x < A.x;
		else return y < A.y;
	}
};

bool comp(const point& A, const point& B) {
	return A.x < B.x;
}

int distance(const point& A, const point& B) {
	return ((A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y));
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, min_d, diff, start = 0;
	point now;
	cin >> n;
	vector<point> arr(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> arr[i].x >> arr[i].y;
	// x축 기준으로 정렬
	sort(arr.begin() + 1, arr.end(), comp);
	min_d = distance(arr[1], arr[2]);
	set<point> candidate = { arr[1], arr[2] };
	// 입력된 모든 점에 대해 가장 작은 두 점의 거리를 찾는다.
	for (int i = 3; i <= n; i++) {
		now = arr[i];
		// candidate x 거리에 대해 min distance보다 큰 것들을 필터링한다.
		while (start < i) {
			diff = now.x - arr[start].x;
			if (diff*diff > min_d) {
				candidate.erase(arr[start]);
				start++;
			}
			else break;
		}
		// candidate y 거리에 대해 min distance보다 큰 것들을 필터링한다.
		int yd = (int)sqrt(min_d) + 1;
		auto lower_point = point(-100001, now.y - yd); // y가 같은게  여러개면 x가 작은 거 우선순위로 하기 위해
		auto upper_point = point(100001, now.y + yd); // y가 큰게  여러개면 x가 큰 거 우선순위로 하기 위해
		auto lower = candidate.lower_bound(lower_point);
		auto upper = candidate.upper_bound(upper_point);
		int temp;
		for (auto it = lower; it != upper; it++) {
			temp = distance(now, *it);
			min_d = min(min_d, temp);
		}
		candidate.insert(now);
	}

	cout << min_d << "\n";
}
