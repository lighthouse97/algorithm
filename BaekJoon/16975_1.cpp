// 16975_1.cpp
// 수열과 쿼리 21
// 앞서 16975를 세그먼트 트리만 사용하고 lazy propagation을 사용하지 않고
// 구현했다면 이번에는 16975를 세그먼트 트리에서 lazy propagation을 사용해서
// 구현한다. 특히 구간 업데이트 후에 업데이트 된 수열에서 하나의 숫자만 출력하는 문제이면
// 굳이 lazy propagation을 구현하지 않고도 구현할 수 있지만 구간 업데이트 후에
// 구간 합을 구하는 문제이면 lazy propagation을 이용해서 구현하는 것이 효율적이다.
// 이 문제에 한해서는 lazy propagation으로 푸는 것이 시간이 더 많이 걸렸다!!!(80ms -> 100ms)
// 제한시간 2초 중 100ms(6,884KB)가 소요되었다.
// 맞은사람 103/165로 상위 62.42%에 rank되었다.

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
	// 현재 node에 lazy값이 있는 경우 즉각 sum에 반영하고 아래로 전파한다.
	if (g_tree[node].lazy != 0) {
		g_tree[node].sum += range * g_tree[node].lazy; // sum에 반영
		if (start < end) {
			g_tree[2 * node].lazy += g_tree[node].lazy; // 왼쪽 child에 lazy 반영
			g_tree[2 * node + 1].lazy += g_tree[node].lazy; // 오른쪽 child에 lazy 반영
		}
	}
	g_tree[node].lazy = 0; // 다음에 재활용 못하도록 초기화

	if (left > end || right < start) return; // 업데이트 구간이 벗어남
	else if (left <= start && end <= right) { // 업데이트 구간이 일치함
		g_tree[node].sum += range * diff;
		if (start < end) {
			g_tree[2 * node].lazy += diff; // 왼쪽 child에 lazy 반영
			g_tree[2 * node + 1].lazy += diff; // 오른쪽 child에 lazy 반영
		}
		return;
	}
	else { // 업데이트 구간이 일부만 걸쳐짐
		mid = (start + end) / 2;
		lazy_update(2 * node, start, mid, left, right, diff);
		lazy_update(2 * node + 1, mid + 1, end, left, right, diff);
		// child node에서 업데이트 되었을 경우 parent node에 그것을 반영한다.
		g_tree[node].sum = g_tree[2 * node].sum + g_tree[2 * node + 1].sum;
	}
}

long long lazy_sum(int node, int start, int end, int left, int right)
{
	int range = end - start + 1, mid;
	// 현재 node에 lazy값이 있는 경우 즉각 sum에 반영하고 아래로 전파한다.
	if (g_tree[node].lazy != 0) {
		g_tree[node].sum += range * g_tree[node].lazy; // sum에 반영
		if (start < end) {
			g_tree[2 * node].lazy += g_tree[node].lazy; // 왼쪽 child에 반영
			g_tree[2 * node + 1].lazy += g_tree[node].lazy; // 오른쪽 child에 반영
		}
	}
	g_tree[node].lazy = 0; // 다음에 재활용 못하도록 초기화

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
