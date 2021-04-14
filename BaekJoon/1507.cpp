// 1507.cpp
// �ñ��� ��ȣ
// Floyd-Warshsll ���빮���̴�.
// �̹� Floyd-Warshsll�� ������ ����� �ѹ� �� Floyd-Warshsll�� �����鼭 �� �������� ���Ŀ� ������ ������ ������Ʈ �Ѵ�.
// ��� �� �������� �������� ���� �ð��� ���� ��� ������ �� �� ���� �켱���� ������Ʈ�Ѵ�.
// �ֳ�? ������ ������ �ּҰ� �Ǿ�� �ϴ� ������ �ٱ� ������, 1->3���� �� �� 1->3�� �ð��� 1->2, 2->3�� �ð��� ������ 1->3 ���δ� �ʿ���� �����̴�.
// �̸� ���� ������ ���̸� �����ϴ� ���̺��� �ϳ� �� �����.
// 1) ���� �ð��� ������ ������ �� ���� ����
// 2) ���� �ð��� �� �� ���� �ִ� ��ΰ� �ƴϹǷ� ���
// 3) ���� �ð��� �� ª�� ��ΰ� ������ ��� ���ð��� �ּ� �̵� ��θ� ���صξ��ٴ� ������ ���ǿ� ���� �ǹǷ�, �Ұ���(-1) ���!
// ����� �� ���̺��� ����� ���� 1�� ��� ����� �̵� �ð��� ���� ���ϸ� �ȴ�.
// ���ѽð� 2�� �� 0ms(2,020KB)�� �ҿ�Ǿ���.
// ������� 1057/1599�� ���� 66.10%�� rank�Ǿ���.

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

vector<vector<int>> g_graph; // �ִ� �ð�
vector<vector<int>> g_path; // ��μ�
int g_N;
bool g_failure = false;

void floyd_warshall()
{
	for (int k = 1; k < g_N + 1; k++) {
		for (int i = 1; i < g_N + 1; i++) {
			for (int j = 1; j < g_N + 1; j++) {
				if (g_graph[i][k] + g_graph[k][j] == g_graph[i][j]) {
					if (g_path[i][k] + g_path[k][j] > g_path[i][j]) g_path[i][j] = g_path[i][k] + g_path[k][j];
				}
				else if (g_graph[i][k] + g_graph[k][j] < g_graph[i][j]) {
					g_failure = true;
					return;
				}
			}
		}
	}
}

int main()
{
	FAST;
	cin >> g_N;
	g_graph.resize(g_N + 1, vector<int>(g_N + 1, 0));
	g_path.resize(g_N + 1, vector<int>(g_N + 1, 1));
	for (int i = 1; i < g_N + 1; i++) {
		for (int j = 1; j < g_N + 1; j++) {
			cin >> g_graph[i][j];
			if (i == j) g_path[i][j] = 0;
		}
	}
	floyd_warshall();
	int sum = 0;
	if (g_failure) cout << -1 << "\n";
	else {
		for (int i = 1; i < g_N + 1; i++)
			for (int j = i + 1; j < g_N + 1; j++) // �ߺ�����, i+1���� ����
				sum += (g_path[i][j] == 1 ? g_graph[i][j] : 0);
		cout << sum << "\n";
	}
}