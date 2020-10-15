// 16163.cpp
// #15164번_제보
// palindrom 응용 문제
// manacher 알고리즘을 응용한다.
// 계속 틀린다고 나오는데 그 원인을 밝혀내지 못하고 있다.
// 원인을 6일 뒤에나 알았다! (9/15 -> 9/22)
// 원인은 answer type을 int가 아닌 long long으로 해야 한다! 
// 문자열 최대 개수가 2,000,000개라 모든 부분 문자열의 팰린드롬 개수가 32bit 범위를 넘어갈 수 있다!
// 팰린드롬 개수 합을 저장하는 변수 type을 long long으로 지정하니 문제가 해결되었다!
// 제한시간 1초 중 60ms(23,692KB)가 소요되었다.
// 맞은사람 30/77로 상위 38.96%에 rank되었다.

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

vector<int> A;

void manacher(const string& str, int n)
{
	int range = 0, center = 0;
	for (int i = 0; i < n; i++) {
		if (i > range) A[i] = 0;
		else A[i] = min(A[2 * center - i], range - i); // center - (i - center)

		while (i - A[i] - 1 >= 0 && i + A[i] + 1 < n
			&& str[i - A[i] - 1] == str[i + A[i] + 1])
			A[i]++;

		if (range < i + A[i]) { // range update
			range = i + A[i];
			center = i;
		}
	}
}

int main()
{
	FAST;

	string S, str;
	long long answer = 0;
	cin >> S;

	int l = (int)S.length();
	str.resize(l * 2 + 1, 0);
	for (int i = 0; i < l; i++) {
		str[i * 2] = '#';
		str[i * 2 + 1] = S[i];
	}
	str.back() = '#';

	int length = (int)str.length();
	A.resize(length, 0);
	manacher(str, length);

	for (int i = 0; i < length; i++) {
		if (A[i] > 0) {
			if (str[i] == '#') answer += A[i] / 2;
			else answer += A[i] / 2 + 1;
		}
	}
	cout << answer << "\n";
}