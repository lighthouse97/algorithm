// 10423.cpp
// ���Ⱑ ������
// University > �������б� > 2014 Sogang Programming Contest - Master E��
// University > �������б� > 2014 Sogang Programming Contest - Champion D��
// MST �����ε�... MST���� ������ ������ ������ �� ������ ��� ������ ���տ� ���ϴ����� üũ�ؼ�
// ������ ��� ���ϴ� ��츸 ���� ���ῡ�� �����Ѵ�.
// �� ���ʸ� �������̰ų� ���� ��� �����Ұ� �ƴ� ��츸 �����ؼ� ������ �ּҰ��� ���Ѵ�.
// ���ѽð� 1�� �� 32ms(3,200KB)�� �ҿ�Ǿ���.
// ������� 35/628�� ���� 5.57%�� rank�Ǿ���.

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
/////
vector<bool> g_plant;

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
		int f1 = djs_find(x.from);
		int f2 = djs_find(x.to);
		if (f1 != f2) {
			if (!g_plant[f1] || !g_plant[f2]) { // ������ ��� �� ������ �ƴ� ���
				if (g_plant[f2]) djs_union(x.to, x.from);
				else djs_union(x.from, x.to);
				count++;
				minval += x.cost;
			}
		}
		if (count == vcnt - 1) break;
	}
	return minval;
}

int main()
{
	FAST;
	int N, M, K;
	cin >> N >> M >> K;
	g_graph.resize(M, { 0, 0, 0 });
	g_parent.resize(N + 1, -1);
	g_plant.resize(N + 1, false);
	int p;
	for (int i = 0; i < K; i++) {
		cin >> p;
		g_plant[p] = true;
	}
	int u, v, w;
	for (int i = 0; i < M; i++) {
		cin >> u >> v >> w;
		g_graph[i] = { u, v, w };
	}
	cout << kruskal(N) << "\n";
}