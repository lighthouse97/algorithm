// 14681.cpp
// 사분면 고르기
// 아주 쉬운 if문 문제이다.
// 그냥 풀면 된다.
// Olympiad > Canadian Computing Competition & Olympiad > 2017 > CCC 2017 Junior Division 1번

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
//#include <vector>
//#include <algorithm> // sort, max, min, copy, reverse
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <unordered_map> // unordered_map
//#include <bitset>
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
	FAST;

	int x, y, q;
	cin >> x >> y;

	q = (y > 0) ? ((x > 0) ? 1 : 2) : ((x > 0) ? 4 : 3);

	cout << q << "\n";
}