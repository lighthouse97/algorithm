// 2820.cpp
// �ڵ��� ����
// 16975(������ ���� 21)�� ���� �����̴�.
// �� �� ������ ���׸�Ʈ Ʈ���� Ǯ���� ���Ϸ��� ������ �������� �Ǿ�� �Ѵ�.
// �׷��� �־��� ������ �������� ���谡 �������� �Ǿ����� �ʱ� ������ DFS �һ��Ͽ�
// �������� ��ȣ�� �ű� �ڷᱸ���� �ϳ� �� ����� �̸� ���� ���� ��ȣ�� ���� ��Ų��.
// ���� ����� ������, ���� ��ȣ�� ���������� ���ε� ��ȣ�� �ٲپ� ���Ŀ��� ���׸�Ʈ Ʈ��
// ������ Ǯ�� �ȴ�.
// ���׸�Ʈ Ʈ���� �����հ� lazy propagation�� �̿��ص� ������(16975_1), �̷��� ���� �ʰ�
// 16975���� Ǯ���� ������� Ǯ��Ҵ�.
// Contest > Croatian Open Competition in Informatics > COCI 2011/2012 > Contest #3 5��
// ���ѽð� 1�� �� 468ms(40,252KB)�� �ҿ�Ǿ���.
// ������� 35/246�� ���� 14.22%�� rank�Ǿ���.

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
vector<long long> g_tree; // ���׸�Ʈ Ʈ��
vector<long long> g_pays; // ������ ������ ���� ����
vector<vector<int>> g_graph; // ���� ���� �׷���
vector<range> g_remap; // ���׸�Ʈ Ʈ�� ó�������� remapping �� ��
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