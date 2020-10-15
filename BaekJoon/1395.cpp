// 1395
// ����ġ
// �� ������ �ƹ��� ���� ����� segment tree with lazy propagation���� Ǯ��� �Ѵ�.
// fenwick tree�� Ǯ����� �߾ �� ������ �������� Ǫ�� ������ �ƴϴ�!!
// Ư�� ��忡�� switch ������ �Ͼ�� �� ����� ���� 0�� ����� �����̴�. �� g_tree[node] = cnt - g_tree[node] �̴�.
// ��? 0->1�� 1->0���� �ٲ�� ������...
// switch ������ �Ͼ�� �ڽ� ��忡 lazy ������Ʈ�� �ϴµ� ���� lazy���� ^1 ���ָ� toggle�Ǿ�
// �������� switch ���� ���ΰ� �����ȴ�.
// �������� switch �� ����  ������ ���� ó�� ���� ������ ���ϴµ� �ش� ��忡�� lazy ������Ʈ �ϴ� �κи�
// �߰��� �ָ� �ȴ�.
// Olympiad > USA Computing Olympiad > 2008-2009 Season > USACO November 2008 Contest > Gold 3��
// ���ѽð� 1�� �� 88ms(4,048KB)�� �ҿ�Ǿ���.
// ������� 120/797�� ���� 15.05%�� rank�Ǿ���.

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
	int val;
	int lazy;
	node() {}
	node(int v, int l) : val(v), lazy(l) {}
};

vector<node> g_tree;

void lazy_update(int node, int start, int end, int left, int right)
{
	int cnt = (end - start + 1), mid;
	// ���� node�� lazy���� �ִ� ��� �ﰢ sum�� �ݿ��ϰ� �Ʒ��� �����Ѵ�.
	if (g_tree[node].lazy != 0) {		
		g_tree[node].val = (cnt - g_tree[node].val);
		if (start < end) {
			g_tree[2 * node].lazy ^= 1; // ���� child�� lazy �ݿ�
			g_tree[2 * node + 1].lazy ^= 1; // ������ child�� lazy �ݿ�
		}
	}
	g_tree[node].lazy = 0; // ������ ��Ȱ�� ���ϵ��� �ʱ�ȭ

	if (left > end || right < start) return; // ������Ʈ ������ ���
	else if (left <= start && end <= right) { // ������Ʈ ������ ��ġ��		
		g_tree[node].val = (cnt - g_tree[node].val);
		if (start < end) {
			g_tree[2 * node].lazy ^= 1; // ���� child�� lazy �ݿ�
			g_tree[2 * node + 1].lazy ^= 1; // ������ child�� lazy �ݿ�
		}
		return;
	}
	else { // ������Ʈ ������ �Ϻθ� ������
		mid = (start + end) / 2;
		lazy_update(2 * node, start, mid, left, right);
		lazy_update(2 * node + 1, mid + 1, end, left, right);
		// child node���� ������Ʈ �Ǿ��� ��� parent node�� �װ��� �ݿ��Ѵ�.
		g_tree[node].val = g_tree[2 * node].val + g_tree[2 * node + 1].val;
	}
}

int lazy_sum(int node, int start, int end, int left, int right)
{
	int cnt = (end - start + 1), mid;
	// ���� node�� lazy���� �ִ� ��� �ﰢ sum�� �ݿ��ϰ� �Ʒ��� �����Ѵ�.
	if (g_tree[node].lazy != 0) {
		g_tree[node].val = (cnt - g_tree[node].val);
		if (start < end) {
			g_tree[2 * node].lazy ^= 1; // ���� child�� �ݿ�
			g_tree[2 * node + 1].lazy ^= 1; // ������ child�� �ݿ�
		}
	}
	g_tree[node].lazy = 0; // ������ ��Ȱ�� ���ϵ��� �ʱ�ȭ

	if (left > end || right < start) return 0;
	else if (left <= start && end <= right) return g_tree[node].val;
	else {
		mid = (start + end) / 2;
		return lazy_sum(2 * node, start, mid, left, right) + lazy_sum(2 * node + 1, mid + 1, end, left, right);
	}
}

int main()
{
	FAST;

	int n, m, o, s, t;
	int h, treeSize;

	cin >> n >> m;
	h = (int)ceil(log2(n));
	treeSize = 1 << (h + 1);
	g_tree.resize(treeSize, { 0, 0 });

	for (int i = 0; i < m; i++) {
		cin >> o >> s >> t;
		if (o == 0) {
			lazy_update(1, 1, n, s, t);
		}
		else if (o == 1) {
			cout << lazy_sum(1, 1, n, s, t) << "\n";
		}
	}
}