// 11505.cpp
// ���� �� ���ϱ�
// ���׸�Ʈ Ʈ���� �̿��� ���� ���� �ƴ϶� ���� ���̴�.
// ����� �Ȱ��� ������ ���̰� �� ���̾ƴϰ� ���� ���� �ٸ���.
// --> �Ȱ����� �ʰ� ���� ���� �� ������ ���� ���� 0�� �ƴ� 1�� �����ؾ� �ϰ� 
//     update �Լ��� �ش� ��常 �ٽ� �����־�� �Ѵ�.
// �׸��� ���ϸ� �� ���� Ŀ���Ƿ� ���� ����� 1,000,000,007�� �������� ����Ѵ�.
// ���ѽð� 1�� �� 140ms(2,6200KB)�� �ҿ�Ǿ���.
// ������� 76/1055�� ���� 7.20%�� rank�Ǿ���.

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

const int g_mod = 1000000007;
vector<long long> g_tree;
vector<long long> g_nums;

long long makeTree(int node, int start, int end)
{
	int mid;
	if (start == end) g_tree[node] = g_nums[start]; // leaf node
	else {
		mid = (start + end) / 2;
		g_tree[node] = (makeTree(2 * node, start, mid) * makeTree(2 * node + 1, mid + 1, end)) % g_mod;
	}
	return g_tree[node];
}

long long mul(int node, int start, int end, int left, int right)
{
	int mid;
	if (left > end || right < start) return 1; // L-R not match with the node
	else if (left <= start && end <= right) return g_tree[node]; // L-R match totaly with the node
	else { // L-R match partialy with the node
		mid = (start + end) / 2;		
		return (mul(2 * node, start, mid, left, right) * mul(2 * node + 1, mid + 1, end, left, right)) % g_mod;
	}
}

long long update(int node, int start, int end, int index)
{
	int mid;		
	if (start <= index && index <= end) { // index�� �ش��ϴ� node�� �ٽ� ���Ѵ�
		if (start == end) g_tree[node] = g_nums[start];
		else {
			mid = (start + end) / 2;
			g_tree[node] = (update(2 * node, start, mid, index) * update(2 * node + 1, mid + 1, end, index)) % g_mod;
		}
	}
	return g_tree[node];
}

int main()
{
	FAST;

	int n, m, k, a, b, c;
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
		cin >> a >> b >> c;
		if (a == 1) { // update			
			g_nums[b] = c;
			update(1, 1, n, b);			
		}
		else if (a == 2) { // multiply						
			cout << mul(1, 1, n, b, c) << "\n";
		}
	}
}