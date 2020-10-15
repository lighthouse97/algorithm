// 2193.cpp
// 이친수
// 이천수도 아니도 이친수!!!
// 패턴을 잘 봐야 한다.
// DP[N]의 0의 갯수는 DP[N-1]의 전체 갯수
// DP[N]의 1의 갯수는 DP[N-1]의 0의 갯수
// 또는 DP[i]를 쪼개지 않고 DP[N-1] + DP[N-2]로 접근해도 된다!
// 제한시간 2초 중 0ms(1984KB)가 소요되었다.
// 맞은사람 6496/12115로 상위 53.61%에 rank되었다.

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

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	long long answer;
	vector<vector<long long>> DP;
	DP.resize(91, vector<long long>(2, 0));
	DP[1][0] = 0;
	DP[1][1] = 1;
	for (int i = 2; i <= 90; i++) {
		DP[i][0] = DP[i - 1][0] + DP[i - 1][1];
		DP[i][1] = DP[i - 1][0];
	}
	cin >> N;
	answer = DP[N][0] + DP[N][1];
	cout << answer << "\n";
}