// 16562.cpp
// ģ����
// University > �������б� > 2018 Sogang Programming Contest (Master) B��
// ���Ͽ� ���ε� �����̴�.
// ���Ͽ� �� �� ����� ���� ���� �������� �δ� ���� �ٽ��̴�.
// �׸��� �� �׷��� ������ ����� �� ���ϸ� �Ǵµ� �־��� ����� �ʰ��ϴ��� �������� �Ѵ�.
// ���ѽð� 2�� �� 4ms(2,176KB)�� �ҿ�Ǿ���.
// ������� 571/1444�� ���� 39.54%�� rank�Ǿ���.

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

int main()
{
	FAST;
	int N, M, K;
	cin >> N >> M >> K;
	g_parent.resize(N + 1, -1);
	g_cost.resize(N + 1, 0);
	for (int i = 1; i < N + 1; i++) cin >> g_cost[i];
	int a, b, x, y;
	for (int i = 0; i < M; i++) { // ģ�� ����
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