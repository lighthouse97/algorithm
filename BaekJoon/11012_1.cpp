// 11012_1.cpp
// Egg
// 바로 전에 PST로 풀었는데 이 문제는 Merge Sort Tree로도 풀 수 있다고 해서
// Merge Sort Tree로 한번 풀어보았다.
// x축 데이터가 MST의 노드의 범위가 되고 노드의 값이 x축에 해당되는 y축의 값들이 정렬된 상태로 저장된다.
// 상위 level로 올라갈수록 노드의 값들이 합쳐지면서 정렬이 되는 관계로 merge sort과 유사한 형태이다.
// MST 초기화할때 leaf node의 값을 만들어주기 위해 입력값에 처리를 해주어야 한다. x축 오름차순으로 정렬하고 같은 x값에는
// y축 값들이 배열로 들어가는데 정렬된 상태로 들어간다.
// query는 x축 범위에 해당되는 노드를 MST에서 찾고 각 노드에서 y축 범위에 맞는 데이터의 갯수를 합치면 된다.
// 각 노드의 y축 데이터가 정렬된 상태이기 때문에 y축 범위의 시작, 끝의 인덱스를 y축 데이터로부터 얻어서 이 인덱스의 차로 부터
// 범위내 데이터의 갯수를 알 수 있다.
// 수행 시간은 1168ms(12,488KB) -> 940ms(5,076KB) 으로 줄었다.
// 맞은사람 113/167로 상위 67.66%에 rank되었다.

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

struct point { // 입력좌표
	int x, y;
	point() : x(0), y(0) {}
	point(int x, int y) : x(x), y(y) {}
};

int N, M;
vector<point> ARR; // 입력 데이터
vector<int> DATA_X; // x축 데이터
vector<int> DATA_Y; // Y축 데이터
vector<vector<int>> P_ARR; // ARR 가공(MST의 leaf)
vector<vector<int>> S_TREE; // segment tree

// merge sort와 유사
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
	P_ARR.reserve(N + 1); // 공간 확보
	P_ARR.push_back(vector<int>()); // 1부터 시작
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