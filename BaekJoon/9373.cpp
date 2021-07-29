// 9373.cpp
// ���� �ձ�
// ICPC > Regionals > Europe > Northwestern European Regional Contest > Benelux Algorithm Programming Contest > BAPC 2013 G��
// ���� ����� �����̴�.
// ���� ����� Ǯ�� ����� ������ ��μ� �����ϰ� �Ǿ���.
// Ǯ�̸� ���� ���� �� �������� MST�� Ǯ �� �ִ� ������� ���� �˰� �Ǿ���.
// n�� 0�� ���, �� ������ �ϳ��� ���� ��쵵 ����ؾ� �Ѵ�!!!
// kruskal�Լ����� minval�� �������� �ƴϴ�! ���� ��������!!!
// ���ѽð� 5�� �� 880ms(14,472KB)�� �ҿ�Ǿ���.
// ������� 69/266�� ���� 25.93%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
#include <cmath> // pow, sqrt, fabs. ceil, hypot
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
	int from, to;
	double cost;
	edge() : from(0), to(0), cost(0.0) {}
	edge(int f, int t, double c) : from(f), to(t), cost(c) {}
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

double kruskal(int vcnt, int left, int right)
{
	int count = 0;
	double minval = 0.0;
	sort(g_graph.begin(), g_graph.end()); // ��뿡 ���� ��������
	for (edge& x : g_graph) {
		if (djs_find(x.from) != djs_find(x.to)) {
			djs_union(x.from, x.to);
			count++;
			minval = x.cost;
			if (djs_find(left) == djs_find(right)) break; // ���� �� ��� ����, �� Ž���� �ʿ� ����!			
		}
		if (count == vcnt - 1) break;
	}
	return minval;
}

struct circle {
	int x, y, r;
	circle() : x(0), y(0), r(0) {}
	circle(int x, int y, int r) : x(x), y(y), r(r) {}
	double dist(const circle& rhs) {
		return max(0.0, hypot(x - rhs.x, y - rhs.y) - r - rhs.r);
	}
};

void doTest()
{
	int w, n;
	cin >> w >> n;
	int left = n, right = n + 1;
	vector<circle> sensor;
	g_parent.assign(n + 2, -1);
	sensor.assign(n, { 0, 0, 0 });
	int x, y, r;
	for (int i = 0; i < n; i++) {
		cin >> x >> y >> r;
		sensor[i] = { x, y, r }; // ���� ����
		double space = max(0, x - r);
		g_graph.push_back({ left, i, space });
		space = max(0, w - x - r); // ������ ����
		g_graph.push_back({ right, i, space });
	}
	for (int i = 0; i < n; i++) { // �����鳢�� ����
		for (int j = i + 1; j < n; j++) {
			double space = max(0.0, sensor[i].dist(sensor[j]));
			g_graph.push_back({ i, j, space });
		}
	}
	g_graph.push_back({ left, right, 1.0 * w }); // ������ ���� ��쵵 ���
	double answer = kruskal(n + 2, left, right);
	answer *= 0.5;
	cout << fixed;
	cout.precision(6);
	cout << answer << "\n";
	g_graph.clear();
}

int main()
{
	FAST;
	int T;
	cin >> T;
	while (T--) doTest();
}