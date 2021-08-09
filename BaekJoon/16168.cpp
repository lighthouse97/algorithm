// 16168.cpp
// 퍼레이드
// University > 숭실대학교 > 2018 SCAL-MOOKJA D번
// University > 중앙대학교 > 2018 SCAL-MOOKJA D번
// 오일러 회로(Euler Circuit) 또는 경로를 사용하는 문제임을 알기만 하면
// 금방 풀 수 있는 문제이다.
// 오일러 회로 또는 오일러 경로 여부를 묻는 문제이다.
// 서로 독립적인 오일러 경로가 2개 이상있으면 안되므로 이 또한 체크해야 한다.
// BFS, DFS, djsjoint-set 등으로 체크할 수 있는데 나는 disjoint-set를 사용하였다.
// 제한시간 2초 중 40ms(37,408KB)가 소요되었다.
// 맞은사람 123/177로 상위 69.49123/177%에 rank되었다.

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
vector<int> g_parent; // union-find 사용(독립그래프 2개 이상인가 체크)

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
	cout << (ecnt == 0 || ecnt == 2 ? "YES" : "NO") << "\n"; // 0이면 오일러 회로, 2이면 오일러 경로
}