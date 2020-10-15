// 2042_1.cpp
// ���� �� ���ϱ�
// �� 2042���� ���׸�Ʈ Ʈ��(segment tree)�� ���ߴ� ���� �� ������
// ����Ʈ��(Fenwick Tree)�� �̿��ؼ� Ǯ���� �Ѵ�.
// ����Ʈ���� Ǫ�� �ð��� �� �� ���� ���Դ�. 148ms(2,6200KB) -> 160ms(17,616KB)
// ������� �ϴ� ���� ��������� ���� ���� ���� Ʈ���� �� �������� ���� �� �ϴ� ������ ���.

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

// Fenwick version
vector<long long> g_tree;
vector<long long> g_nums;
int g_N;

void update(int index, long long diff)
{
	int i = index;

	while (i <= g_N) {
		g_tree[i] += diff;
		i += (i & -i);
	}
}

long long sum(int end)
{
	int i = end;
	long long ret = 0;

	while (i > 0) {
		ret += g_tree[i];
		i -= (i & -i);
	}
	return ret;
}

int main()
{
	FAST;

	int n, m, k, a, b;

	cin >> n >> m >> k;
	g_N = n;
	g_tree.resize(n + 1, 0);
	g_nums.resize(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		cin >> g_nums[i];
		update(i, g_nums[i]);
	}

	for (int i = 0; i < m + k; i++) {
		cin >> a;
		if (a == 1) { // update
			long long c, diff;
			cin >> b >> c;
			diff = c - g_nums[b];
			g_nums[b] = c;
			update(b, diff);
		}
		else if (a == 2) { // sum
			int c;
			cin >> b >> c;
			cout << (sum(c) - sum(b-1)) << "\n";
		}
	}
}