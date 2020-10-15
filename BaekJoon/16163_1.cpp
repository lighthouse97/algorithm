// 16163_1.cpp
// #15164번_제보
// 16163을 manacher 알고리즘으로 풀려다 막혀서
// DP(Dynamic Programming)으로 먼저 풀어본다.
// 점화식은 다음과 같다.
// DP[L][R] = DP[L+1][R] + DP[L][R-1] - DP[L+1][R-1]
// and if(S[L] == S[R]) 이면,
// DP[L][R] += 1 (LR포함 전체 문자열)
// 만일 부분 문자열이 반드시 연속문자라는 조건이 없을경우,
// DP[L][R] = DP[L+1][R] + DP[L][R-1] - DP[L+1][R-1]
// and if(S[L] == S[R]) 이면,
// DP[L][R] += DP[L+1][R-1] + 1
// (쉽게 예를 들면, abba일 경우 DP[L+1][R-1] => (aba, aba, abba), +1 => (aa) 이렇게 추가가 된다)
// 문제는 첫번째 경우인 부분 문자열이 연속문자라는 조건이 있는 경우이다.
// 이 문제는 DP방식으로는 풀 수 없다!!!
// 왜냐하면 문자열의 최대 갯수가 2,000,000개 이기 때문에 최대 문자열일 경우 DP 배열의 크기가
// 2,000,000 * 2,000,000 * 4(byte) = 16TB가 나와서 당연히 메모리 초과가 발생한다.
// 결국 Manacher 알고리즘으로만 풀어야 한다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> DP;

int main()
{
	FAST;

	string str;
	cin >> str;
	int len = (int)str.length();

	DP.resize(len, vector<int>(len, 0));

	for (int i = 0; i < len; i++) {
		DP[i][i] = 1;
		if (i < len - 1)
			DP[i][i + 1] = (str[i] == str[i + 1]) ? 3 : 2;
	}

	int right;
	for (int slen = 2; slen < len; slen++) {
		for (int left = 0; left < len; left++) {
			right = left + slen;
			if (right < len) {
				DP[left][right] = DP[left + 1][right] + DP[left][right - 1] - DP[left + 1][right - 1];
				if (str[left] == str[right])
					DP[left][right] += 1;
			}
		}
	}

	cout << DP[0][len - 1] << "\n";	
}