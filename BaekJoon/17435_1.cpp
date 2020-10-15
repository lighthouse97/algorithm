// 17435_1.cpp
// 합성함수와 쿼리
// 앞에서 푼 것이 시간이 상대적으로 많이 걸려서 최적화 시켜보았다.
// 벡터 사용이 원인이었다. 벡터를 배열로 바꾸니
// 제한시간 1초 중 292ms(16828KB)가 소요되었다.
// 맞은사람 69/123로 상위 56.09%에 rank되었다.
// 그리고 dp[][] 배열을 순서를 바꾸어 log index인 i값을 앞에 오게하고 정수 n의 값을 뒤에
// 오게 하면 244(16828KB)로 48ms의 시간이 감소하였다.(약 16% 개선)
// 이렇게 하면 37/123으로 상위 30.08%에 rank된다.

#include "pch.h"
//#include <cstdio> // NULL
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
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const int g_max_i = 18;
int dp[g_max_i + 1][200001] = { {0, }, };

int main()
{
	FAST

	int m, q, n, x;
	//vector<vector<int>> dp;
	cin >> m;
	//dp.resize(m + 1, vector<int>(g_max_i + 1, 0));
	// initialise
	for (int i = 1; i <= m; i++)
		cin >> dp[0][i];
	for (int j = 1; j <= g_max_i; j++) {
		for (int i = 1; i <= m; i++) {
			dp[j][i] = dp[j - 1][dp[j - 1][i]];
		}
	}
	// find the result
	cin >> q;
	while (q--) {
		cin >> n >> x;
		for (int i = 0; i <= g_max_i; i++) {
			if (n & (1 << i)) x = dp[i][x];
		}
		cout << x << "\n";
	}
}