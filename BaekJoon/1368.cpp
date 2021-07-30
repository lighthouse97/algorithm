// 1368.cpp
// �����
// Olympiad > USA Computing Olympiad > 2008-2009 Season > USACO October 2008 Contest > Gold 3��
// Ǯ�̸� ����, ������ ������ ���� ������... ������ �������� ó���ϰ� �ؼ� MST�� ������ �ȴ�. 
// �̷��� �ϱ� ���ؼ��� ������ ���� N + 1�� ���� �̸� ������ �����Ų��. �� �� ����� ������ ����� 
// ������ ������� ������ �ȴ�.
// ������ ����ϴ�!!! �� �̷� ������ �� ������?
// ���ѽð� 2�� �� 12ms(3,676KB)�� �ҿ�Ǿ���.
// ������� 28/204�� ���� 13.72%�� rank�Ǿ���.

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
	int N;
	cin >> N;
	int wall = N + 1; // ������ ����ó�� ó���� �� �ְ� N + 1 ������ ����
	g_parent.resize(N + 2, -1);
	int w;
	for (int i = 1; i < N + 1; i++) {
		cin >> w;
		g_graph.push_back({ wall, i, w });
	}
	vector<vector<int>> link(N + 1, vector<int>(N + 1, 0));
	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < N + 1; j++)
			cin >> link[i][j];
	}
	for (int i = 1; i < N + 1; i++) {
		for (int j = i + 1; j < N + 1; j++)
			g_graph.push_back({ i, j, link[i][j] });
	}
	cout << kruskal(N + 1) << "\n";
}