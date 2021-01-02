// 7626.cpp
// ���簢��
// University > The MIT Programming Contest > 2008-09 > MIT Programming Contest Team Contest 1 2008 7��
// ������ ���� ������ �ʹ��� ��ƴ�. �� ������ Ǯ�̸� ������ �ܿ� �����ߴ�.
// https://yooniversal.github.io/blog/post91/ ��
// https://codedoc.tistory.com/421 �� �����Ͽ���.
// x ��ǥ ������������ �����ϰ�, ����� y��ǥ�� segment tree�� �����.
// x��ǥ�� sweeping�ϸ鼭 �ش� x��ǥ�� y��ǥ ������ s-tree�� ī��Ʈ�ϰ� ī��Ʈ �� ���� ������ ����Ѵ�.
// x��ǥ�� ������ �� ī��Ʈ +1, �簢���� x��ǥ�� ���� �� ī��Ʈ -1�� �ش�.
// �ش� ����� ī��Ʈ�� 0�̸� ���� �ڽ� ����� ������ ���ļ� �ݿ��Ѵ�.(��Ʈ ��常 ���� ���� ��ȿ�� y������ �� �� �ִ�)
// �̷��� �ϸ� y��ǥ�� �� ������ ª�� ���� ���� �켱������ ������ �ȴ�.
// x��ǥ�� sweeping�ϹǷ� (���� x ��ǥ - ���� x ��ǥ) * (y��ǥ ���� �Ÿ�)�� �簢���� ������ �ȴ�.
// ������ ��)
// --- ������ �߿��ϹǷ� �ݵ�� segment tree�� ��� �Ѵ�. fenwick tree�δ� ���� ���� �� ����.
// y��ǥ ������ update�� ��, ������ leaf node�� �ɰ��� query�� �� �ִ�. ���� ��� 3 ~ 4�� ���� 3, 4 ������ ����� �� �ִ�.
// �̷� ������ ������ ����ϸ� ������ ���� 0�� ��ϵǹǷ� �̸� �ذ��ϱ� ���� technique�� �ʿ��ϴ�.
// (l, r)�� ����Ѵٸ� (l+1, r)�� ����Ѵ�. �׸��� update�� �� ���� ��� �� (l-1, r)�� ����Ѵ�.
// ���� ��� (2, 4)�����ε� (3, 4)�� update�ϰ� 3, 4�� �ɰ����� ���� ��Ͻ� (2~3), (3~4)�� ����ϸ� �ᱹ (2~4)�� ����� �ȴ�.
// ����ϴ�!!!
// === �̰� Segment Tree�� �����ؾ� Ǯ �� �ִ� ������ ���� ���� ���� ���Ѱ� ����.
// ���ѽð� 3�� �� 500ms(18,048KB)�� �ҿ�Ǿ���.
// ������� 11/153�� ���� 7.18%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
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

struct loc {
	int x, y1, y2, mark; // x��, y1~y2����, �簢�� ����/�� ����(+1/-1)
	loc() : x(0), y1(0), y2(0), mark(0) {}
	loc(int x, int y1, int y2, int m) : x(x), y1(y1), y2(y2), mark(m) {}
};

struct node_info {
	int cnt, distance; // s-tree node����(���� ī��Ʈ, ������ �Ÿ�)
	node_info() : cnt(0), distance(0) {}
	node_info(int c, int d) : cnt(c), distance(d) {}
};

vector<loc> square; // �Էµ� �簢��
vector<int> yaxis; // y�� ����(�ߺ� ����)
vector<node_info> s_tree; // segment tree

// segment tree �� update�� ������ �ȴ�. but ���� update�� �������� ������ �Ϻ� ���Եȴ�.
void update(int node, int start, int end, int left, int right, int diff)
{
	int mid;
	if (end < left || right < start) return;
	else if (left <= start && end <= right)
		s_tree[node].cnt += diff;
	else { // �Ϻθ� ��ĥ ���
		mid = (start + end) >> 1;
		update(2 * node, start, mid, left, right, diff);
		update(2 * node + 1, mid + 1, end, left, right, diff);
	}
	if (s_tree[node].cnt) s_tree[node].distance = yaxis[end] - yaxis[start - 1]; // cnt > 0�̸� �ش� ���� �Ÿ� ����
	else {
		if (start == end) s_tree[node].distance = 0; // leaf node, ������ ���� ���� ����, 0�� �ȴ�
		else s_tree[node].distance = s_tree[2 * node].distance + s_tree[2 * node + 1].distance; // child�� ���� �ݿ�
	}
}

int main()
{
	FAST;
	
	int N;
	cin >> N;
	square.resize(2 * N + 1);
	yaxis.resize(2 * N + 1);
	
	int x1, x2, y1, y2;
	for (int i = 1; i < N + 1; i++) {
		cin >> x1 >> x2 >> y1 >> y2;		
		square[i * 2 - 1] = { x1, y1, y2, 1 }; // �簢���� ����
		square[i * 2] = { x2, y1, y2, -1 }; // �簢���� ��
		yaxis[i * 2 - 1] = y1;
		yaxis[i * 2] = y2;
	}	
	auto cmp = [](const loc& a, const loc& b) {
		if (a.x == b.x) return a.y1 < b.y1;
		return a.x < b.x;
	};
	sort(square.begin() + 1, square.end(), cmp); // x��ǥ �������� ����
	sort(yaxis.begin() + 1, yaxis.end()); // y��ǥ��, �������� ����
	yaxis.erase(unique(yaxis.begin() + 1, yaxis.end()), yaxis.end()); // y�� �ߺ� ����
	int h, tree_size;
	h = (int)ceil(log2(yaxis.size() - 1)); // 0�� ���� ���
	tree_size = 2 * (1 << h);
	s_tree.resize(tree_size); // segment tree ����

	ll sum = 0;
	int left, right, end = (int)yaxis.size() - 1;
	int prev_x = square[1].x;
	for (int i = 1; i < 2 * N + 1; i++) {
		sum += 1LL * (square[i].x - prev_x) * s_tree[1].distance; // delta x * y ���� �Ÿ� = ���簢�� ����
		left = lower_bound(yaxis.begin() + 1, yaxis.end(), square[i].y1) - yaxis.begin();
		right = lower_bound(yaxis.begin() + 1, yaxis.end(), square[i].y2) - yaxis.begin();
		update(1, 1, end, left + 1, right, square[i].mark);
		prev_x = square[i].x;
	}
	cout << sum << "\n";
}