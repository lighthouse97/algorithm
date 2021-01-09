// 16978_1.cpp
// ������ ���� 22
// �� ������ PST(Persistent Segment Tree)�� �����̱⵵ ������ Offline Query�� �����̱⵵ �ϴ�.
// �� Segment Tree + Offline Query�ε� Ǯ ���� �ִ�.
// Query type 1�� 2�� ���� ��Ƴ��� Query type 2�� k���� ���� �������� �����Ѵ�.
// k ���� ������ ������ Query 1�� �����ϰ� ���� k���� Query 2�� ��Ƽ� ó���Ѵ�.
// ���� ����� Query 2�� ����� �Ѳ����� ����ϸ� �ȴ�.
// ������ ���� 1) Query2�� sort�� �� k�� ������ �Է¼����� ���ĵǾ����� �Ѵٴ� �Ͱ�
// 2) �̰� �ſ� �߿��ѵ�, k�� �ܰ躰�� �ϳ��� �������� �ʰ� ��� �ǳʶ� ���� �ִٴ� ���̴�!
//    ���⿡ �°� update �κ��� �� �����ؼ� �ۼ��ؾ� �Ѵ�.
// Ȯ���� PST���� segment tree �ϳ��� ���� Offline Query�� ����ϴ� ���� �ξ� �� ������!!
// ����ð��� ���� 348ms(72,876KB) -> 76ms(7,608KB)�� �پ�����.
// ���ѽð� 1�� �� 76ms(7,608KB)�� �ҿ�Ǿ���.
// ������� 54/282�� ���� 19.14%�� rank�Ǿ���.

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

vector<int> ARR; // number �迭
vector<ll> S_TREE; // �����տ� ���� segment tree

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
	initialise(1, 1, N); // segment tree �ʱ�ȭ

	cin >> M;
	query1.reserve(M); query1.push_back({ 0, 0 }); // 1���� �����ϱ� ����
	query2.reserve(M);
	int type, v, k, i, j;
	int cnt = 0;
	for (int index = 0; index < M; index++) { // query�� ��� �Է¹޴´�.
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
	sort(query2.begin(), query2.end(), cmp); // k �������� �����Ѵ�.
	int prev_k = 0;
	for (qtype2& x : query2) {
		if (prev_k < x.k) { // query2�� k�� �ϳ��� �������� �ʰ� ��� �ǳʶ� �� �ִ�!!!
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
	sort(query2.begin(), query2.end(), cmp); // ���� �Էµ� ������ �ٽ� �����Ѵ�.
	for (qtype2& x : query2) cout << x.result << "\n";
}