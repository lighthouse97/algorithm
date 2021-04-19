// 1719.cpp
// �ù�
// 11780�� �����ϰ� Floyd-Warshall�� ��� ������ ���� �ִ� ��ο� �� ��θ� ����ϴ� �����̴�.
// �Ѱ��� ������ ����, �ִ� ��ο��� ���� �������� �湮�ߴ� ������ �ƴ϶� ���� ���� �湮�� ������ ����ؾ� �Ѵ�!!!
// �׷��� ��� �������� �ؾ� �Ѵ�!!!
// k�� �����ϰ� �� k�� ���� ����� �� �������ص� ���ڸ�,
// g_graph[i][j]�� ���� �߰� ��ΰ� k�̸� �ִ� ��� update�ÿ� g_graph[i][j].k = g_graph[i][k].k �� ������Ʈ�ص� �ȴ�.(�̰� �� �����ϴ�)
// i -> j�� �ִ� �Ÿ��� �߰� ��ΰ� k�̸� i -> k�� �ִ� �Ÿ��� �߰� ��� k�� ������Ʈ�Ѵ�. �̷��� �ϸ� ���� i -> j �ִ� �Ÿ��� ù �湮������ �� �� �ִ�.
// ���ѽð� 2�� �� 16ms(2,416KB)�� �ҿ�Ǿ���.
// ������� 86/752�� ���� 11.43%�� rank�Ǿ���.

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

struct point {
	int t, k; // time, k(path)
	point() : t(0), k(0) {}
	point(int t, int k) : t(t), k(k) {}
};

const int INF = 987654321;
int g_N;
vector<vector<point>> g_graph;

void floyd_warshall()
{
	for (int k = 1; k < g_N + 1; k++) {
		for (int i = 1; i < g_N + 1; i++) {
			for (int j = 1; j < g_N + 1; j++) { 
				if (g_graph[i][k].t + g_graph[k][j].t < g_graph[i][j].t) {
					g_graph[i][j].t = g_graph[i][k].t + g_graph[k][j].t;
					g_graph[i][j].k = g_graph[i][k].k; // �߰� ��� ����
				}
			}
		}
	}
}

int main()
{
	FAST;
	cin >> g_N;
	g_graph.resize(g_N + 1, vector<point>(g_N + 1, { INF, 0 }));
	for (int i = 1; i < g_N + 1; i++) g_graph[i][i].t = 0;
	int m;
	cin >> m;
	int s, e, t;
	for (int i = 0; i < m; i++) {
		cin >> s >> e >> t;
		g_graph[s][e].t = t;
		g_graph[e][s].t = t;
		g_graph[s][e].k = e;
		g_graph[e][s].k = s;
	}
	floyd_warshall();
	for (int i = 1; i < g_N + 1; i++) {
		for (int j = 1; j < g_N + 1; j++) {
			if (i == j) cout << '-' << " ";
			else
				cout << g_graph[i][j].k << " ";
		}
		cout << "\n";
	}
}