// 2820.cpp
// 자동차 공장
// 16975(수열과 쿼리 21)과 같은 문제이다.
// 단 이 문제를 세그먼트 트리로 풀려면 구하려는 구간이 연속으로 되어야 한다.
// 그러나 주어진 문제는 상하조직 관계가 연속으로 되어있지 않기 때문에 DFS 텀색하여
// 연속으로 번호를 매긴 자료구조를 하나 더 만들어 이를 기존 직원 번호와 매핑 시킨다.
// 이후 명령이 들어오면, 직원 번호를 순차적으로 매핑된 번호로 바꾸어 이후에는 세그먼트 트리
// 문제로 풀면 된다.
// 세그먼트 트리의 구간합과 lazy propagation을 이용해도 되지만(16975_1), 이렇게 하지 않고
// 16975에서 풀었던 방식으로 풀어보았다.
// Contest > Croatian Open Competition in Informatics > COCI 2011/2012 > Contest #3 5번
// 제한시간 1초 중 468ms(40,252KB)가 소요되었다.
// 맞은사람 35/246로 상위 14.22%에 rank되었다.

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

struct range {
	int start;
	int end;
	range() {}
	range(int s, int e) : start(s), end(e) {}
};

const long long MAXVAL = 999999999999;
vector<long long> g_tree; // 세그먼트 트리
vector<long long> g_pays; // 사장을 포함한 직원 월급
vector<vector<int>> g_graph; // 조직 관계 그래프
vector<range> g_remap; // 세그먼트 트리 처리용으로 remapping 한 것
int g_count = 0;

void dfs(int here)
{
	g_remap[here].start = ++g_count;
	for (int next : g_graph[here]) {
		if (!g_remap[next].start)
			dfs(next);
	}
	g_remap[here].end = g_count;
}

void update(int node, int start, int end, int left, int right, int diff)
{
	int mid;
	if (left > end || right < start) return;
	if (left <= start && end <= right) {
		if (g_tree[node] == MAXVAL) g_tree[node] = diff;
		else g_tree[node] += diff;
	}
	else {
		mid = (start + end) / 2;
		update(2 * node, start, mid, left, right, diff);
		update(2 * node + 1, mid + 1, end, left, right, diff);
	}
}

long long find(int node, int start, int end, int index)
{
	int mid;
	bool updated = false;
	long long result = MAXVAL, temp;
	if (start <= index && index <= end) {
		temp = g_tree[node];
		if (temp < MAXVAL) {
			if (!updated) result = temp;
			else result += temp;
			updated = true;
		}
		if (start < end) {
			mid = (start + end) / 2;
			temp = find(2 * node, start, mid, index);
			if (temp < MAXVAL) {
				if (!updated) result = temp;
				else result += temp;
				updated = true;
			}
			temp = find(2 * node + 1, mid + 1, end, index);
			if (temp < MAXVAL) {
				if (!updated) result = temp;
				else result += temp;
				updated = true;
			}
		}
	}
	return result;
}

int main()
{
	FAST;

	int n, m, a, x;
	char cmd;
	int h, treeSize;
	int t1, t2;
	long long result;

	cin >> n >> m;
	h = (int)ceil(log2(n));
	treeSize = 1 << (h + 1);
	g_tree.resize(treeSize, MAXVAL);
	g_pays.resize(n + 1, 0);
	g_graph.resize(n + 1);
	g_remap.resize(n + 1, { 0, 0 });

	for (int i = 1; i <= n; i++) {
		cin >> t1;
		g_pays[i] = t1;
		if (i > 1) {
			cin >> t2;
			g_graph[t2].push_back(i);
		}
	}
	dfs(1);

	// query
	for (int i = 0; i < m; i++) {
		cin >> cmd;
		if (cmd == 'p') {
			cin >> a >> x;
			if (g_remap[a].start == g_remap[a].end) continue;  // leaf node
			update(1, 1, n, g_remap[a].start + 1, g_remap[a].end, x);
		}
		else if (cmd == 'u') {
			cin >> a;
			result = find(1, 1, n, g_remap[a].start);
			if (result != MAXVAL) result += g_pays[a];
			else result = g_pays[a];
			cout << result << "\n";
		}
	}
}