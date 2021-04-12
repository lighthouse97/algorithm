// 1613.cpp
// ����
// 2458 ������ �����ϴ�. Floyd-Warshall�� Ǯ �� �ִ�.
// ��ΰ� ������ 1, ��ΰ� ������ 0���� ǥ���Ѵ�.
// ������ a b�� �־��� �� a -> b ��� ������ a�� �ռ��Ƿ� -1
// a -> b�� ������ b -> a�� ������ a�� �����̹Ƿ� 1,
// a -> b, b -> a �� �� ��� ������ ������ �� �� �����Ƿ� 0���� ǥ���Ѵ�.
// ���ѽð� 1�� �� 84ms(2,680KB)�� �ҿ�Ǿ���.
// ������� 590/2340�� ���� 25.21%�� rank�Ǿ���.

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
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_graph;
int g_N;

void floyd_warshall()
{
	for (int k = 1; k < g_N + 1; k++) {
		for (int i = 1; i < g_N + 1; i++) {
			for (int j = 1; j < g_N + 1; j++) {
				if (g_graph[i][k] & g_graph[k][j]) g_graph[i][j] = 1;
			}
		}
	}
}

int main()
{
	FAST;
	int k, s;
	cin >> g_N >> k;
	g_graph.resize(g_N + 1, vector<int>(g_N + 1, 0));

	int a, b;
	for (int i = 1; i < g_N + 1; i++) g_graph[i][i] = 1;
	for (int i = 0; i < k; i++) {
		cin >> a >> b;
		g_graph[a][b] = 1;
	}
	floyd_warshall();
	
	cin >> s;
	for (int i = 0; i < s; i++) {
		cin >> a >> b;
		cout << (g_graph[a][b] ? -1 : g_graph[b][a] ? 1 : 0) << "\n";
	}
}