// 2660.cpp
// ȸ�� �̱�
// Olympiad > �ѱ������ø��ǾƵ� > KOI 1997 > �ʵ�� 3��
// ���� Floyd-Warshall ���빮���̴�.
// ģ�����̶� ��������� ��� �ִ� �Ÿ��� ���Ѵ�.
// ȸ�� i�� ���� ��� ģ������ �Ÿ��� ���� ū ���� �� ȸ�� ������ �ȴ�.
// ���� ������ ���� ���� ȸ���� ã�� ���� ���� ���� �� ���� ���� ȸ���� ����, �׸��� �� ȸ���� ������������ ����ϴ� ���� �����̴�.
// deque�� ����ϸ� �ǰڴ�.
// ���ѽð� 1�� �� 0ms(2,020KB)�� �ҿ�Ǿ���.
// ������� 731/1848�� ���� 39.55%�� rank�Ǿ���.

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
#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_graph;
int g_N;
const int INF = 987654321;

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
	cin >> g_N;
	g_graph.resize(g_N + 1, vector<int>(g_N + 1, INF));
	for (int i = 1; i < g_N + 1; i++) g_graph[i][i] = 0;
	int a, b;
	while (1) {
		cin >> a >> b;
		if (a == -1 && b == -1) break;
		g_graph[a][b] = 1;
		g_graph[b][a] = 1;
	}
	floyd_warshall();

	vector<int> score(g_N + 1, 0);
	int maxval;
	for (int i = 1; i < g_N + 1; i++) {
		maxval = 0;
		for (int j = 1; j < g_N + 1; j++) {
			if (g_graph[i][j] > maxval)
				maxval = g_graph[i][j];
		}
		score[i] = maxval;
	}
	deque<pair<int, int>> dq;
	dq.push_back({ 1, score[1] });
	for (int i = 2; i < g_N + 1; i++) {
		while (!dq.empty() && dq.back().second > score[i]) // ���� ���� �͸� ������ ������.
			dq.pop_back();
		if (!dq.empty() && dq.back().second < score[i]) continue;
		dq.push_back({ i, score[i] });
	}
	cout << dq.front().second << " " << dq.size() << "\n";
	while (!dq.empty()) {
		cout << dq.front().first << " ";
		dq.pop_front();
	}
	cout << "\n";
}