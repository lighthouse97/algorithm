// 9663.cpp
// N-Queen
// 대표적인 BackTracking 문제이다.
// dfs를 이용해서 풀어보았다.
// 제한시간 10초 중 4,096ms(2,016KB)가 소요되었다.
// 등수는 의미가 없어서 방법만 참고하기 바란다.

#include "pch.h"
//#include <cstdio> // NULL
#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int N = 0;
int cnt = 0;
vector<int> cols; // index : row, vel : col

bool IsPromising(int level)
{
	for (int i = 1; i < level; i++) {
		if (cols[level] == cols[i]) // 수직으로 같은 경우
			return false;
		else if ((level - i) == abs(cols[level] - cols[i])) // 대각선으로 같은 경우
			return false;
	}
	return true;
}

void BackTracking(int level)
{
	if (level > N) {
		cnt++;
		return;
	}
	else {
		for (int i = 1; i < N + 1; i++) {
			cols[level] = i;
			if (IsPromising(level))
				BackTracking(level + 1);
		}
	}
}

int main() {

	FAST;

	cin >> N;
	cols.resize(N + 1, 0);
	BackTracking(1);
	cout << cnt << "\n";
}