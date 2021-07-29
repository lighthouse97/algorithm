// 13905.cpp
// ����
// University > �������б� > ��12ȸ ����� �������б� ���α׷��� ��ȸ Champion F��
// MST �����ε�, ������ cost�� ������ �� �����̱� ������ ������� �������� ���� �������� ���̴� ������ ������ ����ġ�� ���� �ȴ�.
// ���� ������ ����ġ�� ������ �������� ���� ����� �� �ٽ� -�� �ٿ��־�� �Ѵ�.
// MST�� �Ӽ��� ���� �� �̿��ϴ� ���� ������ �� �� �ִ�!!!
// MST Ž���� ������ ��������� bfs �Ǵ� dfs Ž���� �ؼ� ã�ư� ���� �ִµ� �װ� �� ��ȿ�������� ���δ�!!!
// ���ѽð� 1�� �� 104ms(5,932KB)�� �ҿ�Ǿ���.
// ������� 8/304�� ���� 2.63%�� rank�Ǿ���.

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

int kruskal(int vcnt, int s, int t)
{
	int count = 0, minval = 0;
	int answer;
	sort(g_graph.begin(), g_graph.end()); // ��뿡 ���� ��������
	for (edge& x : g_graph) {
		if (djs_find(x.from) != djs_find(x.to)) {
			djs_union(x.from, x.to);
			count++;
			minval += x.cost;
			if (djs_find(s) == djs_find(t)) { // '����� - ������' ��ΰ� ��������� ������ �����.
				answer = x.cost;
				break;
			}
		}
		if (count == vcnt - 1) break;
	}
	return answer;
}

int main()
{
	FAST;
	int N, M, s, t;
	cin >> N >> M >> s >> t;
	g_graph.resize(M, { 0, 0, 0 });
	g_parent.resize(N + 1, -1);
	int h1, h2, k;
	for (int i = 0; i < M; i++) {
		cin >> h1 >> h2 >> k;
		g_graph[i] = { h1, h2, -k };
	}
	cout << -kruskal(N, s, t) << "\n";
}