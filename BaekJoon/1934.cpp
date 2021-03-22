// 1934.cpp
// 최소공배수
// 간단한 수학(정수론) 문제이다.
// 유클리드 알고리즘(유클리드 호제법)으로 풀 수 있다.
// 즉 (A * B) / GCF = LCM 을 이용하면 된다...
// 제한시간 1초 중 0ms(2,016KB)가 소요되었다.
// 맞은사람 3613/12710로 상위 28.42%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
//#include <vector>
#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int getGCF(int a, int b)
{
	int large = a, small = b, temp;
	if (large < small) swap(large, small);

	while (small) {
		temp = large % small;
		large = small;
		small = temp;		
	}
	return large;
}

int main()
{
	FAST;

	int T;
	cin >> T;
	int a, b, gcf;
	for (int i = 0; i < T; i++) {
		cin >> a >> b;
		gcf = getGCF(a, b);
		cout << ((a * b) / gcf) << "\n";
	}		 
}