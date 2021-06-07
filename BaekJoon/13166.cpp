// 13166.cpp
// ���� ��Ƽ
// University > ���� ���л� ���α׷��� ��ȸ ���Ƹ� ���� ���� ��ȸ > UCPC 2016 H��
// �̺� Ž�� �����ε�, '1348 : ������'�� ����ϰ� Ǯ�� �ȴ�.
// �̺� ��Ī �ÿ� ���� K�� �ξ� K�� �����ϴ� �͸� ��Ī�� �Ѵ�.
// �׸��� 0 ~ K�� �̺� Ž������ �پ��� K���� �־ �̺� ��Ī�� �ִ� ��Ī  ���� N�� �Ǵ� �ּ����� K�� ���ϸ� �ȴ�.
// � K�� �־ �̺� ��Ī�� �ִ� ��Ī ����� N�� �ȳ����� -1�� ����Ѵ�.
// MLE ������ ���ͼ� ��뿡 map�� ����ߴ�.
// map�� ����ϸ� MLE�� �ȳ������� TLE�� �� �߻��Ͽ���.
// ��, �� ������ N�� ������ 200,000�̳� �ǹǷ� �Ϲ����� �̺и�Ī �˰���(�ܼ� dfs ���)�� ����ϸ�
// TLE�� �߻��� �� �ۿ� ���� �����̴�.
// �׷���!!! �� ������ Hopcroft-Karp �˰����� ����ؾ߸� Ǯ �� �ִ� �����̴�!!!
// Hopcroft-Karp �˰����� ����ؼ� �ٽ� Ǯ���.

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
#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_graph;
vector<bool> g_visited;
vector<int> g_matched;
map<pair<int, int>, int> g_cost;
int g_N = 0, g_FN = 0; // �������� ��, ģ���� ��

bool dfs_with_p(int from, int p)
{
	for (int to : g_graph[from]) {
		if (g_cost.find({ from, to }) == g_cost.end()) continue;
		if (g_cost[{from, to}] > p || g_visited[to]) continue;
		else g_visited[to] = true;
		if (g_matched[to] == 0 || dfs_with_p(g_matched[to], p)) {
			g_matched[to] = from;
			return true;
		}
	}
	return false;
}

int match(int t)
{
	int count = 0;
	g_matched.assign(g_FN + 1, 0);
	for (int i = 1; i < g_N + 1; i++) {
		g_visited.assign(g_FN + 1, false);
		if (dfs_with_p(i, t)) count++;
	}
	return count;
}

int main()
{
	FAST;
	cin >> g_N;
	g_graph.resize(g_N + 1);
	int f1, k1, f2, k2;
	int maxcost = 0;
	for (int i = 1; i < g_N + 1; i++) {
		cin >> f1 >> k1 >> f2 >> k2;
		g_graph[i].push_back(f1); // ģ�� 1		
		g_cost[{ i, f1 }] = k1;
		g_FN = max(g_FN, f1); // ģ���� �ִ� ��ȣ�� ã�´�
		maxcost = max(maxcost, k1);
		g_graph[i].push_back(f2); // ģ�� 2		
		g_cost[{ i, f2 }] = k2;
		g_FN = max(g_FN, f2);
		maxcost = max(maxcost, k2);
	}

	int left = 0, mid = 0, right = maxcost;
	while (left < right) { // ���� Ž��, lower_bound
		mid = (left + right) / 2;
		if (match(mid) < g_N) left = mid + 1; // �ð� �ø�
		else right = mid; // �ð� ����
	}
	if (match(left) == g_N) cout << left << "\n";
	else cout << -1 << "\n";
}