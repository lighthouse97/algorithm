// 7579.cpp
// 앱
// 동적프로그래밍으로 푼다.
// knapsack problem에서 풀었던 방법을 응용하였다.
// DP[i][j]가 i번째 app이 j의 cost조건이내에서 소요되는 최대 메모리 소요량이라고 한다면,
// DP[i][j] = MAX(DP[i-1][j], DP[i][j - app[i].cost] + app[i].memory)
// i는 app번호로 1 ~ N이고
// j는 cost 총합이 W라면 W ~ app[i].cost 까지 loop돈다.
// 주어진 메모리 소요량이 M이면 DP[i][j] >= M 인 j의 최소값을 구한다.
// 즉 구해진 값이 필요한 메모리 조건 M을 만족하면서, 소요 cost가 최소로 될 때의 cost가 된다.
// 참고...
// DP[]를 구할 때, i loop를 N까지 다 돌리는데, 다 돌리지 않고 (DP[j] >= M) 까지만 i loop를 돌려서
// 그 때까지의 DP[]를 이용해서 cost를 구하면 계속 틀린다. 그 이유를 아직까지 모르겠고 반례도 찾지를 못하겠다!!! 

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
#include <algorithm> // max, sort
//#include <climits> // INT_MAX
//#include <string>
#include <utility> // pair

using namespace std;

int N, M;
vector<pair<int, int>> APPS;
vector<int> DP;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int costsum = 0;
	int ans;
	cin >> N >> M;
	APPS.resize(N+1);

	for (int i = 1; i <= N; i++)
		cin >> APPS[i].second; // read memory
	for (int i = 1; i <= N; i++) {
		cin >> APPS[i].first; // read cost
		costsum += APPS[i].first;
	}
	DP.resize(costsum + 1, 0);

	for (int i = 1; i <= N; i++) {
		for (int j = costsum; j >= APPS[i].first; j--) {
			DP[j] = max(DP[j], DP[j - APPS[i].first] + APPS[i].second);
		}
	}

	for (ans = 0; ans < costsum; ans++) {
		if (DP[ans] >= M) break;
	}
	cout << ans << "\n";
}