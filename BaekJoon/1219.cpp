// 1219.cpp
// ���ν��� ���
// �ִ� �Ÿ� �˰��� �߿��� ����Ŭ ������ üũ�� �� �ִ� ���� ����(Bellman-Ford) �˰����� �̿��ϴ� �����̴�.
// ���� ���尡 �ִ� ��� ã�� �� ���� ����ġ�� ���� ����Ŭ ������ ã�� ���ε�... �� ������ �̸� ����� �����ؾ� �Ѵ�.
// (���� ��ο� ��� ����ġ�� ���� ����Ŭ ����...)
// �� ������ �ִ밪�� �����ϴ� �迭���� 100���� ���ð� 100���� ��η� ����Ŭ�� �̷� ��� 1000000 * 190 * 100����
// int�� ������ ��� �� �����Ƿ� long long type���� �迭�� �����ؾ� �Ѵ�!!!
// �׷��� bellman-ford�����̱⵵ ������ cycle ���� �Ǵ��ϴ� ���� ��ٷӴ�!!(�� �κп� ����ī�尡 �����ִ�)
// ���� 1) �ϴ� cycle�� �߻��ص� �������� ���� �� �� ���� ����(�� �� �߻��� ���), ������ ������ �켱�̴�. gg�� ���� �Ѵ�!
// ���� 2) cycle������� �������� �ִ� ��쵵 ������ ����� �ٱ��� ����Ǿ� �ִ� ��쵵 �ִ�.
//         �� ���� cycle�� ������ ��� ������ queue�� �־ bfs�� ����� ��� ������ Ž��, �������� ���� �� �������� �Ѵ�.
//         bfsŽ�� ��������, bfs Ž���� ���� queue�� �� ������ �������ϼ��� �����Ƿ� �׻� pop�� current queue����
//         �������ΰ��� ���� ���� �Ѵ�.
//			  ������� �������� ������ Gee, ������ ������������ �����̴�.
// ���ѽð� 2�� �� 0ms(2,020KB)�� �ҿ�Ǿ���.
// ������� 429/699�� ���� 61.37%�� rank�Ǿ���.

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
//#include <stack>
//#include <set>
#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

typedef long long ll;
struct path {
	int c, p; // next city, traffic price
	path() : c(0), p(0) {}
	path(int c, int p) : c(c), p(p) {}
};

const ll INF = 99999999999;
vector<vector<path>> g_city; // ���� �׷���
vector<ll> g_maxp; // �ִ� ���� ����
vector<int> g_profit; // �� ���ÿ��� ���� �� �ִ� ����
int g_N, g_S, g_E, g_M;
vector<int> g_check; // ���������� ����Ŭ ������ �޴��� üũ!

void bellman_ford()
{
	ll money;
	g_maxp[g_S] = g_profit[g_S];
	for (int i = 0; i < g_N; i++) {
		for (int j = 0; j < g_N; j++) {
			for (path& x : g_city[j]) {
				money = g_maxp[j] - x.p + g_profit[x.c]; // ���絵���� �̵� - �̵���� + ���� ������ �̵�
				if (g_maxp[j] != -INF && money > g_maxp[x.c]) {
					g_maxp[x.c] = money;
					if (i == g_N - 1) g_check.push_back(x.c); // ����Ŭ �߻� ���� ����. ���߿� ������ ����!
				}
			}
		}
	}
}

int main()
{
	FAST;
	cin >> g_N >> g_S >> g_E >> g_M;
	g_city.resize(g_N);
	g_maxp.resize(g_N, -INF);
	g_profit.resize(g_N, 0);
	g_check.reserve(g_N);
	int s, e, p;
	for (int i = 0; i < g_M; i++) {
		cin >> s >> e >> p;
		g_city[s].push_back({ e, p });
	}
	for (int i = 0; i < g_N; i++) cin >> g_profit[i];

	bellman_ford(); // bellman-ford algorithm

	ll result = g_maxp[g_E];

	bool cycle = false; // ���⼭ ���� ����Ŭ�� ���������� ����Ǿ� �ִ��� �Ǻ�(bfs�� �Ǻ�)
	vector<bool> visited(g_N, false);
	queue<int> myq;
	for (int x : g_check) myq.push(x);
	while (!myq.empty()) {
		int cur = myq.front();
		myq.pop();
		visited[cur] = true;
		if (cur == g_E) { cycle = true; break; }
		for (path& x : g_city[cur]) {
			if (!visited[x.c]) {
				visited[x.c] = true;
				myq.push(x.c);
			}
		}
	}

	if (result == -INF) cout << "gg" << "\n";
	else {
		if (cycle) cout << "Gee" << "\n";
		else cout << result << "\n";
	}
}