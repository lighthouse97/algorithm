// 1738.cpp
// ����
// ���� ���� �˰��� �����ε�, 1219(���ν��� ���) ������ ���� �ּҰ��� �ƴ� �ִ밪�� ã�� �����̴�.
// N��° ������ ���������� �ִ밪�� ���ϴ� �� �ƴ϶� �ִ밪�� ���� ���� ��θ� ���ϴ� ���� �ٸ���.
// ��θ� ���ϱ� ���ؼ��� dist[]�迭�� �ִ밪 �� ���� ��α��� ���� �����Ѵ�.
// N��° ������ �������� ���ϸ� -1, cycle�� �߻��Ͽ� �̰� N��° ������ ������ ��ġ�� �� ���� -1�� ����Ѵ�.
// �ᱹ '1219(���ν��� ���)'�� ���� ������ �����ε�, �������ϴ� �͸� �ٸ���!
// ���ѽð� 2�� �� 4ms(2,296KB)�� �ҿ�Ǿ���.
// ������� 123/256�� ���� 48.04%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
//#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
#include <stack>
//#include <set>
#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct path {
	int c, p; // next(or previous) city, traffic price
	path() : c(0), p(0) {}
	path(int c, int p) : c(c), p(p) {}
};

const int INF = 2000000000;
vector<vector<path>> g_graph; // ���� �׷���
vector<path> g_maxp; // �ִ� ���� ����
int g_N, g_M;
vector<int> g_check; // ���������� ����Ŭ ������ �޴��� üũ!

void bellman_ford()
{
	int money;
	g_maxp[1] = { 1, 0 };
	for (int i = 1; i < g_N + 1; i++) {
		for (int j = 1; j < g_N + 1; j++) {
			for (path& x : g_graph[j]) {
				money = g_maxp[j].p + x.p; // ���絵���� �̵� - �̵���� + ���� ������ �̵�
				if (g_maxp[j].p != -INF && money > g_maxp[x.c].p) {
					g_maxp[x.c] = { j, money };
					if (i == g_N) g_check.push_back(x.c); // ����Ŭ �߻� ���� ����. ���߿� ������ ����!
				}
			}
		}
	}
}

int main()
{
	FAST;
	cin >> g_N >> g_M;
	g_graph.resize(g_N + 1);
	g_maxp.resize(g_N + 1, { 0, -INF });
	g_check.reserve(g_N + 1);
	int u, v, w;
	for (int i = 0; i < g_M; i++) {
		cin >> u >> v >> w;
		g_graph[u].push_back({ v, w });
	}
	bellman_ford(); // bellman ford �˰���
	
	int result = g_maxp[g_N].p;
	if (result == -INF) {
		cout << -1 << "\n";
		return 0;
	}
	bool cycle = false; // ���⼭ ���� ����Ŭ�� ���������� ����Ǿ� �ִ��� �Ǻ�(bfs�� �Ǻ�)
	vector<bool> visited(g_N + 1, false);
	queue<int> myq;
	for (int x : g_check) myq.push(x);
	while (!myq.empty()) {
		int cur = myq.front();
		myq.pop();
		visited[cur] = true;
		if (cur == g_N) { cycle = true; break; } // ��������(N)�� ����Ŭ ������.
		for (path& x : g_graph[cur]) {
			if (!visited[x.c]) {
				visited[x.c] = true;
				myq.push(x.c);
			}
		}
	}
	if (cycle) cout << -1 << "\n";
	else { // ��ǥ������ cycle�� ���� ��� ���� ��θ� ����Ѵ�.
		stack<int> chain;
		int cur = g_N;
		while (1) {
			chain.push(cur);
			if (cur == 1) break;
			cur = g_maxp[cur].c; // previous						
		}
		while (!chain.empty()) {
			cout << chain.top() << " ";
			chain.pop();
		}
		cout << "\n";
	}
}