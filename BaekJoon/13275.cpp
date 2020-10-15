// 13275.cpp
// 가장 긴 펠린드롬 부분 문자열
// 마나허(manacher) 알고리즘을 사용하는 문제다.
// 마나허 알고리즘을 직관적으로 사용하는 문제이고
// 응용은 없기 때문에 마나허 알고리즘만 알면 바로 풀수 있다.
// 제한시간 2초 중 4ms(3,268KB)가 소요되었다.
// 맞은사람 94/228로 상위 41.22%에 rank되었다.

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
	cin >> S;

	for (int i = 0; i < S.length(); i++) {
		str += '#';
		str += S[i];
	}
	str += '#';
	
	int length = (int)str.length();
	A.resize(length + 1, 0);
	manacher(str, length);

	int answer = 0;
	for (int i = 0; i < A.size(); i++)
		answer = max(answer, A[i]);
	cout << answer << "\n";
}