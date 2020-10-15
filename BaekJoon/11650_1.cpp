// 11650_1.cpp
// 좌표정렬
// x, y 좌표가 모두 같은 두 점은 없다.
// 11650의 qsort를 사용하지 않고 이번에는 std::vector의 sort를 사용하였다.
// qsort를 사용한 경우(68ms),  -> std:sort를 사용한 경우(64ms) ,4ms 정도 개선된다.
// 성능(수행속도) 개선
// 1. make_fair를 쓰지 않고 coors 배열을 만들어 바로 할당
// 2. scanf, printf를 쓰지 않고 'ios_base::sync_with_stdio(false)' 조건하에서 cin, cout 사용
// 이렇게 수정하면 64ms -> 52ms, 12ms 개선된다. (경우에 따라 64ms -> 48ms, 16ms 개선된다.)

#include "pch.h"
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
//#include <cstdio>
#include <utility> // pair
#include <vector> // vector
#include <algorithm> // sort

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	int N;	
	cin >> N;
	vector<pair<int, int>> coors(N);
	for (int i = 0; i < N; i++) {
		cin >> coors[i].first >> coors[i].second;
	}
	sort(coors.begin(), coors.end());
	for (int i = 0; i < N; i++)
	   cout << coors[i].first << " " << coors[i].second << "\n";
}