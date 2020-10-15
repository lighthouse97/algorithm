// 9345.cpp
// ������ ���� ��ũ(DVDs)
// Ư�� ������ �ִ� �ּҰ��� ������ ������ �ٲ������ ���θ� üũ�ϴ� ������ ���� �ȴ�.
// 2357(�ּҰ��� �Ҵ밪) ���ϴ� ������ �̿��ϵ� ������Ʈ �ϴ� �κи� �߰���Ű�� �ȴ�.
// ICPC > Regionals > Asia Pacific > Thailand > Asia Thailand National Programming Contest > 2013 ACM-ICPC Thailand National Programming Contest G��
// ���߱�� ������ ���� �ð��� �� ���� ���� ���ε�, �� ����ȭ�� �� ���� ������ �� ���� ������ Ǯ������ �׳� �Ѿ��� �Ѵ�.
// ���ѽð� 2�� �� 452ms(4,972KB)�� �ҿ�Ǿ���.
// ������� 181/352�� ���� 51.42%�� rank�Ǿ���.

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

range update(int node, int start, int end, int index)
{
	int mid;
	range a, b;
	if (start <= index && index <= end) { // index�� �ش��ϴ� node�� min max update �Ѵ�.
		if (start == end) g_tree[node] = g_nums[start];
		else {
			mid = (start + end) / 2;
			a = update(2 * node, start, mid, index);
			b = update(2 * node + 1, mid + 1, end, index);
			g_tree[node] = { min({a.min, a.max, b.min, b.max}), max({a.min, a.max, b.min, b.max}) };
		}
	}
	return g_tree[node];
}

void do_test()
{
	int n, k, q ,a ,b;
	int h, treeSize;
	range found;
	cin >> n >> k;
	h = (int)ceil(log2(n));
	treeSize = 1 << (h + 1);
	g_tree.resize(treeSize, { 0, 0 });
	g_nums.resize(n, { 0, 0 });
	for (int i = 0; i < n; i++)
		g_nums[i] = { i, i };
	makeTree(1, 0, n - 1); // node, start, end

	for (int i = 0; i < k; i++) {
		cin >> q >> a >> b;
		if (q == 0) { // upadte
			range temp = g_nums[a];
			g_nums[a] = g_nums[b];
			g_nums[b] = temp;
			update(1, 0, n - 1, a);
			update(1, 0, n - 1, b);
		}
		else if (q == 1) { // find
			found = find(1, 0, n - 1, a, b);
			cout << ((found.min == a && found.max == b) ? "YES" : "NO") << "\n";
		}
	}
	g_tree.clear();
	g_nums.clear();
}

int main()
{
	FAST;

	int t;
	cin >> t;
	for (int i = 0; i < t; i++)
		do_test();
}
