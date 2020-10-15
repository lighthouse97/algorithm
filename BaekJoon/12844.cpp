// 12844.cpp
// XOR
// segment tree with lazy propagation���� Ǭ��.
// ���׸�Ʈ Ʈ���� �� ��忡 �������� �ƴ� ���� XOR ���� �����صд�.
// ������ ������ k�� XOR�� ��, ������ ������ ������ ¦���̸� ��忡 0�� XOR�ϰ�
// ������ ������ ������ Ȧ���̸� ��忡 k�� XOR�ϸ� �ȴ�. (XOR�� �Ӽ��� �׷���!)
// a ~ b�����̶�� ���� a < b�� ���� �ƴϴ�! a > b �ϼ��� �ִ�. �̰Ŷ����� �ѹ� Ʋ�ȴ�!
// University > ���Ǵ��б� > SCCC 2016 Summer Contest F��
// ���ѽð� 2�� �� 540ms(12,064KB)�� �ҿ�Ǿ���.
// ������� 33/461�� ���� 7.15%�� rank�Ǿ���.

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
#include <utility> // pair, swap
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
vector<int> g_nums;

int makeTree(int node, int start, int end)
{
	int mid;
	if (start == end) g_tree[node].val = g_nums[start]; // leaf node
	else {
		mid = (start + end) / 2;
		g_tree[node].val = makeTree(2 * node, start, mid) ^ makeTree(2 * node + 1, mid + 1, end);
	}
	return g_tree[node].val;
}

void lazy_update(int node, int start, int end, int left, int right, int diff)
{
	int flag = (end - start + 1) % 2, mid;
	// ���� node�� lazy���� �ִ� ��� �ﰢ sum�� �ݿ��ϰ� �Ʒ��� �����Ѵ�.
	if (g_tree[node].lazy != 0) {
		g_tree[node].val ^= ((flag) ? g_tree[node].lazy : 0);
		if (start < end) {
			g_tree[2 * node].lazy ^= g_tree[node].lazy; // ���� child�� lazy �ݿ�
			g_tree[2 * node + 1].lazy ^= g_tree[node].lazy; // ������ child�� lazy �ݿ�
		}
	}
	g_tree[node].lazy = 0; // ������ ��Ȱ�� ���ϵ��� �ʱ�ȭ

	if (left > end || right < start) return; // ������Ʈ ������ ���
	else if (left <= start && end <= right) { // ������Ʈ ������ ��ġ��
		g_tree[node].val ^= ((flag) ? diff : 0);
		if (start < end) {
			g_tree[2 * node].lazy ^= diff; // ���� child�� lazy �ݿ�
			g_tree[2 * node + 1].lazy ^= diff; // ������ child�� lazy �ݿ�
		}
		return;
	}
	else { // ������Ʈ ������ �Ϻθ� ������
		mid = (start + end) / 2;
		lazy_update(2 * node, start, mid, left, right, diff);
		lazy_update(2 * node + 1, mid + 1, end, left, right, diff);
		// child node���� ������Ʈ �Ǿ��� ��� parent node�� �װ��� �ݿ��Ѵ�.
		g_tree[node].val = g_tree[2 * node].val ^ g_tree[2 * node + 1].val;
	}
}

int lazy_xor(int node, int start, int end, int left, int right)
{
	int flag = (end - start + 1) % 2, mid;
	// ���� node�� lazy���� �ִ� ��� �ﰢ sum�� �ݿ��ϰ� �Ʒ��� �����Ѵ�.
	if (g_tree[node].lazy != 0) {
		g_tree[node].val ^= ((flag) ? g_tree[node].lazy : 0);
		if (start < end) {
			g_tree[2 * node].lazy ^= g_tree[node].lazy; // ���� child�� �ݿ�
			g_tree[2 * node + 1].lazy ^= g_tree[node].lazy; // ������ child�� �ݿ�
		}
	}
	g_tree[node].lazy = 0; // ������ ��Ȱ�� ���ϵ��� �ʱ�ȭ

	if (left > end || right < start) return 0;
	else if (left <= start && end <= right) return g_tree[node].val;
	else {
		mid = (start + end) / 2;
		return lazy_xor(2 * node, start, mid, left, right) ^ lazy_xor(2 * node + 1, mid + 1, end, left, right);
	}
}

int main()
{
	FAST;

	int n, m;
	int h, treeSize;
	int t, a, b, c;
	int result;

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
		cin >> t >> a >> b;
		if (a > b) swap(a, b);
		if (t == 1) { // update
			cin >> c;
			lazy_update(1, 1, n, a + 1, b + 1, c);
		}
		else if (t == 2) { // xor
			result = lazy_xor(1, 1, n, a + 1, b + 1);
			cout << result << "\n";
		}
	}
}