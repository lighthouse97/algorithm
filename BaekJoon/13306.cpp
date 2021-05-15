// 13306.cpp
// Ʈ��
// Olympiad > �ѱ������ø��ǾƵ� > KOI 2016 > �ߵ�� 3��
// ������ �� �о��, N - 1���� ������ �����ϱ� ������ �ᱹ ��� ����(edge)�� �����ϴ� ���� �ȴ�.
// �� ���� query �������� ������ ������ ���Ű� �ǰ� �Ʒ����� ������ ��� ������ ������ �� ������ ���̴�.
// ���� ���߻�����, N - 1�� ������ ������ �ؿ��� �Ųٷ� �ö󰡸鼭 ������ ���ʷ� ����(union)�Ѵ�. �׷��鼭 ������ ó���Ѵ�.
// (find()�� ���� ������ �� ������ ����, �ٸ��� ������ ���̴�.) �׸��� ������ ����� ���� ����� �������� ����ϸ� �ȴ�.
// ���ѽð� 2�� �� 160ms(10,952KB)�� �ҿ�Ǿ���.
// ������� 225/821�� ���� 27.40%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
//#include <list>
//#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
#include <utility> // pair
#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<int> g_parent;

int djs_find(int x)
{
	if (g_parent[x] < 0) return x;
	return g_parent[x] = djs_find(g_parent[x]);
}

void djs_union(int x, int y)
{
	int r1 = djs_find(x);
	int r2 = djs_find(y);

	if (r1 == r2) return;
	g_parent[r1] += g_parent[r2];
	g_parent[r2] = r1;
}

int main()
{
	FAST;

	int N, Q;
	vector<int> edge;
	vector<pair<int, pair<int, int>>> query;
	cin >> N >> Q;
	g_parent.resize(N + 1, -1);
	edge.resize(N + 1, 0);
	query.resize(N - 1 + Q);

	int a;
	int x, b, c, d;
	for (int i = 1; i < N; i++) { // ������������
		cin >> a;
		edge[i + 1] = a; // child -> parent
	}
	for (int i = 0; i < N - 1 + Q; i++) { // ���� ���� ����
		cin >> x;
		if (!x) {
			cin >> b;
			query[i] = { x, { b, 0 } }; // b : child
		}
		else {
			cin >> c >> d;
			query[i] = { x, { c, d } };
		}
	}

	stack<int> myst;
	for (int i = N - 1 + Q - 1; i >= 0; i--) {
		if (!query[i].first) { // link
			djs_union(edge[query[i].second.first], query[i].second.first);
		}
		else { // query
			c = djs_find(query[i].second.first);
			d = djs_find(query[i].second.second);
			myst.push((c == d ? 1 : 0)); // 1 : YES, 0 : NO
		}
	}
	while (!myst.empty()) {
		b = myst.top();
		myst.pop();
		cout << (b ? "YES" : "NO") << "\n";
	}
}