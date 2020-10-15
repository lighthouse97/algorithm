// 12899.cpp
// ������ ����
// ������ ���� ���� �������� �ʾƼ� Ǯ�̸� ������ �ܿ� �����ߴ�.
// �Դٰ� ������ �� �� ������ ���� �ִµ�, T�� 2 �� ��
// X�� X���ŷ� �Է��� ���� �ƴ϶� X��°�� ���� ���̴�.
// �������� �и��� ������ �ִµ� �װ� �����ϰ� �����ؼ� �� ������ ��ư� �������.
// ���̵��� �߰��� X�� �ִ밪�� 2�鸸 ��ŭ ���׸�Ʈ Ʈ���� �����,
// �߰��� ������ �ش� ��忡 1�� �����ش�.
// �����ϴ� ������ �ش� ��忡 1�� ���ش�.
// �˻��� �˻��ҷ��� ���� child ����� ���ʰ����� ���ų� ������ �������� ����
// �ݴ�� ũ�� ���������� ����. -> �̰� �����ϴµ� ���� �ɷȴ�.
// �ſ� ����� �����ε�, ���׸�Ʈ Ʈ���� �Ϻ��� �����ϰ� �� ���ư� ���� ������ �����ؾ� �Ѵ�.
// -> �������� query�ϰ� -1�� �ش� ���� ������Ʈ �� ��, �ش� ���� query�� ���ϰ��ε� �̰��� �Է¹��� x��° ���� ����
//    �����ϴ� �ٶ��� Ʋ�ȴµ� �̰� ã�µ� ���� ���� �ɷȴ�!
// --> ����Ʈ���� �� ���� Ǯ ���� �ִٴµ� �̰� ���߿� ���� �˾ƺ��� �ڴ�!!!
// ���ѽð� 2�� �� 1184ms(18,372KB)�� �ҿ�Ǿ���.
// ������� 71/108�� ���� 65.74%�� rank�Ǿ���.

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

vector<int> g_tree;
const int MAX_NUM = 2000000;

void update(int node, int start, int end, int index, int diff)
{
	int mid;
	if (index < start || end < index) return;
	if (start == end) g_tree[node] += diff;
	else {
		mid = (start + end) / 2;
		update(2 * node, start, mid, index, diff);
		update(2 * node + 1, mid + 1, end, index, diff);
		g_tree[node] = g_tree[2 * node] + g_tree[2 * node + 1];
	}
}

int query(int node, int start, int end, int nth)
{
	int mid;
	if (start == end) return start;
	mid = (start + end) / 2;
	if (nth <= g_tree[2 * node])
		return query(2 * node, start, mid, nth);
	else
		return query(2 * node + 1, mid + 1, end, nth - g_tree[2 * node]);
}

int main()
{
	FAST;
	int n, t, x, pos;
	int h, treeSize;

	h = (int)ceil(log2(MAX_NUM));
	treeSize = 1 << (h + 1);
	g_tree.resize(treeSize, 0);
	
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> t >> x;
		if (t == 1) {
			update(1, 1, MAX_NUM, x, 1);
		}
		else if (t == 2) {
			pos = query(1, 1, MAX_NUM, x);
			cout << pos << "\n";
			update(1, 1, MAX_NUM, pos, -1); // x��° ���� ���� �ƴ� �ش� �� �� ��ü�� ������Ʈ �ؾ� �Ѵ�! 
		}
	}
}