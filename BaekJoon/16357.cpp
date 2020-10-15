// 16357.cpp
// Circuits
// ����� �� ������ Ǯ��� �ȴ�.
// �⺻������ Segment Tree with lazy propagation�� ����ϴ� ���� �´µ�
// ������ 2���� ������ ���� ���� ������ ������ ������ ���������̴�.
// ������ Ǯ�����ؼ� ���� Ǭ ���� ��ĥ�� ���� �ܿ� �����ؼ� Ǯ�� �����
// ������ �����Ͽ���.(����Ǯ��_16357.pptx)
// �� �� Ǯ���!!
// �ܿ� �¾Ҵ�!
// ICPC > Regionals > Asia Pacific > Korea > Asia Regional - Seoul 2018 A��
// ���ѽð� 1�� �� 176ms(8,452KB)�� �ҿ�Ǿ���.
// ������� 11/80�� ���� 13.75%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
#include <cmath> // pow, sqrt, fabs, ceil, log2
#include <vector>
#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <functional> // less, greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct rect {
	int y1, y2;
	rect() {}
	rect(int y1, int y2) : y1(y1), y2(y2) {}
	bool operator < (const rect& comp) const
	{
		return y1 < comp.y1;
	}
};

struct node {
	int val;
	int lazy;
	node() {}
	node(int v, int l) : val(v), lazy(l) {}
};

vector<rect> g_rect; // �簢�� �迭, n
vector<int> g_yaxis; // y��ǥ �迭, n*2
vector<int> g_count; // y��ǥ���� ������ �簢�� ���� �迭, n*2
vector<node> g_tree; // segment tree with lazy propagation
int g_maxval = 0;

void lazy_update(int node, int start, int end, int left, int right)
{
	int mid;
	// ���� node�� lazy���� �ִ� ��� �ﰢ sum�� �ݿ��ϰ� �Ʒ��� �����Ѵ�.
	if (g_tree[node].lazy) {
		g_tree[node].val += g_tree[node].lazy;
		if (start < end) {
			g_tree[2 * node].lazy += g_tree[node].lazy;
			g_tree[2 * node + 1].lazy += g_tree[node].lazy;
		}
	}
	g_tree[node].lazy = 0;

	if (left > end || right < start) return; // ������Ʈ ������ ���
	else if (left <= start && end <= right) { // ������Ʈ ������ ��ġ��		
		g_tree[node].val++;
		if (start < end) {
			g_tree[2 * node].lazy++; // ���� child�� lazy �ݿ�
			g_tree[2 * node + 1].lazy++; // ������ child�� lazy �ݿ�
		}
		return;
	}
	else { // ������Ʈ ������ �Ϻθ� ������
		mid = (start + end) / 2;
		lazy_update(2 * node, start, mid, left, right);
		lazy_update(2 * node + 1, mid + 1, end, left, right);
		// child node���� ������Ʈ �Ǿ��� ��� ������ ���� max���� parent�� �ݿ��Ѵ�.
		g_tree[node].val = max(g_tree[2 * node].val, g_tree[2 * node + 1].val);
	}
}

int lazy_query(int node, int start, int end, int left, int right)
{
	int mid;
	// ���� node�� lazy���� �ִ� ��� �ﰢ sum�� �ݿ��ϰ� �Ʒ��� �����Ѵ�.
	if (g_tree[node].lazy) {
		g_tree[node].val += g_tree[node].lazy;
		if (start < end) {
			g_tree[2 * node].lazy += g_tree[node].lazy;
			g_tree[2 * node + 1].lazy += g_tree[node].lazy;
		}
	}
	g_tree[node].lazy = 0;
	
	if (left > end || right < start) return 0;
	else if (left <= start && end <= right) return g_tree[node].val;
	else {
		mid = (start + end) / 2;
		// ���� ����� ������ ������ ����� ���� �� ū ���� ����
		return max(lazy_query(2 * node, start, mid, left, right), lazy_query(2 * node + 1, mid + 1, end, left, right));
	}
}

int main()
{
	FAST;
	int n, x1, y1, x2, y2;
	int h, treeSize;
	cin >> n;
	g_rect.resize(n + 1, { 0, 0 });
	g_yaxis.resize(n * 2 + 1, 0);	
	
	int cnt = 0, len;
	for (int i = 1; i <= n; i++) {
		cin >> x1 >> y1 >> x2 >> y2;
		g_rect[i] = { y1, y2 };
		g_yaxis[++cnt] = y1;
		g_yaxis[++cnt] = y2;
	}
	sort(g_rect.begin() + 1, g_rect.end()); // �簢�� �������� ����
	sort(g_yaxis.begin() + 1, g_yaxis.end()); // y��ǥ �������� ����
	len = unique(g_yaxis.begin() + 1, g_yaxis.end()) - g_yaxis.begin(); // y ��ǥ�� �������� �ߺ��� �� ����		
	g_yaxis.resize(len);
	g_count.resize(len + 1, 0);
	h = (int)ceil(log2(len - 1));
	treeSize = 1 << (h + 1);
	g_tree.resize(treeSize, { 0, 0 });
	int loc;
	// Ư�� y��ǥ���� ������ �簢���� �� ������ ���ؼ� g_count �迭�� ����.
	for (int i = 1; i <= n; i++) {
		loc = lower_bound(g_yaxis.begin() + 1, g_yaxis.end(), g_rect[i].y2) - g_yaxis.begin();
		g_count[loc]++;
		loc = lower_bound(g_yaxis.begin() + 1, g_yaxis.end(), g_rect[i].y1) - g_yaxis.begin();
		g_count[loc + 1]--;
	}
	// ���� ���� ��� �����ؾ� ����� �� ī��Ʈ ���� ���´�!!!
	for (int i = 1; i < len + 1; i++)
		g_count[i] += g_count[i - 1];

	// �� ���ϱ�
	int reccnt = 1; // �簢�� ��ȣ, 1���� ����.
	int ycnt = len - 1; // y��ǥ�� ����
	int left, right;
	for (int i = 1; i <= ycnt; i++) { // ��� y��ǥ�� ���ؼ� Ž��
		g_maxval = max(g_maxval, g_count[i] + lazy_query(1, 1, ycnt, 1, i - 1));		
		while (reccnt <= n && g_yaxis[i] == g_rect[reccnt].y1) { // if�� �ƴϴ�. reccnt++ ���Ŀ� �� ���ǿ� �´� ��찡 �ִ�.
			left = lower_bound(g_yaxis.begin() + 1, g_yaxis.end(), g_rect[reccnt].y2) - g_yaxis.begin();
			right = lower_bound(g_yaxis.begin() + 1, g_yaxis.end(), g_rect[reccnt].y1) - g_yaxis.begin();
			lazy_update(1, 1, ycnt, left, right); // segment tree�� ���� �簢�� �߰�
			reccnt++;
		}
	}
	cout << g_maxval << "\n";
}
