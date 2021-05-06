// 16562.cpp
// 친구비
// University > 서강대학교 > 2018 Sogang Programming Contest (Master) B번
// 유니온 파인드 문제이다.
// 유니온 할 때 비용이 작은 것을 조상으로 두는 것이 핵심이다.
// 그리고 각 그룹의 조상의 비용을 다 합하면 되는데 주어진 비용을 초과하는지 따져봐야 한다.
// 제한시간 2초 중 4ms(2,176KB)가 소요되었다.
// 맞은사람 571/1444로 상위 39.54%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
//#include <list>
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

vector<int> g_parent; // disjoint set
vector<int> g_cost; // cost

int djs_find(int x) // find 함수
{
	if (g_parent[x] < 0) return x; // 자신이 root
	return g_parent[x] = djs_find(g_parent[x]);
}

void djs_union(int x, int y) // union 함수
{
	int r1 = djs_find(x);
	int r2 = djs_find(y);

	if (r1 == r2) return;
	g_parent[r1] += g_parent[r2];
	g_parent[r2] = r1;
}

int main()
{
	FAST;
	int N, M, K;
	cin >> N >> M >> K;
	g_parent.resize(N + 1, -1);
	g_cost.resize(N + 1, 0);
	for (int i = 1; i < N + 1; i++) cin >> g_cost[i];
	int a, b, x, y;
	for (int i = 0; i < M; i++) { // 친구 관계
		cin >> a >> b;
		x = djs_find(a);
		y = djs_find(b);
		if (g_cost[x] <= g_cost[y]) djs_union(x, y);
		else djs_union(y, x);
	}
	int sum = 0;
	vector<bool> check(N + 1, false);
	for (int i = 1; i < N + 1; i++) {
		x = djs_find(i);
		if (!check[x]) { check[x] = true; sum += g_cost[x]; }
	}
	if (sum <= K) cout << sum << "\n";
	else cout << "Oh no" << "\n";
}