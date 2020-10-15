// 2110.cpp
// 공유기 설치
// 이분 탐색을 이용해서 2805(나무자르기)와 유사하게 푼다.

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
//#include <set>
//#include <cmath> // sqrt

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, C;
	int start, end, mid, ans = 0;
	int cnt, cur;

	cin >> N >> C;
	vector<int> arr(N);
	for (int i = 0; i < N; i++)
		cin >> arr[i];
	sort(arr.begin(), arr.end());

	start = 1;
	end = arr.back() - arr.front();
	// 이분 탐색
	while (start <= end) {
		mid = (start + end) >> 1;
		cnt = 1;
		cur = 0;
		// 순차 탐색하여 집사이의 거리가 mid보다 같거나 크면 공유기 count 증가 시킨다.
		for (int i = 1; i < N; i++) {
			if (arr[cur] + mid <= arr[i]) {
				cnt++;
				cur = i;
			}
		}
		if (cnt >= C) { // 증가된 count가 목표 갯수보다 같거나 크면 거리(mid)를 더 늘린다.
			if (ans < mid) ans = mid;
			start = mid + 1;
		}
		else end = mid - 1; // 공유기 갯수가 목표 갯수보다 작으면 거리(mid)를 더 좁힌다.
	}
	cout << ans << "\n";
}