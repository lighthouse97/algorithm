// 2458.cpp
// Ű ����
// Floyd-Warshall, 9205�� ����� �����̴�.
// �� �� ������ 1, �� �� ������ 0 ǥ���� ������, Floyd-Warshall ������.
// 0�� ��θ� Ž���ϸ鼭 a->b, b->a ��� 0�� ��θ� ī��Ʈ�ؼ� ��ü ���� �������� ���ش�.
// �� Ư�� �������� ��, �� ��ȣ�� ����� ��ΰ� �ϳ��� ������ �� ������ �ڽ��� Ű ������ �� �� ���� �����̴�.
// ���� �������� ���� 4�� �յڷ� ��� ������ ����Ǿ� �ְ�, ������ ������ �յڷ� ������ ���� �ȵ� ���� �ϳ� �̻� �ִ�.
// �װ� ���̴�!
// dfs�� �̿��ؼ� Ǯ�� �� �� ���� ó���� �ȴ�.
// floyd_warshall() �Լ����� g_graph[i][j], g_grapj[i][k], g_graph[k][j] ��� query�ϴ� ����� g_grapj[i][k], g_graph[k][j] 2���� query�ϴ� ���
// �� �ִµ�, g_grapj[i][k], g_graph[k][j] 2���� query�ϴ� ����� �ξ� ����ð��� �پ���.
// �뷫, 340ms -> 132ms�� ����ð��� 1/3 ���� �پ���.
// ���ѽð� 1�� �� 340ms(3,080KB)�� �ҿ�Ǿ���.
// ������� 1801/2824�� ���� 63.77%�� rank�Ǿ���.
// floyd_warshall() �Լ����� ����ȭ ���� ���, 340ms -> 132ms�� ����ȭ�ǰ� ���� ��� 1027/2825�� ���� 36.35%�� rank �ȴ�. 

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
				//if (!g_graph[i][j]) // �� �� ���� ��츸 ������.
				//	g_graph[i][j] = g_graph[i][k] * g_graph[k][j];
				if (g_graph[i][k] & g_graph[k][j]) g_graph[i][j] = 1;
			}
		}
	}
}

int main()
{
	FAST;
	int M;
	cin >> g_N >> M;
	g_graph.resize(g_N + 1, vector<int>(g_N + 1, 0));

	int a, b;
	for (int i = 1; i < g_N + 1; i++) g_graph[i][i] = 1;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		g_graph[a][b] = 1;
	}
	floyd_warshall();
	int cnt = 0;
	for (int i = 1; i < g_N + 1; i++) {
		for (int j = 1; j < g_N + 1; j++) {
			if (!g_graph[i][j] && !g_graph[j][i]) { cnt++; break; }
		}
	}
	cout << (g_N - cnt) << "\n";
}