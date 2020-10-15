// 2805.cpp
// 나무 자르기
// 랜선 자르기(1654)와 유사하게 풀면 된다.
// 시간은 5896KB에 180ms가 나왔다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
//#include <algorithm> // sort, max, min
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

	int N, M, max_val = 0;
	int start, end, mid, ans = 0;
	long long cnt = 0;

	cin >> N >> M;
	vector<int> arr(N);
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
		if (max_val < arr[i]) max_val = arr[i];
	}
	
	// 가장 긴 나무를 기준으로 start, end 값을 정한다.
	start = 0;
	end = max_val;
	// 이분 탐색
	while (start <= end) {
		mid = (start + end) >> 1;
		cnt = 0;
		for (int i = 0; i < N; i++)
			if (arr[i] > mid) cnt += (long long)(arr[i] - mid); // mid로 잘라서 얻을 수 있는 나무의 총길이를 구한다.
		if (cnt >= M) {
			if (ans < mid) ans = mid; // 현재의 mid(길이)로 필요한 길이 이상 얻을 수 있으므로 일단 이 값을 저장한다.
			start = mid + 1;
		}
		else end = mid - 1;
	}
	cout << ans << "\n";
}