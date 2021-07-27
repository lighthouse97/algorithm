// 4792.cpp
// ���� ��� ���д� Ʈ��
// University > North American Invitational Programming Contest > UCIPC 2012 G��
// �Ķ��� ������ cost�� 1, ������ ������ cost�� 0���� �ϰ� MST ������.
// �׷��� �Ķ��� ������ �ּҷ� ������� ���� �Ķ��� ������ ������ ���´�.
// ���� �Ķ��� ������ cost�� -1, ������ ������ cost�� 0���� �ϰ� MST ������.
// ����� -1 ���ϸ� �Ķ��� ������ �ִ�� ������� ���� �Ķ��� ������ ������ ���´�.
// �Ķ��� ������ �ּҰ��� �ִ밪 ������ ������ k�� ������ k���� �Ķ��� �������� ST�� ������ �� �ִ�
// ���̴�.
// �Ʒ��� ó���� Ʋ���� ������ ����̴�.
// MST, �Ķ��� ������ cost�� 0, ������ ������ cost�� 1�� �ϰ�
// MST ���Ѵ�.
// MST �߿� �Ķ��� ������ ������ K���� �Ѿ�� ������ �������� �Ѿ��.
///////
// ���ѽð� 3�� �� 196ms(6,832KB)�� �ҿ�Ǿ���.
// ������� 60/639�� ���� 9.38%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil, hypot
#include <vector>
//#include <list>
#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct edge {
	int from, to, cost;
	edge() : from(0), to(0), cost(0) {}
	edge(int f, int t, int c) : from(f), to(t), cost(c) {}
	bool operator< (const edge& rhs) { return cost < rhs.cost; }
};

vector<edge> g_graph;
vector<int> g_parent;

int djs_find(int item)
{
	if (g_parent[item] < 0) return item;
	return g_parent[item] = djs_find(g_parent[item]);
}

void djs_union(int u, int v)
{
	int u1 = djs_find(u);
	int v1 = djs_find(v);
	if (u1 == v1) return;
	else {
		g_parent[u1] += g_parent[v1];
		g_parent[v1] = u1;
	}
}

int kruskal(int vcnt)
{
	int count = 0, minval = 0;
	sort(g_graph.begin(), g_graph.end()); // ��뿡 ���� ��������
	for (edge& x : g_graph) {
		if (djs_find(x.from) != djs_find(x.to)) {
			djs_union(x.from, x.to);
			count++;
			minval += x.cost;
		}
		if (count == vcnt - 1) break;
	}
	return minval;
}

int main()
{
	FAST;
	int n, m, k;
	while (true) {
		cin >> n >> m >> k;
		if (!n && !m && !k) break;
		g_graph.assign(m, { 0, 0, 0 });
		g_parent.assign(n + 1, -1);
		char c;
		int color, f, t;
		for (int i = 0; i < m; i++) {
			cin >> c >> f >> t;
			color = (c == 'B') ? 1 : 0;
			g_graph[i] = { f, t, color };
		}
		int minval = kruskal(n); // blue min value

		g_parent.assign(n + 1, -1);
		for (int i = 0; i < m; i++) g_graph[i].cost *= -1;
		int maxval = -kruskal(n); // blue max value
		cout << (minval <= k && k <= maxval ? 1 : 0) << "\n";
	}
}