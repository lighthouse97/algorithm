// 11012_1.cpp
// Egg
// �ٷ� ���� PST�� Ǯ���µ� �� ������ Merge Sort Tree�ε� Ǯ �� �ִٰ� �ؼ�
// Merge Sort Tree�� �ѹ� Ǯ��Ҵ�.
// x�� �����Ͱ� MST�� ����� ������ �ǰ� ����� ���� x�࿡ �ش�Ǵ� y���� ������ ���ĵ� ���·� ����ȴ�.
// ���� level�� �ö󰥼��� ����� ������ �������鼭 ������ �Ǵ� ����� merge sort�� ������ �����̴�.
// MST �ʱ�ȭ�Ҷ� leaf node�� ���� ������ֱ� ���� �Է°��� ó���� ���־�� �Ѵ�. x�� ������������ �����ϰ� ���� x������
// y�� ������ �迭�� ���µ� ���ĵ� ���·� ����.
// query�� x�� ������ �ش�Ǵ� ��带 MST���� ã�� �� ��忡�� y�� ������ �´� �������� ������ ��ġ�� �ȴ�.
// �� ����� y�� �����Ͱ� ���ĵ� �����̱� ������ y�� ������ ����, ���� �ε����� y�� �����ͷκ��� �� �� �ε����� ���� ����
// ������ �������� ������ �� �� �ִ�.
// ���� �ð��� 1168ms(12,488KB) -> 940ms(5,076KB) ���� �پ���.
// ������� 113/167�� ���� 67.66%�� rank�Ǿ���.

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
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct point { // �Է���ǥ
	int x, y;
	point() : x(0), y(0) {}
	point(int x, int y) : x(x), y(y) {}
};

int N, M;
vector<point> ARR; // �Է� ������
vector<int> DATA_X; // x�� ������
vector<int> DATA_Y; // Y�� ������
vector<vector<int>> P_ARR; // ARR ����(MST�� leaf)
vector<vector<int>> S_TREE; // segment tree

// merge sort�� ����
vector<int> merge_mst(const vector<int>& left, const vector<int>& right)
{
	vector<int> ret;
	int i = 0, j = 0;
	int leftLen = left.size(), rightLen = right.size();
	while (i < leftLen && j < rightLen) {
		if (left[i] <= right[j]) { ret.push_back(left[i]); i++; }
		else { ret.push_back(right[j]); j++; }
	}
	while (i < leftLen) { ret.push_back(left[i]); i++; }
	while (j < rightLen) { ret.push_back(right[j]); j++; }
	return ret;
}

vector<int> init_mst(int node, int start, int end)
{
	int m;
	vector<int> lval, rval;
	if (start == end) {
		S_TREE[node] = P_ARR[start];
		return S_TREE[node];
	}
	m = (start + end) >> 1;
	lval = init_mst(node * 2, start, m);
	rval = init_mst(node * 2 + 1, m + 1, end);
	return S_TREE[node] = merge_mst(lval, rval);
}

int count_arr(const vector<int>& vt, int s, int e)
{
	int res;
	int li = lower_bound(vt.begin(), vt.end(), s) - vt.begin();
	int ri = upper_bound(vt.begin(), vt.end(), e) - vt.begin() - 1;
	res = ri - li + 1;
	return res;
}

int query_mst(int node, int start, int end, int xs, int xe, int ys, int ye)
{
	int m;
	if (xe < start || end < xs) return 0;
	if (xs <= start && end <= xe) return count_arr(S_TREE[node], ys, ye);
	m = (start + end) >> 1;
	return query_mst(node * 2, start, m, xs, xe, ys, ye) +
				query_mst(node * 2 + 1, m + 1, end, xs, xe, ys, ye);
}

void DoTest()
{
	cin >> N >> M;
	ARR.resize(N + 1);
	DATA_X.resize(N + 1, 0);
	DATA_Y.resize(N + 1, 0);
	int x, y;
	for (int i = 1; i < N + 1; i++) {
		cin >> x >> y;
		ARR[i] = { x, y };
		DATA_X[i] = x;
		DATA_Y[i] = y;
	}
	sort(DATA_X.begin() + 1, DATA_X.end());
	sort(DATA_Y.begin() + 1, DATA_Y.end());
	DATA_X.erase(unique(DATA_X.begin() + 1, DATA_X.end()), DATA_X.end());
	DATA_Y.erase(unique(DATA_Y.begin() + 1, DATA_Y.end()), DATA_Y.end());
	auto cmp = [](const point & a, const point & b) {
		if (a.x == b.x)
			return a.y < b.y;
		return a.x < b.x;
	};
	sort(ARR.begin() + 1, ARR.end(), cmp);
	int prev_x = -1;
	P_ARR.reserve(N + 1); // ���� Ȯ��
	P_ARR.push_back(vector<int>()); // 1���� ����
	for (int i = 1; i < N + 1; i++) {
		if (prev_x != ARR[i].x) P_ARR.push_back(vector<int>());
		int yref = lower_bound(DATA_Y.begin() + 1, DATA_Y.end(), ARR[i].y) - DATA_Y.begin();
		P_ARR.back().push_back(yref);
		prev_x = ARR[i].x;
	}
	int h = (int)ceil(log2(P_ARR.size() - 1));
	int tree_size = 2 * (1 << h);
	S_TREE.resize(tree_size);
	init_mst(1, 1, (int)P_ARR.size() - 1);

	// QUERY
	int l, r, b, t;
	int xs, xe, ys, ye;
	int sum = 0;
	for (int i = 0; i < M; i++) {
		cin >> l >> r >> b >> t;
		xe = (upper_bound(DATA_X.begin() + 1, DATA_X.end(), r) - DATA_X.begin()) - 1;
		xs = (lower_bound(DATA_X.begin() + 1, DATA_X.end(), l) - DATA_X.begin());
		ye = (upper_bound(DATA_Y.begin() + 1, DATA_Y.end(), t) - DATA_Y.begin()) - 1;
		ys = (lower_bound(DATA_Y.begin() + 1, DATA_Y.end(), b) - DATA_Y.begin());
		sum += query_mst(1, 1, (int)P_ARR.size() - 1, xs, xe, ys, ye);
	}
	cout << sum << "\n";
	ARR.clear();
	DATA_X.clear();
	DATA_Y.clear();
	P_ARR.clear();
	S_TREE.clear();
}

int main()
{
	FAST;

	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
		DoTest();
}