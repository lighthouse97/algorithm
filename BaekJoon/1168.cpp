// 1168.cpp
// 요세푸스 문제 2
// 수시로 업데이트 하면서 k번째 수를 찾는 문제인데, Segment Tree로 풀 수 있다.
// 풀기는 풀었는데 문제 푸는데 시간이 너무 많이 걸렸다...
// 제한시간 0.15초 중 44ms(3,452KB)가 소요되었다.
// 맞은사람 101/281로 상위 35.94%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
//#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int N, K;
vector<int> S_TREE;

void init_st(int node, int start, int end)
{
	int m;
	if (start == end) {
		S_TREE[node] = 1;
		return;
	}
	m = (start + end) >> 1;
	init_st(node * 2, start, m);
	init_st(node * 2 + 1, m + 1, end);
	S_TREE[node] = S_TREE[node * 2] + S_TREE[node * 2 + 1];
}

void update_st(int node, int start, int end, int loc, int diff)
{
	if (loc < start || end < loc) return;
	S_TREE[node] += diff;
	if (start != end) {
		int m = (start + end) >> 1;
		update_st(node * 2, start, m, loc, diff);
		update_st(node * 2 + 1, m + 1, end, loc, diff);
	}	
}

int query_sum(int node, int start, int end, int left, int right)
{
	if (right < start || end < left) return 0;
	if (left <= start && end <= right) return S_TREE[node];
	int m = (start + end) >> 1;
	return query_sum(node * 2, start, m, left, right) + query_sum(node * 2 + 1, m + 1, end, left, right);
}

int query_kth(int node, int start, int end, int k)
{
	if (start == end) return start;
	int m = (start + end) >> 1;
	int lval = S_TREE[node * 2];
	if (k <= lval) return query_kth(node * 2, start, m, k);
	else return query_kth(node * 2 + 1, m + 1, end, k - lval);
}

int solve(int prev, int k)
{
	int k_sum = query_sum(1, 1, N, 1, prev) + k;
	int all_sum = query_sum(1, 1, N, 1, N);
	int k_temp = k_sum % all_sum;
	int kth = (k_temp != 0) ? k_temp : all_sum;
	int answer = query_kth(1, 1, N, kth);
	update_st(1, 1, N, answer, -1);
	return answer;
}

int main()
{
	FAST;
	
	cin >> N >> K;
	int h, tree_size;
	vector<int> result(N, 0);
	h = (int)ceil(log2(N));
	tree_size = 2 * (1 << h);
	S_TREE.resize(tree_size, 0);

	init_st(1, 1, N);
	int prev = 0;
	for (int i = 0; i < N; i++) {
		prev = solve(prev, K);
		result[i] = prev;
	}		
	cout << "<";
	for (int i = 0; i < N; i++) {
		cout << result[i];
		if (i < N - 1) cout << ", ";
		else cout << ">" << "\n";		
	}	
}