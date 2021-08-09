// 16168.cpp
// �۷��̵�
// University > ���Ǵ��б� > 2018 SCAL-MOOKJA D��
// University > �߾Ӵ��б� > 2018 SCAL-MOOKJA D��
// ���Ϸ� ȸ��(Euler Circuit) �Ǵ� ��θ� ����ϴ� �������� �˱⸸ �ϸ�
// �ݹ� Ǯ �� �ִ� �����̴�.
// ���Ϸ� ȸ�� �Ǵ� ���Ϸ� ��� ���θ� ���� �����̴�.
// ���� �������� ���Ϸ� ��ΰ� 2�� �̻������� �ȵǹǷ� �� ���� üũ�ؾ� �Ѵ�.
// BFS, DFS, djsjoint-set ������ üũ�� �� �ִµ� ���� disjoint-set�� ����Ͽ���.
// ���ѽð� 2�� �� 40ms(37,408KB)�� �ҿ�Ǿ���.
// ������� 123/177�� ���� 69.49123/177%�� rank�Ǿ���.

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

vector<vector<int>> g_graph;
vector<int> g_parent; // union-find ���(�����׷��� 2�� �̻��ΰ� üũ)

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

int main()
{
	FAST;
	int V, E;
	cin >> V >> E;
	g_graph.resize(V + 1, vector<int>(V + 1, 0));
	g_parent.resize(V + 1, -1);
	int v1, v2;
	for (int i = 0; i < E; i++) {
		cin >> v1 >> v2;
		g_graph[v1][v2] = 1;
		g_graph[v2][v1] = 1;
		djs_union(v1, v2);
	}
	int found = djs_find(1);
	for (int i = 2; i < V + 1; i++) {
		if (found != djs_find(i)) {
			cout << "NO" << "\n";
			return 0;
		}
	}
	int cnt = 0, ecnt = 0;
	for (int i = 1; i < V + 1; i++) {
		for (int j = 1; j < V + 1; j++) cnt += g_graph[i][j];
		if (cnt % 2) ecnt++;
		cnt = 0;
	}
	cout << (ecnt == 0 || ecnt == 2 ? "YES" : "NO") << "\n"; // 0�̸� ���Ϸ� ȸ��, 2�̸� ���Ϸ� ���
}