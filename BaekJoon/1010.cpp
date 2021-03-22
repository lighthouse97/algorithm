// 1010.cpp
// 다리 놓기
// 이항 계수(순열, Permutation)만 구하면 쉽게 구할 수 있다.
// 이항 계수는 동적계획볍(DP)를 이용해서 빠르게 구한다.
// 제한시간 0.5초 중 0ms(2,020KB)가 소요되었다.
// 맞은사람 4038/12028로 상위 33.57%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
//#include <vector>
//#include <algorithm> // sort, max, min, copy, swap, unique
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

int DP[31][31] = { { 0, }, };

void getBC(int n) // get Binomial Coefficient
{
	DP[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		DP[i][0] = 1;
		for (int j = i; j >= 1; j--)
			DP[i][j] = DP[i - 1][j] + DP[i - 1][j - 1];
	}	
}

int main()
{
	FAST;

	int T;
	cin >> T;	
	getBC(29);
	int n, m;
	for (int i = 0; i < T; i++) {
		cin >> n >> m;
		cout << DP[m][n] << "\n";
	}	
}