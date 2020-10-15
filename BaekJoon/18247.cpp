// 18247.cpp
// 겨울왕국 티켓 예매
// 2019 GoodBye 컨테스트에 나왔던 문제이고 별로 안어려워 보이기에 바로 풀어버렸다!
// Contest > Good Bye, BOJ > Good Bye, BOJ 2019! A번
// 제한시간 1초 중 0ms(1984KB)가 소요되었다.
// 맞은사람 126/219로 상위 57.53%에 rank되었다.

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
//#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int T, N, M;
	int target_r = 'L' - 'A' + 1;
	int target_c = 4;
	int result;
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> N >> M;
		if (target_r <= N && target_c <= M) {
			result = (target_r - 1)*M + target_c;
			cout << result << "\n";
		}
		else cout << -1 << "\n";
	}
}