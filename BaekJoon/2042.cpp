// 2042.cpp
// ���� �� ���ϱ�
// ��(11659)�� '���� �� ���ϱ� 4'�� �߰��� �־��� ���� �迭�� ���� �ٲ��� �ʾƼ�
// �ܼ��� ���� ��ȹ������ Ǯ�� ���� �ð��ȿ� �� Ǯ ���� ������
// �̹� ������ �߰� �߰��� �־��� ���� �迭�� ���� ��� �ٲ�� ������ �׶�����
// ������ȹ������ ��ü �������� ��� �ٽ� ����ؼ� ������Ʈ �ϸ� �־��� �ð����� ������ Ǯ ���� ����.
// ���� �� ������ ���׸�Ʈ Ʈ���� �̿��ؼ� �κ����� ����ؾ� �־��� �ð����� ������ Ǯ �� �ִ�.
// ���ѽð� 2�� �� 148ms(2,6200KB)�� �ҿ�Ǿ���.
// ������� 206/5118�� ���� 4.02%�� rank�Ǿ���.

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

vector<long long> g_tree;
vector<long long> g_nums;

long long makeTree(int node, int start, int end)
{
	int mid;
	if (start == end) g_tree[node] = g_nums[start]; // leaf node
	else {
		mid = (start + end) / 2;
		g_tree[node] = makeTree(2 * node, start, mid) + makeTree(2 * node + 1, mid + 1, end);
	}
	return g_tree[node];
}

long long sum(int node, int start, int end, int left, int right)
{
	int mid;
	if (left > end || right < start) return 0; // L-R not match with the node
	else if (left <= start && end <= right) return g_tree[node]; // L-R match totaly with the node
	else { // L-R match partialy with the node
		mid = (start + end) / 2;
		return sum(2 * node, start, mid, left, right) + sum(2 * node + 1, mid + 1, end, left, right);
	}
}

void update(int node, int start, int end, int index, long long diff)
{
	int mid;
	if (index < start || end < index) return; // update�� ������� ����
	g_tree[node] += diff;
	if (start != end) { // leaf node�� �ƴ� ���
		mid = (start + end) / 2;
		update(2 * node, start, mid, index, diff); // update left child node
		update(2 * node + 1, mid + 1, end, index, diff); // update right child node
	}
}

int main()
{
	FAST;

	int n, m, k, a, b;
	int h, treeSize;
	
	cin >> n >> m >> k;
	h = (int)ceil(log2(n));
	treeSize = 1 << (h + 1);
	g_tree.resize(treeSize, 0);
	g_nums.resize(n + 1, 0);
	for (int i = 1; i <= n; i++)
		cin >> g_nums[i];
	makeTree(1, 1, n);

	for (int i = 0; i < m + k; i++) {
		cin >> a;
		if (a == 1) { // update
			long long c, diff;
			cin >> b >> c;
			diff = c - g_nums[b];
			g_nums[b] = c;
			update(1, 1, n, b, diff);
		}
		else if (a == 2) { // sum
			int c;
			cin >> b >> c;
			cout << sum(1, 1, n, b, c) << "\n";
		}
	}
}