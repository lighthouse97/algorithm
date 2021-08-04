// 1199.cpp
// ���Ϸ� ȸ��(Euler Circuit)
// ���Ϸ� ȸ���� ��θ� ���ϴ� �����̴�.
// ���Ϸ� ȸ�� Ž���� �� ���� �������� ������ Ž���� ������ ������ �������� ������,
// TLE�� �߻��Ѵ�.
// �� �� �����ؾ� �Ѵ�!!!
// ���ѽð� 3�� �� 724ms(367,324KB)�� �ҿ�Ǿ���.
// ������� 19/130�� ���� 14.61%�� rank�Ǿ���.

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
vector<int> g_record; // ���� ���� ���� ���� ����
///
vector<int> g_ecpath; // euler circuit path

void eulerc(int curr) // ���Ϸ� ȸ�� Ž��
{
	for (int& i = g_record[curr]; i < (int)g_graph[curr].size(); i++) { // TLE�� ���� ���� ���� �������� �̸� ����
		int& cnt = g_graph[curr][i];
		if (cnt > 0) {
			cnt--;
			g_graph[i][curr]--;
			eulerc(i);
		}
	}
	g_ecpath.push_back(curr); // ��� ����
}

int main()
{
	FAST;
	int N;
	cin >> N;
	g_graph.resize(N + 1, vector<int>(N + 1, 0));
	g_record.resize(N + 1, 1);
	int degree = 0;
	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < N + 1; j++) {
			cin >> g_graph[i][j];
			degree += g_graph[i][j];
		}
		if (degree % 2) { // ������ ������ ¦���̾�� ��
			cout << -1 << "\n";
			return 0;
		}
		degree = 0;
	}
	eulerc(1);
	for (int x : g_ecpath) cout << x << " ";
	cout << "\n";
}