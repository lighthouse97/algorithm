// 1395
// 스위치
// 이 문제는 아무리 봐도 명백히 segment tree with lazy propagation으로 풀어야 한다.
// fenwick tree로 풀어볼려고 했어나 이 문제는 펜윅으로 푸는 문제는 아니다!!
// 특정 노드에서 switch 연산이 일어나면 그 노드의 값은 0인 노드의 갯수이다. 즉 g_tree[node] = cnt - g_tree[node] 이다.
// 왜? 0->1로 1->0으로 바뀌기 때문에...
// switch 연산이 일어나면 자식 노드에 lazy 업데이트를 하는데 기존 lazy값에 ^1 해주면 toggle되어
// 다음번에 switch 연산 여부가 결정된다.
// 구간내에 switch 가 켜진  갯수는 기존 처럼 구간 합으로 구하는데 해당 노드에서 lazy 업데이트 하는 부분만
// 추가해 주면 된다.
// Olympiad > USA Computing Olympiad > 2008-2009 Season > USACO November 2008 Contest > Gold 3번
// 제한시간 1초 중 88ms(4,048KB)가 소요되었다.
// 맞은사람 120/797로 상위 15.05%에 rank되었다.

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
	// 현재 node에 lazy값이 있는 경우 즉각 sum에 반영하고 아래로 전파한다.
	if (g_tree[node].lazy != 0) {		
		g_tree[node].val = (cnt - g_tree[node].val);
		if (start < end) {
			g_tree[2 * node].lazy ^= 1; // 왼쪽 child에 lazy 반영
			g_tree[2 * node + 1].lazy ^= 1; // 오른쪽 child에 lazy 반영
		}
	}
	g_tree[node].lazy = 0; // 다음에 재활용 못하도록 초기화

	if (left > end || right < start) return; // 업데이트 구간이 벗어남
	else if (left <= start && end <= right) { // 업데이트 구간이 일치함		
		g_tree[node].val = (cnt - g_tree[node].val);
		if (start < end) {
			g_tree[2 * node].lazy ^= 1; // 왼쪽 child에 lazy 반영
			g_tree[2 * node + 1].lazy ^= 1; // 오른쪽 child에 lazy 반영
		}
		return;
	}
	else { // 업데이트 구간이 일부만 걸쳐짐
		mid = (start + end) / 2;
		lazy_update(2 * node, start, mid, left, right);
		lazy_update(2 * node + 1, mid + 1, end, left, right);
		// child node에서 업데이트 되었을 경우 parent node에 그것을 반영한다.
		g_tree[node].val = g_tree[2 * node].val + g_tree[2 * node + 1].val;
	}
}

int lazy_sum(int node, int start, int end, int left, int right)
{
	int cnt = (end - start + 1), mid;
	// 현재 node에 lazy값이 있는 경우 즉각 sum에 반영하고 아래로 전파한다.
	if (g_tree[node].lazy != 0) {
		g_tree[node].val = (cnt - g_tree[node].val);
		if (start < end) {
			g_tree[2 * node].lazy ^= 1; // 왼쪽 child에 반영
			g_tree[2 * node + 1].lazy ^= 1; // 오른쪽 child에 반영
		}
	}
	g_tree[node].lazy = 0; // 다음에 재활용 못하도록 초기화

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