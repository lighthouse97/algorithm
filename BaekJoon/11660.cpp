// 11660.cpp
// 구간 합 구하기 5
// 2차원 배열의 구간합을 구하는 문제이다.
// 배열의 값이 중간에 바뀌지 않으므로 DP를 사용해서 풀 수 있다.
// 다음에 나오는 '구간 합 구하기 3'이 중간에 값이 계속 바뀌므로
// 2차원 배열에 대한 세그먼트 트리를 사용하는 어려운 문제이다.
// 동적 프로그래밍의 점화식은 다음과 같다.
// DP[i, j] = DP[i-1, j] + DP[i, j-1] - DP[i-1, j-1] + NUM[i, j]
// 구간합의 식은 다음과 같다.
// SUM[x1, y1, x2, y2] = DP[x2, y2] - DP[x2, y1-1] - DP[x1-1, y2] + DP[x1-1, y1-1]
// 그렇게 어려운 문제는 아닌데 수식 만드는데 시간이 제법 걸렸다!
// 제한시간 1초 중 132ms(6,228KB)가 소요되었다.
// 맞은사람 85/2152로 상위 3.94%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs, ceil, log2
#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <functional> // less, greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_DP;

int main()
{
	FAST;

	int n, m, num, x1, x2, y1, y2, sum;
	cin >> n >> m;
	g_DP.resize(n + 1, vector<int>(n + 1, 0));

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> num;
			g_DP[i][j] = g_DP[i - 1][j] + g_DP[i][j - 1] - g_DP[i - 1][j - 1] + num;
		}
	}

	for (int i = 0; i < m; i++) {
		cin >> x1 >> y1 >> x2 >> y2;
		sum = g_DP[x2][y2] - g_DP[x2][y1 - 1] - g_DP[x1 - 1][y2] + g_DP[x1 - 1][y1 - 1];
		cout << sum << "\n";
	}
}