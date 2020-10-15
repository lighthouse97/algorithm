// 17435.cpp
// 합성함수와 쿼리
// 이 문제는 LCA 구현 중 일부에 대한 연습문제이다.
// LCA 알고리즘구현에서 각 노드의 2^i 부모 찾는 것을 점화식을 세우고 동적계획법으로
// 찾는다고 했는데 이 방법에 대한 연습이다.
// 참고로 동적계획법에서의 점화식은 par[x][i] = par[par[x][i-1]][i-1] 이다.
// 문제에서 주어진 n의 max 500,000을 모두 배열로 잡으면 메모리 초과가 난다.
// 그때그때 계산해야 겠다.
// 그때 그때 계산하니 시간초과 발생. 음...
// 결국 LCA에서와 같이 2^i 탐색이 필요하다는 말이다!
// 제한시간 1초 중 456ms(25416KB)가 소요되었다.
// 맞은사람 110/122로 상위 90.16%에 rank되었다.(거의 꼴찌~~)
// 좀 더 빠르게 최적화시킬 방법이 있을까?
// 벡터가 문제이다. 데이터 양이 많을 때는 벡터보다 전역 변수로 배열 선언하는 것이 훨씬 더 빠르다.
// 벡터만 전역 변수로 이차원 배열로 바꾸고 실행하면 276ms(16828KB)로 약 39.47%나 수행시간이 대폭 줄어든다.
// 이 때 등수는 60/123으로 상위 48.78%에 rank된다.
// 여기서 dp[][]에서 n의 값과 log 값의 순서만 바꿔주면 처리 시간은 더 단축된다.(그러나 문제의 본질에 크게 의미는 없어 보인다.)

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
int dp[200001][g_max_i + 1] = { {0, }, };

int main()
{
	FAST

	int m, q, n, x, depth;
	//vector<vector<int>> dp;
	cin >> m;
	//dp.resize(m + 1, vector<int>(g_max_i + 1, 0));
	// initialise
	for (int i = 1; i <= m; i++)
		cin >> dp[i][0];
	for (int j = 1; j <= g_max_i; j++) {
		for (int i = 1; i <= m; i++) {
			dp[i][j] = dp[dp[i][j-1]][j-1];
		}
	}
	// find the result
	cin >> q;
	while (q--) {
		cin >> n >> x;
		depth = n;
		for (int i = g_max_i; i >= 0; i--) {
			if (depth >= (1 << i)) {
				x = dp[x][i];
				depth -= (1 << i);
			}
		}
		cout << x << "\n";
	}
}