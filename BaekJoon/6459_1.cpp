// 6459_1.cpp
// 히스토그램에서 가장 큰 직사각형
// Contest > University of Ulm Local Contest > University of Ulm Local Contest 2003 H번
// 스택을 이용해서 풀었지만 이 문제의 취지가 분할 정복과 세그먼트 트리를 이용해서
// 푸는 것이라 취지에 맞게 분할 정복과 세그먼트 트리를 이용해서 풀어 보았다.
// 결과는 스택을 이용해서 푸는 것이 비해 실행 시간이 더 많이 걸린다.
// 스택을 이용할 경우 : 36ms(2,497KB)
// 분할 정복, 세그먼트 트리 이용할 경우 : 76ms(6,444KB)

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
			if (H[lc] <= H[rc]) ret = lc; // 양쪽에 값이 있을 경우 작은 값을 선택
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
	maxarea = max(maxarea, area); // 현재 노드에서 면적

	int loc;
	loc = (mid == left) ? left : mid - 1;
	area = maxArea(left, loc);
	maxarea = max(maxarea, area); // 왼쪽 자식 노드로부터 면적
	loc = (mid == right) ? right : mid + 1;
	area = maxArea(loc, right);
	maxarea = max(maxarea, area); // 오른쪽 자식 노드로부터 면적, 가장 큰 값을 고른다.

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