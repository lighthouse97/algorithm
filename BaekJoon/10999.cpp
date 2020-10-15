// 10999.cpp
// 구간 합 구하기 2
// 세그먼트 트리에서 lazy propagation을 이용하는 문제이다.
// lazy propagation 응용도 아니고 그 자체이다.
// 구간의 값이 수시로 바뀌는 문제면 100% lazy propagation 으로 보면 된다!
// 16975_1에서 한번 풀었기 때문에 이를 그대로 응용하기로 한다!
// 제한시간 2초 중 152ms(42,588KB)가 소요되었다.
// 맞은사람 79/1414로 상위 5.58%에 rank되었다.

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

	int n, m, k, a, b, c, d;
	int h, treeSize;
	long long result;

	cin >> n >> m >> k;
	h = (int)ceil(log2(n));
	treeSize = 1 << (h + 1);
	g_tree.resize(treeSize, { 0, 0 });
	g_nums.resize(n + 1, 0);
	for (int i = 1; i <= n; i++)
		cin >> g_nums[i];
	makeTree(1, 1, n);

	for (int i = 0; i < m + k; i++) {
		cin >> a;
		if (a == 1) {
			cin >> b >> c >> d;
			lazy_update(1, 1, n, b, c, d);
		}
		else if (a == 2) {
			cin >> b >> c;
			result = lazy_sum(1, 1, n, b, c);
			cout << result << "\n";
		}
	}
}