// 16978_1.cpp
// 수열과 쿼리 22
// 이 문제는 PST(Persistent Segment Tree)의 문제이기도 하지만 Offline Query의 문제이기도 하다.
// 즉 Segment Tree + Offline Query로도 풀 수가 있다.
// Query type 1과 2를 따로 모아놓고 Query type 2는 k값에 따라 오름차순 정렬한다.
// k 값이 증가할 때마다 Query 1을 수행하고 같은 k에서 Query 2를 모아서 처리한다.
// 이후 저장된 Query 2의 결과를 한꺼번에 출력하면 된다.
// 주의할 점은 1) Query2를 sort할 때 k가 같으면 입력순으로 정렬되어져야 한다는 것과
// 2) 이건 매우 중요한데, k가 단계별로 하나씩 증가하지 않고 몇개씩 건너뛸 수도 있다는 점이다!
//    여기에 맞게 update 부분을 잘 생각해서 작성해야 한다.
// 확실히 PST보다 segment tree 하나만 쓰고 Offline Query를 사용하는 것이 훨씬 더 빨랐다!!
// 수행시간이 무려 348ms(72,876KB) -> 76ms(7,608KB)로 줄어들었다.
// 제한시간 1초 중 76ms(7,608KB)가 소요되었다.
// 맞은사람 54/282로 상위 19.14%에 rank되었다.

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

typedef long long ll;

struct qtype1 { // query type 1
	int i, v;
	qtype1() : i(0), v(0) {}
	qtype1(int i, int v) : i(i), v(v) {}
};

struct qtype2 { // query type 2
	int num, k, i, j;
	ll result;
	qtype2() : num(0), k(0), i(0), j(0), result(0) {}
	qtype2(int n, int k, int i, int j) : num(n), k(k), i(i), j(j), result(0) {}
};

vector<int> ARR; // number 배열
vector<ll> S_TREE; // 구간합에 대한 segment tree

ll initialise(int node, int start, int end)
{
	int m;
	if (start == end) S_TREE[node] = ARR[start];
	else {
		m = (start + end) >> 1;
		S_TREE[node] = initialise(node * 2, start, m) + initialise(node * 2 + 1, m + 1, end);
	}
	return S_TREE[node];
}

void update_val(int node, int start, int end, int loc, int diff)
{
	int m;
	if (loc < start || end < loc) return;
	S_TREE[node] += diff;
	if (start != end) {
		m = (start + end) >> 1;
		update_val(node * 2, start, m, loc, diff);
		update_val(node * 2 + 1, m + 1, end, loc, diff);
	}
}

ll query(int node, int start, int end, int left, int right)
{
	int m;
	if (right < start || end < left) return 0;
	if (left <= start && end <= right) return S_TREE[node];
	else {
		m = (start + end) >> 1;
		return query(node * 2, start, m, left, right)	+ query(node * 2 + 1, m + 1, end, left, right);
	}
}

int main()
{
	FAST;

	int N, M;
	vector<qtype1> query1;
	vector<qtype2> query2;
	
	cin >> N;
	ARR.resize(N + 1, 0);
	int h = (int)ceil(log2(N));
	int tree_size = 2 * (1 << h);
	S_TREE.resize(tree_size, 0);
	for (int i = 1; i < N + 1; i++) cin >> ARR[i];
	initialise(1, 1, N); // segment tree 초기화

	cin >> M;
	query1.reserve(M); query1.push_back({ 0, 0 }); // 1부터 시작하기 위함
	query2.reserve(M);
	int type, v, k, i, j;
	int cnt = 0;
	for (int index = 0; index < M; index++) { // query를 모두 입력받는다.
		cin >> type;
		if (type == 1) {
			cin >> i >> v;
			query1.push_back({ i, v });
		}
		else {
			cin >> k >> i >> j;
			query2.push_back({ cnt++, k, i, j });
		}
	}
	int sort_type = 0;
	auto cmp = [&](const qtype2& a, const qtype2& b) { 
		if (sort_type == 0) {
			if (a.k == b.k) return a.num < b.num;
			return a.k < b.k;
		}
		else return a.num < b.num;		
	};
	sort(query2.begin(), query2.end(), cmp); // k 오름차순 정리한다.
	int prev_k = 0;
	for (qtype2& x : query2) {
		if (prev_k < x.k) { // query2의 k가 하나씩 증가하지 않고 몇개씩 건너뛸 수 있다!!!
			for (int ki = prev_k + 1; ki <= x.k; ki++) {
				int loc = query1[ki].i, val = query1[ki].v;				
				update_val(1, 1, N, loc, val - ARR[loc]);
				ARR[loc] = val;
			}			
		}
		x.result = query(1, 1, N, x.i, x.j);
		prev_k = x.k;
	}
	sort_type = 1;
	sort(query2.begin(), query2.end(), cmp); // 원래 입력된 순서로 다시 정렬한다.
	for (qtype2& x : query2) cout << x.result << "\n";
}