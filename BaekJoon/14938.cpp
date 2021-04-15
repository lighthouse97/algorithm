// 14938.cpp
// ���� �׶���
// University > �������б� > 2017 Sogang Programming Contest - Master D��
// Floyd-Warshall�� Ǯ �� �ִ�. �տ��� Ǭ 1508������ ����ϴ�.
// Floyd-Warshall�� �� ������ ���� �ִ� ��θ� ��� ���Ѵ�.
// ���� �� �������� �ִ� ��� �� ���� ������ ���� ����� ������ ���� �ջ��Ѵ�.
// �� ������ �ջ�� ������ �� �� ���� ū ���� ����.
// ���ѽð� 1�� �� 0ms(2,056KB)�� �ҿ�Ǿ���.
// ������� 417/824�� ���� 50.60%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
//#include <vector>
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

const int INF = 987654321;
int g_N;
int g_graph[101][101];
int g_item[101];

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

	int m, r;
	cin >> g_N >> m >> r;
	for (int i = 1; i < g_N + 1; i++) { // initialize
		for (int j = 1; j < g_N + 1; j++) {
			if (i == j) g_graph[i][j] = 0;
			else g_graph[i][j] = INF;
		}
	}
	for (int i = 1; i < g_N + 1; i++) cin >> g_item[i];
	int s, e, l;
	for (int i = 0; i < r; i++) {
		cin >> s >> e >> l;
		g_graph[s][e] = g_graph[e][s] = l;
	}
	floyd_warshall();

	int sum = 0, maxsum = 0;
	for (int i = 1; i < g_N + 1; i++) {
		sum = 0;
		for (int j = 1; j < g_N + 1; j++) {
			if (g_graph[i][j] < m + 1) sum += g_item[j];
		}
		if (sum > maxsum) maxsum = sum;
	}
	cout << maxsum << "\n";
}