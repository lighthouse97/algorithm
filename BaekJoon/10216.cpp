// 10216.cpp
// Count Circle Groups
// Contest > Coder's High > Coder's High 2014 C번
// 유니온 파인드 문제이다.
// 그룹을 만들 수 있는게 해결의 키포인트이다.
// 일단 그룹을 만들면 주어진 적군 진영으로부터 만들어진 그룹의 갯수를 세면 된다.
// 그룹을 만드는 방법은 두원이 겹치는지 여부인데 반지름의 합이 두원의 중심보다 같거나 크면 겹치고 아니면 겹치지 않는다.
// 제한시간 8초 중 988ms(2,152KB)가 소요되었다.
// 맞은사람 183/1510로 상위 12.11%에 rank되었다.

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

struct circle {
	int x, y, r;
	circle() : x(0), y(0), r(0) {}
	circle(int x, int y, int r) : x(x), y(y), r(r) {}
	inline bool isIntersect(const circle& rhs) const {
		int rsum = r + rhs.r;
		int diff_x = x - rhs.x;
		int diff_y = y - rhs.y;
		return (rsum)*(rsum) >= (diff_x)*(diff_x) + (diff_y)*(diff_y);
	}
};

vector<int> g_parent; // disjoint set
vector<circle> g_group;

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

void doTest()
{
	int N;
	cin >> N;
	g_parent.resize(N + 1, -1);
	g_group.resize(N + 1);
	int x, y, r;
	for (int i = 1; i < N + 1; i++) {
		cin >> x >> y >> r;
		g_group[i] = { x, y, r }; // 적군 진영 입력
	}
	for (int i = 1; i < N + 1; i++) {
		for (int j = i + 1; j < N + 1; j++) {
			if (g_group[i].isIntersect(g_group[j])) djs_union(i, j); // 유니온으로 그룹화
		}
	}
	int cnt = 0;
	vector<int> check(N + 1, false);
	for (int i = 1; i < N + 1; i++) {
		r = djs_find(i);
		if (!check[r]) { check[r] = true; cnt++; }
	}
	cout << cnt << "\n";
	g_parent.clear();
	g_group.clear();
}

int main()
{
	FAST;
	int T;
	cin >> T;
	while (T--) doTest();
}