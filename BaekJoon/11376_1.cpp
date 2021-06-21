// 11376_1.cpp
// ������ȣ 2
// �̺� ��Ī �����ε�, Hopcroft-Karp �˰������� Ǯ��Ҵ�.
// ����ð��� Ȯ���� ������ �Ǿ���.
// N�� ������ �뷫 1000 �̻����� Ŭ���� Hopcroft-Karp �˰����� ū ȿ���� ���Ѵ�.
// 1,348ms(6,096KB) -> 84ms(6,128KB) �� ���� 16�� �̻� �����Ǿ���.
// ���ѽð� 4�� �� 84ms(6,128KB)�� �ҿ�Ǿ���.
// ������� 6/1494�� ���� 0.40%�� rank�Ǿ���.

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
#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_graph;
vector<int> g_A, g_B;
vector<int> g_levA;
int g_N;

void bfs()
{
	queue<int> myq;
	for (int i = 1; i < g_N + 1; i++) {
		if (g_A[i] == -1) { // matching�ȵ� A�������� ����
			g_levA[i] = 0; // matching�ȵ� A������ level 0�̴�.
			myq.push(i);
		}
		else g_levA[i] = -1; // matching �� A ����(), �Ŀ� update���� -1�� ǥ��
	}
	while (!myq.empty()) { // matching�� ������ level update
		int cur = myq.front(); myq.pop();
		for (int b : g_graph[cur]) {
			if (g_B[b] != -1 && g_levA[g_B[b]] == -1) {
				g_levA[g_B[b]] = g_levA[cur] + 1;
				myq.push(g_B[b]);
			}
		}
	}
}

bool dfs(int cur)
{
	for (int b : g_graph[cur]) {
		if (g_B[b] == -1 || (g_levA[g_B[b]] == g_levA[cur] + 1 && dfs(g_B[b]))) {
			g_A[cur] = b;
			g_B[b] = cur;
			return true;
		}
	}
	return false;
}

int hopcroft_karp()
{
	int maxMatch = 0; // ��ü ��Ī ��
	while (true) {
		bfs(); // A ���տ� level ����
		int match = 0; // �� level������ ��Ī ��
		for (int i = 1; i < g_N + 1; i++)
			if (g_A[i] == -1 && dfs(i)) match++; // A���� match�� �ȵ� �������� dfs Ž��
		if (match == 0) break; // dfs���� match�� �����ϸ� �� Ž���� �ʿ� �����Ƿ� �˰��� ����
		maxMatch += match;
	}
	return maxMatch;
}

int main()
{
	FAST;
	int n, m;
	cin >> n >> m;
	g_N = n;
	g_graph.resize(g_N + 1);
	g_A.resize(m + 1, -1);
	g_B.resize(m + 1, -1);
	g_levA.resize(g_N + 1, -1);
	int cnt, jn;
	for (int i = 1; i < g_N + 1; i++) {
		cin >> cnt;
		for (int j = 0; j < cnt; j++) {
			cin >> jn;
			g_graph[i].push_back(jn);
		}
	}
	int maxMatch = 0;
	maxMatch = hopcroft_karp();
	g_A.assign(g_N + 1, -1); // reset A set
	maxMatch += hopcroft_karp(); // A[]�� �ʱ�ȭ �ϰ� �ѹ� �� ����.
	cout << maxMatch << "\n";
}