// 10757.cpp
// 큰 수 A+B
// 앞의 타일링(1793)을 이용하면 된다.
// 더하는게 문제가 아니고 스트링으로 더하기 연산을 하는 것이 주 목적이다.
// 제한시간 1초 중 0ms(2132KB)가 소요되었다.
// 맞은사람 1116/3299로 상위 33.82%에 rank되었다.

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue

using namespace std;

string add_num(const string& a, const string& b)
{
	string l, s;
	int tmp, extra = 0;
	if (a.length() >= b.length()) {
		l = a;
		s = b;
		s.insert(0, string(a.length() - b.length(), '0'));
	}
	else {
		l = b;
		s = a;
		s.insert(0, string(b.length() - a.length(), '0'));
	}
	for (int i = (int)l.length() - 1; i >= 0; i--) {
		tmp = (l[i] - '0') + (s[i] - '0') + extra;
		extra = tmp / 10;
		tmp = tmp % 10;
		l[i] = tmp + '0';
	}
	if (extra) l.insert(l.begin(), extra + '0');
	return l;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string a, b;
	cin >> a >> b;

	cout << add_num(a, b) << "\n";
}