// 16975_1.cpp
// ������ ���� 21
// �ռ� 16975�� ���׸�Ʈ Ʈ���� ����ϰ� lazy propagation�� ������� �ʰ�
// �����ߴٸ� �̹����� 16975�� ���׸�Ʈ Ʈ������ lazy propagation�� ����ؼ�
// �����Ѵ�. Ư�� ���� ������Ʈ �Ŀ� ������Ʈ �� �������� �ϳ��� ���ڸ� ����ϴ� �����̸�
// ���� lazy propagation�� �������� �ʰ� ������ �� ������ ���� ������Ʈ �Ŀ�
// ���� ���� ���ϴ� �����̸� lazy propagation�� �̿��ؼ� �����ϴ� ���� ȿ�����̴�.
// �� ������ ���ؼ��� lazy propagation���� Ǫ�� ���� �ð��� �� ���� �ɷȴ�!!!(80ms -> 100ms)
// ���ѽð� 2�� �� 100ms(6,884KB)�� �ҿ�Ǿ���.
// ������� 103/165�� ���� 62.42%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
#include <cmath> // pow, sqrt, fabs, ceil, log2
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

struct node {
	long long sum;
	long long lazy;
	node() {}
	node(long long s, long long l) : sum(s), lazy(l) {}
};

vector<node> g_tree;
vector<long long> g_nums;

long long makeTree(int node, int start, int end)
{
	int mid;
	if (start == end) g_tree[node].sum = g_nums[start]; // leaf node
	else {
		mid = (start + end) / 2;
		g_tree[node].sum = makeTree(2 * node, start, mid) + makeTree(2 * node + 1, mid + 1, end);
	}
	return g_tree[node].sum;
}

void lazy_update(int node, int start, int end, int left, int right, long long diff)
{
	int range = end - start + 1, mid;
	// ���� node�� lazy���� �ִ� ��� �ﰢ sum�� �ݿ��ϰ� �Ʒ��� �����Ѵ�.
	if (g_tree[node].lazy != 0) {
		g_tree[node].sum += range * g_tree[node].lazy; // sum�� �ݿ�
		if (start < end) {
			g_tree[2 * node].lazy += g_tree[node].lazy; // ���� child�� lazy �ݿ�
			g_tree[2 * node + 1].lazy += g_tree[node].lazy; // ������ child�� lazy �ݿ�
		}
	}
	g_tree[node].lazy = 0; // ������ ��Ȱ�� ���ϵ��� �ʱ�ȭ

	if (left > end || right < start) return; // ������Ʈ ������ ���
	else if (left <= start && end <= right) { // ������Ʈ ������ ��ġ��
		g_tree[node].sum += range * diff;
		if (start < end) {
			g_tree[2 * node].lazy += diff; // ���� child�� lazy �ݿ�
			g_tree[2 * node + 1].lazy += diff; // ������ child�� lazy �ݿ�
		}
		return;
	}
	else { // ������Ʈ ������ �Ϻθ� ������
		mid = (start + end) / 2;
		lazy_update(2 * node, start, mid, left, right, diff);
		lazy_update(2 * node + 1, mid + 1, end, left, right, diff);
		// child node���� ������Ʈ �Ǿ��� ��� parent node�� �װ��� �ݿ��Ѵ�.
		g_tree[node].sum = g_tree[2 * node].sum + g_tree[2 * node + 1].sum;
	}
}

long long lazy_sum(int node, int start, int end, int left, int right)
{
	int range = end - start + 1, mid;
	// ���� node�� lazy���� �ִ� ��� �ﰢ sum�� �ݿ��ϰ� �Ʒ��� �����Ѵ�.
	if (g_tree[node].lazy != 0) {
		g_tree[node].sum += range * g_tree[node].lazy; // sum�� �ݿ�
		if (start < end) {
			g_tree[2 * node].lazy += g_tree[node].lazy; // ���� child�� �ݿ�
			g_tree[2 * node + 1].lazy += g_tree[node].lazy; // ������ child�� �ݿ�
		}
	}
	g_tree[node].lazy = 0; // ������ ��Ȱ�� ���ϵ��� �ʱ�ȭ

	if (left > end || right < start) return 0;
	else if (left <= start && end <= right) return g_tree[node].sum;
	else {
		mid = (start + end) / 2;
		return lazy_sum(2 * node, start, mid, left, right) + lazy_sum(2 * node + 1, mid + 1, end, left, right);
	}
}

int main()
{
	FAST;

	int n, m, a, b, c, d;
	int h, treeSize;
	long long result;

	cin >> n;
	h = (int)ceil(log2(n));
	treeSize = 1 << (h + 1);
	g_tree.resize(treeSize, { 0, 0 });
	g_nums.resize(n + 1, 0);
	for (int i = 1; i <= n; i++)
		cin >> g_nums[i];
	makeTree(1, 1, n);

	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> a;
		if (a == 1) {
			cin >> b >> c >> d;
			lazy_update(1, 1, n, b, c, d);
		}
		else if (a == 2) {
			cin >> b;
			result = lazy_sum(1, 1, n, b, b);
			cout << result << "\n";
		}
	}
}
