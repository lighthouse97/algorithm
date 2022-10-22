// 11478.cpp
// 서로 다른 부분 문자열의 개수
// 부분 문자열을 모두 구해서 이를 unordered_set에 넣을 때 중복되는 부분 문자열을
// 찾는 문제이다.
// Suffix array 나 LCP 같은 문자열 알고리즘을 이용하면 더 빠르게 처리할 수 있다.
// 일단은 unordered_set를 사용해서, 211,832KB, 628ms 소요되었다.
// 풀이는 간단하지만 성능은 그리 좋지 못하다!

#include "pch.h"
#include <iostream>
//#include <sstream>
//#include <string>
//#include <cstring> // strlen
//#include <cctype> // isdigit
//#include <vector>
//#include <list>
//#include <algorithm> // sort
//#include <unordered_map>
//#include <utility> // pair, make_pair()
//#include <set>
#include <unordered_set>
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
	FAST;

	unordered_set<string> str_set;

	string str, substr;
	cin >> str;
	// 부분 문자열을 구한다.
	for (int length = 1; length <= str.length(); length++) {
		for (int start = 0; start + length - 1 < str.length(); start++) {
			substr = str.substr(start, length);
			str_set.insert(substr);
		}
	}

	cout << str_set.size() << '\n';
}