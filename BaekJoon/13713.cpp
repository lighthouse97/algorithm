// 13173.cpp
// 문자열과 쿼리
// Z 알고리즘 응용 문제이다.
// 1) 문제의 문자열 S를 뒤집는다.
// 2) 뒤집은 문자열에서 Z 배열을 구한다.
// 3) index = 문자열 개수(n) - 쿼리값(i) - 1
// 4) Z[index]가 가장 긴 공통 접미사 F(i) 값이 된다.
// 제한시간 2초 중 44ms(8,020KB)가 소요되었다.
// 맞은사람 36/97로 상위 37.11%에 rank되었다.

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

vector<int> Z;

void z_algorithm(const string& str)
{
	int R = 0, L = 0;
	int n = (int)str.length();
	for (int i = 1; i < n; i++) {
		if (i > R) {
			L = R = i;
			while (R < n && str[R - L] == str[R]) R++;
			Z[i] = R - L; R--;
		}
		else { // L < i <= R
			int k = i - L; // i'
			if (i + Z[k] - 1 < R) Z[i] = Z[k];
			else {
				L = i;
				while (R < n && str[R - L] == str[R]) R++;
				Z[i] = R - L; R--;
			}
		}
	}
	Z[0] = n;
}

int main()
{
	FAST;

	string S, str;
	int M, slen;
	cin >> S;
	slen = (int)S.length();	
	str.resize(slen, 0);
	for (int i = 0; i < slen; i++) // reverse string
		str[i] = S[slen - 1 - i];

	Z.resize(slen, 0);
	z_algorithm(str);
	cin >> M;
	for (int i = 0; i < M; i++) {
		int index;
		cin >> index;
		index = slen - index;
		cout << Z[index] << "\n";
	}
}