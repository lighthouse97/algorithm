// 1043.cpp
// 거짓말
// 유니온 파인드에 query가 추가된 문제이다.
// query를 저장하고 각 query를 유니온으로 만든다.
// 각 query마다 파인드의 root가 진실을 알지 못하는 사람이면 카운트한다.
// 쿼리의 파티원으로부터 유니온 만들 때 파티원의 파인드가 진실인지 판단해서 만들어야 한다.
// 그냥 파티원만 진실인지 판단하면 틀린다. (실제로 틀렸다!)
// {1} <= 3 <= 4, 5 <= 4 일 때 파티원의 파인드로 판단하지 않으면 2번째 파티가 카운트되어 버린다!!!(카운트 0이 정답)
// truth인 사람들끼리 모아 union으로 만들어도 된다. 그러면 truth그룹의 root만 비교하면 된다.
// 제한시간 2초 중 0ms(2,020KB)가 소요되었다.
// 맞은사람 926/1787로 상위 51.81%에 rank되었다.

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
vector<bool> g_truth; // 진실을 알고 있는 자
vector<vector<int>> g_party; // party

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
	int N, M;
	cin >> N >> M;
	g_parent.resize(N + 1, -1);
	g_truth.resize(N + 1, false);
	g_party.resize(M);
	int t, tp;
	cin >> t;
	for (int i = 0; i < t; i++) {
		cin >> tp;
		g_truth[tp] = true;
	}
	int a, b, c, d;
	for (int i = 0; i < M; i++) { // query로 union 만듦
		cin >> a;
		g_party[i].resize(a);
		for (int j = 0; j < a; j++) {
			cin >> b;
			g_party[i][j] = b;
			if (j > 0) {
				c = djs_find(g_party[i][j - 1]);
				d = djs_find(g_party[i][j]);
				if (g_truth[c]) djs_union(c, d); // party 중 진실을 아는 사람이 있으면 그 사람 아래로 붙인다.
				else djs_union(d, c);
			}
		}
	}

	int cnt = 0;
	for (int i = 0; i < M; i++) { // query
		if (g_party[i].empty()) cnt++;
		else {
			a = g_party[i][0]; // party의 첫번째 멤버만 따지면 된다
			if (g_truth[djs_find(a)] == false) cnt++;
		}
	}
	cout << cnt << "\n";
}