// 1074.cpp
// Z
// 분할 정복 응용 연습문제이다.
// 분할 정복을 위한 이분 탐색과 재귀호출을 이용하는데, 영역 나눌때 각 영역의 시작점의 숫자 규칙 찾기가 어려웠다.
// 제한시간 0.5초 중 0ms(2,016KB)가 소요되었다.
// 맞은사람 2779/6004로 상위 46.28%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
//#include <vector>
//#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

// rs : row의 시작, cs : column의 시작, len : 영역의 길이, r, c : 찾으려는 좌표, start : 영역의 시작값.
int find_num(int rs, int cs, int len, int r, int c, int start)
{
	if (rs == r && cs == c) return start;

	int mid_r = rs + len / 2 - 1;
	int mid_c = cs + len / 2 - 1;
	int h_len = len >> 1;
	if (r <= mid_r) {
		if (c <= mid_c) return find_num(rs, cs, h_len, r, c, start + h_len * h_len * 0); // 1 / 4
		else return find_num(rs, mid_c + 1, h_len, r, c, start + h_len * h_len * 1); // 2 / 4
	}
	else {
		if (c <= mid_c) return find_num(mid_r + 1, cs, h_len, r, c, start + h_len * h_len * 2); // 3 / 4
		else return find_num(mid_r + 1, mid_c + 1, h_len, r, c, start + h_len * h_len * 3); // 4 / 4
	}
}

int main()
{
	FAST;

	int n, row, column;
	cin >> n >> row >> column;
	int length = 1 << n;

	int result = find_num(0, 0, length, row, column, 0);
	cout << result << "\n";
}