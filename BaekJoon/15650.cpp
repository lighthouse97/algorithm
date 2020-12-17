// 15650.cpp
// N과 M (2)
// 앞의 N과 M (1)과 유사한 방식(조건이 달라 약간 다르다)으로 풀면 된다.
// BackTracking 함수에 직전 level의 선택된 index를 parameter로 추가로 더 넘겨준다.
// 현재 선택된 item의 선택 여부에 (i <= pre) 조건만
// 추가해 주면 된다.
// 제한시간 1초 중 0ms(2,016KB)가 소요되었다.
// 맞은사람 5115/9022로 상위 56.69%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
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

int N = 0, M = 0;
vector<int> answer;

void BackTracking(const int& level, const int& pre)
{
	if (level > M) {
		for (int i = 1; i < level; i++) cout << answer[i] << " ";
		cout << "\n";
		return;
	}
	else {
		for (int i = 1; i < N + 1; i++) {
			if (i <= pre) continue;
			else {				
				answer[level] = i;
				BackTracking(level + 1, i);				
			}
		}
	}
}

int main() {

	FAST;

	cin >> N >> M;	
	answer.resize(M + 1, 0);
	BackTracking(1, 0);
}