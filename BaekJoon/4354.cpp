// 4354.cpp
// 문자열 제곱
// 문제를 잘 이해해야 한다!
// 특정 패턴으로 시작되고 또 반복되는 패턴의 문자열을 찾아서 반복되는 패턴의 반복횟수를 출력하는
// 문제이다. 시작부터 반복되는 문자의 반복횟수를 찾아내는 것이지 문자열 내의 임의의 문자의 반복횟수를
// 찾아내는 것은 절대 아니다!!!
// 처음부터 잘못 접근하여 하루종일 고민했던 시간을 헛되게 하고 아주 소중한 시간을 낭비해 버렸다.
// KMP 알고리즘의 pi배열을 기본적으로 구한다. pi 배열 마지막의 값을 문자열 길이에서 빼면
// 반복되는 문자열의 길이가 나온다.
// 이 값을 문자열의 전체 길이로 나눠주면 반복되는 문자열의 반복 횟수가 나온다.
// 예를 들어, ababab가 있으면 문자열의 길이는 6, pi[5]=4, 6/(6-4)=3, ab 반복횟수 3이 나온다.
// 중간에 반복패턴이 없으면 예를 들어 abcdab인 경우 길이는 6, pi[5]=2, 6/(6-2)=1이 나온다.
// 즉 전체 문자열에 걸쳐 마지막까지 연속으로 반복 패턴이 없으면 suffix의 길이가 문자열 길이의 절반이 안되어
// suffix를 제외한 나머지 문자열의 길이로 1번 밖에 반복하지 못한다.
// 그리고 가운데 겹치는 부분이 반복문자열의 패턴이 되는지도 검사해야 한다. 이거 때문에 또 틀렸다!
// 이거까지 수정해서 겨우겨우 맞혔다!!!
// 제한시간 1초 중 48ms(7040KB)가 소요되었다.
// 맞은사람 16/461로 상위 3.47%에 rank되었다.
// Contest > Waterloo's local Programming Contests > 1 June, 2002 D번

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue

using namespace std;

vector<int> g_pi;

int getPi(const string& str)
{
	int sz = (int)str.length();
	int mark = 0, tmp, result;
	for (int i = 1; i < sz; i++) {
		while (mark > 0 && str[mark] != str[i])
			mark = g_pi[mark - 1];
		if (str[mark] == str[i])
			g_pi[i] = ++mark;
	}
	tmp = sz - g_pi[sz - 1];
	//if ((g_pi[sz - 1] - tmp) % tmp) result = 1; // 가운데 겹치는 부분이 tmp의 배수가 아닐 경우 // sz % tmp로 비교해도 된다!
	if (sz % tmp) result = 1;
	else result = sz / tmp;
	return result;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	string a;
	while (true) {
		cin >> a;
		if (a == ".") break;
		g_pi.resize(a.length(), 0);
		cout << getPi(a) << "\n";
		g_pi.clear();
	}
}