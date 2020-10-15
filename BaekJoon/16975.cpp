// 16975.cpp
// ������ ���� 21
// ó�� ���� ������� �ð��ʰ��� �߻��Ѵ�. => ���� ���� ����� Ʋ�ȴ�!
// Ʈ�� ��带 MAX_VAL(1,000,000 * 100,000 ���� ū ��)���� �ʱ�ȭ �ϰ�
// ������Ʈ ������ ������ ���ԵǴ� Ʈ�� ��常 diff ������ ������Ʈ �Ѵ�.
// ���� ���� ���� ���� ����� �� ���׸�Ʈ Ʈ���� ��Ʈ���� ã�� ���ڰ� ���Ե� ��常 ���ʷ� Ž���ϸ鼭
// Ž���ϴ� Ʈ�� ��尡 �ʱ�ȭ ���� �ƴ� ��� diff������ ������Ʈ �� ����̸� leaf ������ diff���� ���
// �����ش�.(�� Ʈ�� ��帶�� diff���� ������ ����Ѵ�.)
// �̷��� ������ diff���� ������ ���� ���� ���� ���ϸ� ������Ʈ �� ���� ���ڰ��� �� �� �ִ�.
// ���� diff���� �ʱⰪ�̸� ���� ���ڰ� ������Ʈ ���� ���� ���̱� ������ ������ ���� ���� ���� ����Ѵ�.
// ����� ������ diff���� int ������ �Ѿ �� �����Ƿ� long lnng type���� ��´�.
// �׸��� lazy propagation�� ����ϸ� �� �� ���� �����ų �� �ִµ�, ���Ŀ� �н��ؼ� �����Ű���� ����.
// ���ѽð� 2�� �� 80ms(4,832KB)�� �ҿ�Ǿ���.
// ������� 62/163�� ���� 38.03%�� rank�Ǿ���.

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

const long long MAXVAL = 999999999999;
vector<long long> g_tree;
vector<long long> g_nums;

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
		if(start < end) {
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

	int n, m, a, b, c, d;
	int h, treeSize;
	long long result;

	cin >> n;
	h = (int)ceil(log2(n));
	treeSize = 1 << (h + 1);
	g_tree.resize(treeSize, MAXVAL);
	g_nums.resize(n + 1, 0);
	for (int i = 1; i <= n; i++)
		cin >> g_nums[i];

	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> a;
		if (a == 1) {
			cin >> b >> c >> d;
			update(1, 1, n, b, c, d);
		}
		else if (a == 2) {
			cin >> b;			
			result = find(1, 1, n, b);
			if (result != MAXVAL) result += g_nums[b];
			else result = g_nums[b];
			cout << result << "\n";
		}
	}
}