// 2357.cpp
// �ּڰ��� �ִ밪
// �̹����� �־��� ������ ������ ���̳� ���� �ƴ� �ּҰ��� �ִ밪�� ���ϴ� �����̴�.
// ���׸�Ʈ Ʈ���� ������ ���ݸ� �����ϸ� ���� Ǯ �� �ִ�.
// �׸��� �߰��� ���� �ٲٴ� ���̽��� ���� ������ �� �����ϰ� Ǯ �� �ִ�.
// �ּҰ��� �ִ밪�̱� ������ makeTree() �Լ��� ���ϰ��� �ϳ��� �ƴ� {min, max} 2���� ��Ҵ�.
// ���ѽð� 2�� �� 112ms(4,832KB)�� �ҿ�Ǿ���.
// ������� 335/2513�� ���� 13.33%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
#include <cmath> // pow, sqrt, fabs, ceil, log2
#include <vector>
#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <functional> // less, greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct range {
	int min;
	int max;
	range() {}
	range(int a, int b) : min(a), max(b) {}
};

vector<range> g_tree;
vector<range> g_nums;

range makeTree(int node, int start, int end)
{
	int mid;
	range a, b;
	if (start == end) g_tree[node] = g_nums[start]; // leaf node
	else {
		mid = (start + end) / 2;
		a = makeTree(2 * node, start, mid);
		b = makeTree(2 * node + 1, mid + 1, end);
		g_tree[node] = { min({a.min, a.max, b.min, b.max}), max({a.min, a.max, b.min, b.max}) };
	}
	return g_tree[node];
}

range find(int node, int start, int end, int left, int right)
{
	int mid;
	range a, b;
	if (left > end || right < start) return range(-1, -1);
	else if (left <= start && end <= right) return g_tree[node];
	else {
		mid = (start + end) / 2;
		a = find(2 * node, start, mid, left, right);
		b = find(2 * node + 1, mid + 1, end, left, right);
		if (a.min == -1) return b;
		else if (b.min == -1) return a;
		else
			return range(min({ a.min, a.max, b.min, b.max }), max({ a.min, a.max, b.min, b.max }));
	}
}

int main()
{
	FAST;

	int n, m, a, b, num;
	range answer;
	int h, treeSize;

	cin >> n >> m;
	h = (int)ceil(log2(n));
	treeSize = 1 << (h + 1);
	g_tree.resize(treeSize, { 0, 0 });
	g_nums.resize(n + 1, { 0, 0 });
	for (int i = 1; i <= n; i++) {
		cin >> num;
		g_nums[i] = { num, num };
	}
	makeTree(1, 1, n);
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		answer = find(1, 1, n, a, b);
		cout << answer.min << " " << answer.max << "\n";
	}
}