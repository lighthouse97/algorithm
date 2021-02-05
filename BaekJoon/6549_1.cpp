// 6459_1.cpp
// ������׷����� ���� ū ���簢��
// Contest > University of Ulm Local Contest > University of Ulm Local Contest 2003 H��
// ������ �̿��ؼ� Ǯ������ �� ������ ������ ���� ������ ���׸�Ʈ Ʈ���� �̿��ؼ�
// Ǫ�� ���̶� ������ �°� ���� ������ ���׸�Ʈ Ʈ���� �̿��ؼ� Ǯ�� ���Ҵ�.
// ����� ������ �̿��ؼ� Ǫ�� ���� ���� ���� �ð��� �� ���� �ɸ���.
// ������ �̿��� ��� : 36ms(2,497KB)
// ���� ����, ���׸�Ʈ Ʈ�� �̿��� ��� : 76ms(6,444KB)

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;
typedef long long ll;

int N;
vector<int> S_TREE; // segment tree
vector<int> H; // height array

int initTree(int node, int start, int end)
{
	int mid, left, right;
	if (start == end) S_TREE[node] = start;
	else {
		mid = (start + end) / 2;
		left = initTree(node * 2, start, mid);
		right = initTree(node * 2 + 1, mid + 1, end);
		if (H[left] <= H[right]) S_TREE[node] = left;
		else S_TREE[node] = right;
	}
	return S_TREE[node];
}

int query(int node, int start, int end, int left, int right)
{
	int mid, lc, rc, ret;
	if (left > end || right < start) return -1;
	else if (left <= start && end <= right) return S_TREE[node];
	else {
		mid = (start + end) / 2;
		lc = query(node * 2, start, mid, left, right);
		rc = query(node * 2 + 1, mid + 1, end, left, right);
		if (lc == -1) ret = rc;
		else if (rc == -1) ret = lc;
		else {
			if (H[lc] <= H[rc]) ret = lc; // ���ʿ� ���� ���� ��� ���� ���� ����
			else ret = rc;
		}
	}
	return ret;
}

ll maxArea(int left, int right)
{
	int mid;
	ll maxarea = 0, area;
	if (left == right) return 1LL * H[left] * 1;
	mid = query(1, 1, N, left, right);
	area = 1LL * H[mid] * (right - left + 1);
	maxarea = max(maxarea, area); // ���� ��忡�� ����

	int loc;
	loc = (mid == left) ? left : mid - 1;
	area = maxArea(left, loc);
	maxarea = max(maxarea, area); // ���� �ڽ� ���κ��� ����
	loc = (mid == right) ? right : mid + 1;
	area = maxArea(loc, right);
	maxarea = max(maxarea, area); // ������ �ڽ� ���κ��� ����, ���� ū ���� ����.

	return maxarea;
}

void DoTest(int n)
{
	ll maxval;
	H.resize(n + 1, 0);
	for (int i = 1; i < n + 1; i++) cin >> H[i];
	int h = (int)ceil(log2(n));
	int treeSize = 2 * (1 << h);
	S_TREE.resize(treeSize, 0);

	initTree(1, 1, N);
	maxval = maxArea(1, N);
	cout << maxval << "\n";
	H.clear();
	S_TREE.clear();
}


int main() {
	FAST;

	while (1) {
		cin >> N;
		if (N == 0) break;
		DoTest(N);
	}
}