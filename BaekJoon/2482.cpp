// 2482.cpp
// 색상환
// 동적프로그래밍으로 푸는데 밤새고민해서 푼게 틀렸다!
// 점화식 세운 것을 다른 사람이 푼 것을 봤는데 이해 하는데도 한참 걸렸다.
// 사실 아직도 잘 이해가 안간다.
// N개의 색상에서 서로 인접하지 않게 K개를 고르는 경우의 수를
// DP[N][K]에 저장한다면
// DP[N][K] = DP[N-2][K-1] + DP[N-1][K] 가 된다.
// DP[N-2][K-1] : 임의로 하나를 고르면 인접한 1개가 빠지므로 전체 N-2개로 줄어들고, 남은 것중에서 K-1개 선택
// DP[N-1][K] : 임의로 하나를 고르지 않으면 전체 N-1개로 줄어들고, 남은 것 중에서 K개 선택
// 예를 들어 이해를 하려고 해도 얼추맞는 다는 것만 알 뿐, 정확한 예를 들 수가 없었다.
// 임의의 하나 선택은 뭘 해도 결국 K개의 조합은 똑같다.(이것은 예를 들어 살펴 보면 알 수 있다)

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <cstdlib> // abs
#include <vector>
//#include <algorithm> // max, min, sort
//#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair
//#include <stack> // stack
//#include <bitset> // bitmask

using namespace std;

const int MOD = 1000000003;
int N, K;
vector<vector<int>> DP;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> K;
	DP.resize(N + 1, vector<int>(N + 1, 0)); // 0으로 초기화!

	// N = 1 ~ 3 까지 기록
	for (int i = 1; i <= 3; i++)
		DP[i][1] = i;
	for (int i = 4; i <= N; i++) {
		for (int j = 1; j <= i / 2; j++) { // N/2 보다 큰 갯수 선택은 경우의 수 모두 0
			if (j == 1) DP[i][j] = i;
			else
				DP[i][j] = (DP[i - 2][j - 1] + DP[i - 1][j]) % MOD;
		}
	}
	cout << DP[N][K] << "\n";
}