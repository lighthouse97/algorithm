// 1305.cpp
// 광고(advertisement)
// 전체 길이가 L이면 PI[L-1](PI배열은 0부터 시작한다)의 값이 길이 L 광고판에서
// 광고판 내 앞 뒤 두개의 광고 문구에서 겹치는 광고 문자열이 된다.
// 따라서 L - PI[L-1]의 값이 겹치는 광고문구에서 겹치는 문자열을 제외하고 가능한 광고의
// 길이 중 가장 짧은 광고의 길이가 된다.
// 간단한 문제인데... 너무 어렵게 생각해 버렸다!!!
// 제한시간 2초 중 12ms(7040KB)가 소요되었다.
// 맞은사람 142/941로 상위 15.09%에 rank되었다.

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
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<int> g_pi;

void getPi(const string& str)
{
	int sz = (int)str.length();
	int mark = 0;
	g_pi.resize(sz, 0);
	for (int i = 1; i < sz; i++) {
		// mark > 0이고 다른 문자가 나오면 mark 앞의 prefix 다음부터 비교한다.
		// prefix가 없으면 처음부터 비교한다		
		while (mark > 0 && str[mark] != str[i]) {
			mark = g_pi[mark - 1];
		}
		if (str[mark] == str[i]) {
			g_pi[i] = ++mark; // 맨 앞과 맨 끝이 같으면 각각 index + 1, 동시에 PI[]를 업데이트 한다
		}
	}
}

int main()
{
	FAST;

	int L;
	string a;
	cin >> L >> a;
	getPi(a);
	cout << L - g_pi.back() << "\n";
}