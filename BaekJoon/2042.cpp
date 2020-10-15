// 2042.cpp
// 구간 합 구하기
// 앞(11659)의 '구간 합 구하기 4'는 중간에 주어진 수의 배열의 값이 바뀌지 않아서
// 단순히 동적 계획법으로 풀면 제한 시간안에 다 풀 수가 있으나
// 이번 문제는 중간 중간에 주어진 수의 배열의 값이 계속 바뀌기 때문에 그때마다
// 동적계획법으로 전체 누적합을 계속 다시 계산해서 업데이트 하면 주어진 시간내에 문제를 풀 수가 없다.
// 따라서 본 문제는 세그먼트 트리를 이용해서 부분합을 계산해야 주어진 시간내에 문제를 풀 수 있다.
// 제한시간 2초 중 148ms(2,6200KB)가 소요되었다.
// 맞은사람 206/5118로 상위 4.02%에 rank되었다.

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
	if (index < start || end < index) return; // update와 상관없는 구간
	g_tree[node] += diff;
	if (start != end) { // leaf node가 아닌 경우
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