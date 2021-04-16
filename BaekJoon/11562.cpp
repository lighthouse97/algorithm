// 11562.cpp
// ���� �극��ũ
// University > �������б� > 2015 �������б� ���α׷��� ��ô�ȸ F��
// ó������ ������ �� �� ��Ҵ�!
// ������ �������� �ִ� �Ÿ��� ��� ���������� �� �� ���� ��ġ�� ���������� ���󰡸鼭 ������� �����ϰ�
// ������ �������� �Ÿ��� ���� ������ ���ߴµ� �̷��� �ϸ� Ʋ����! ���� ���,
// 1 -> 5���� 1 -> 2 -> 3 -> 5 ��ο� 1 -> 6 <-> 7 <-> 8 <-> 5�� ��ΰ� ���� ���,
// ������ ���� �ִ� �Ÿ��� ������ �翬�� 1 -> 2 -> 3 -> 5 ��ΰ� ���õǰ� 5 -> 1�� �� �� ��������, 3���� ��θ� ��������� ����� �־�� �Ѵ�.
// �׷��� ������ �ȵ� 1 -> 6 <-> 7 <-> 8 <-> 5 ��θ� �����ϸ� 1���� ��θ� ��������� ������ָ� �ȴ�.
// ���� ������ ���� �ִ� ��θ� ������ ���� ���� ���� ����.(�������� �������ϸ� ���� ���´�.)
// �׷��� ��� �ϴ���?
// ��Ʈ�� ����� ���Ҵµ�... �ᱹ �������� ���ɾ��� �����⿡�� ����� �����ϰ� ��ΰ� �ּҰ� �� ���� ��μ��� ���ϸ� �ȴ�.
// �� �Է¹��� �� ������� �ƴϸ� a -> b�� 0, b -> a�� 1, ������̸� �Ѵ� 0���� �Է��Ѵ�.
// �׸��� Floyd-Warshall�� ������, ���������� �� �� �ִ� ��δ� �ִ� ��ΰ� ��� 0�� �� ���̰�,
// ���������� �� �� ���� ��� �� �����⿡�� ������� �����ϰ� �ִ� ��μ��� ��������. �� ������ ������ �´� ���̴�.
// ���ѽð� 1�� �� 24ms(2,284KB)�� �ҿ�Ǿ���.
// ������� 27/656�� ���� 4.11%�� rank�Ǿ���.

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

const int INF = 987654421;
int g_N;
vector<vector<int>> g_graph;

void floyd_warshall()
{
	for (int k = 1; k < g_N + 1; k++) {
		for (int i = 1; i < g_N + 1; i++) {
			for (int j = 1; j < g_N + 1; j++) {
				if (g_graph[i][k] + g_graph[k][j] < g_graph[i][j])
					g_graph[i][j] = g_graph[i][k] + g_graph[k][j];
			}
		}
	}
}

int main()
{
	FAST;
	int m;
	cin >> g_N >> m;
	g_graph.resize(g_N + 1, vector<int>(g_N + 1, INF));
	for (int i = 1; i < g_N + 1; i++) g_graph[i][i] = 0;
	int u, v, b;
	for (int i = 0; i < m; i++) { // ���Ⱑ �ٽ��̴�!
		cin >> u >> v >> b;
		g_graph[u][v] = 0;
		g_graph[v][u] = b ? 0 : 1;
	}
	floyd_warshall();
	int k, s, e; // query
	cin >> k;
	for (int i = 0; i < k; i++) {
		cin >> s >> e;
		cout << g_graph[s][e] << "\n";
	}
}