// 11505.cpp
// 구간 곱 구하기
// 세그먼트 트리를 이용한 구간 합이 아니라 구간 곱이다.
// 방식은 똑같을 것으로 보이고 단 합이아니고 곱인 점만 다르다.
// --> 똑같지는 않고 구간 곱할 때 구간에 없는 노드는 0이 아닌 1을 리턴해야 하고 
//     update 함수는 해당 노드만 다시 곱해주어야 한다.
// 그리고 곱하면 그 수가 커지므로 곱한 결과에 1,000,000,007의 나머지를 사용한다.
// 제한시간 1초 중 140ms(2,6200KB)가 소요되었다.
// 맞은사람 76/1055로 상위 7.20%에 rank되었다.

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
	if (start <= index && index <= end) { // index에 해당하는 node만 다시 곱한다
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