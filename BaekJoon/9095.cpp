// 9095.cpp
// 1,2,3 더하기
// 간단한 DP 문제인데 많이 헤맸다!
// ICPC > Regionals > Asia Pacific > Korea > Asia Regional - Taejon 2001 PC번

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue

using namespace std;

int T;
vector<int> DP;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int num;
	cin >> T;
	DP.resize(11, 0);
	DP[1] = 1;
	DP[2] = 2;
	DP[3] = 4;
	for (int i = 4; i <= 10; i++)
		DP[i] = DP[i - 1] + DP[i - 2] + DP[i - 3];
	
	for (int i = 0; i < T; i++) {
		cin >> num;
		cout << DP[num] << "\n";
	}
}