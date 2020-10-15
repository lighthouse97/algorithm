// 12844.cpp
// XOR
// segment tree with lazy propagation으로 푼다.
// 세그먼트 트리의 각 노드에 구간합이 아닌 구간 XOR 값을 저장해둔다.
// 임의의 구간에 k를 XOR할 때, 임의의 구간의 갯수가 짝수이면 노드에 0을 XOR하고
// 임의의 구간의 갯수가 홀수이면 노드에 k를 XOR하면 된다. (XOR의 속성상 그렇다!)
// a ~ b구간이라고만 했지 a < b인 것은 아니다! a > b 일수도 있다. 이거때문에 한번 틀렸다!
// University > 숭실대학교 > SCCC 2016 Summer Contest F번
// 제한시간 2초 중 540ms(12,064KB)가 소요되었다.
// 맞은사람 33/461로 상위 7.15%에 rank되었다.

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
	// 현재 node에 lazy값이 있는 경우 즉각 sum에 반영하고 아래로 전파한다.
	if (g_tree[node].lazy != 0) {
		g_tree[node].val ^= ((flag) ? g_tree[node].lazy : 0);
		if (start < end) {
			g_tree[2 * node].lazy ^= g_tree[node].lazy; // 왼쪽 child에 lazy 반영
			g_tree[2 * node + 1].lazy ^= g_tree[node].lazy; // 오른쪽 child에 lazy 반영
		}
	}
	g_tree[node].lazy = 0; // 다음에 재활용 못하도록 초기화

	if (left > end || right < start) return; // 업데이트 구간이 벗어남
	else if (left <= start && end <= right) { // 업데이트 구간이 일치함
		g_tree[node].val ^= ((flag) ? diff : 0);
		if (start < end) {
			g_tree[2 * node].lazy ^= diff; // 왼쪽 child에 lazy 반영
			g_tree[2 * node + 1].lazy ^= diff; // 오른쪽 child에 lazy 반영
		}
		return;
	}
	else { // 업데이트 구간이 일부만 걸쳐짐
		mid = (start + end) / 2;
		lazy_update(2 * node, start, mid, left, right, diff);
		lazy_update(2 * node + 1, mid + 1, end, left, right, diff);
		// child node에서 업데이트 되었을 경우 parent node에 그것을 반영한다.
		g_tree[node].val = g_tree[2 * node].val ^ g_tree[2 * node + 1].val;
	}
}

int lazy_xor(int node, int start, int end, int left, int right)
{
	int flag = (end - start + 1) % 2, mid;
	// 현재 node에 lazy값이 있는 경우 즉각 sum에 반영하고 아래로 전파한다.
	if (g_tree[node].lazy != 0) {
		g_tree[node].val ^= ((flag) ? g_tree[node].lazy : 0);
		if (start < end) {
			g_tree[2 * node].lazy ^= g_tree[node].lazy; // 왼쪽 child에 반영
			g_tree[2 * node + 1].lazy ^= g_tree[node].lazy; // 오른쪽 child에 반영
		}
	}
	g_tree[node].lazy = 0; // 다음에 재활용 못하도록 초기화

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