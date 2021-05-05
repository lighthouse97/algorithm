// 10216.cpp
// Count Circle Groups
// Contest > Coder's High > Coder's High 2014 C��
// ���Ͽ� ���ε� �����̴�.
// �׷��� ���� �� �ִ°� �ذ��� Ű����Ʈ�̴�.
// �ϴ� �׷��� ����� �־��� ���� �������κ��� ������� �׷��� ������ ���� �ȴ�.
// �׷��� ����� ����� �ο��� ��ġ���� �����ε� �������� ���� �ο��� �߽ɺ��� ���ų� ũ�� ��ġ�� �ƴϸ� ��ġ�� �ʴ´�.
// ���ѽð� 8�� �� 988ms(2,152KB)�� �ҿ�Ǿ���.
// ������� 183/1510�� ���� 12.11%�� rank�Ǿ���.

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

int djs_find(int x) // find �Լ�
{
	if (g_parent[x] < 0) return x; // �ڽ��� root
	return g_parent[x] = djs_find(g_parent[x]);
}

void djs_union(int x, int y) // union �Լ�
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
		g_group[i] = { x, y, r }; // ���� ���� �Է�
	}
	for (int i = 1; i < N + 1; i++) {
		for (int j = i + 1; j < N + 1; j++) {
			if (g_group[i].isIntersect(g_group[j])) djs_union(i, j); // ���Ͽ����� �׷�ȭ
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