// 9525.cpp
// �� ��ġ�ϱ�
// ICPC > Regionals > Latin America > Latin America Regional Contests 2013 A��
// '2570 ���2'�� �Ѽ�Ʈ�� ���� Ǯ��� �����̴�.
// �̺� ��Ī��ü�� �����ѵ� �̺� ��Ī�� ���� �̺� �׷��� �����ؾ� �ϴµ� ü������ ���� �̺� �׷��� �����ϴ� �۾���
// ���� �ذ��� 85%�� �����Ѵٰ� ���� �ȴ�.
// '2570 ���2'�� �밢�� �����̰� �� ������ ���� ����/���� ������ ���� �ٸ��� �������� �����ϴ�.
// �׷� ���� ��, �׷��� ������ 'X'(pawn)�̸� '.'�� ���� �� ���� �׷� ī��Ʈ �������� �ʵ��� �ϴ� ���� �߿��ϴ�.
// ���ѽð� 1�� �� 12ms(2,492KB)�� �ҿ�Ǿ���.
// ������� 131/269�� ���� 48.69%�� rank�Ǿ���.

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
#include <string> // string, stoi
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
vector<bool> g_visited;
vector<int> g_matched;

bool dfs(int from)
{
	for (int to : g_graph[from]) {
		if (g_visited[to]) continue;
		else g_visited[to] = true;
		if (g_matched[to] == 0 || dfs(g_matched[to])) {
			g_matched[to] = from;
			return true;
		}
	}
	return false;
}

struct group {
	int g1, g2; // group1, group2
	bool barrier; // ��ֹ� ����
	group() : g1(0), g2(0), barrier(false) {}
	group(int g1, int g2, bool b) : g1(g1), g2(g2), barrier(b) {}
};

int main()
{
	FAST;
	int N;
	cin >> N;
	vector<vector<group>> chess(N + 1, vector<group>(N + 1, { 0, 0, false }));
	string cm; // chessman
	for (int i = 1; i < N + 1; i++) { // ü���� pawn ��ġ �Է�		
		cin >> cm;
		for (int j = 0; j < cm.length(); j++)
			if (cm[j] == 'X') chess[i][j + 1].barrier = true;
	}

	// ���� �׷� �Է�
	bool gflag = false;
	int g1cnt = 0;
	for (int i = 1; i < N + 1; i++) {
		gflag = false; if (!chess[i][1].barrier) g1cnt++;
		for (int j = 1; j < N + 1; j++) {
			if (chess[i][j].barrier) gflag = true;
			else {
				if (gflag) { gflag = false; g1cnt++; }
				chess[i][j].g1 = g1cnt;
			}
		}
	}
	// ���� �׷� �Է�
	int g2cnt = 0;
	for (int j = 1; j < N + 1; j++) {
		gflag = false; if (!chess[1][j].barrier) g2cnt++;
		for (int i = 1; i < N + 1; i++) {
			if (chess[i][j].barrier) gflag = true;
			else {
				if (gflag) { gflag = false; g2cnt++; }
				chess[i][j].g2 = g2cnt;
			}
		}
	}

	// �̺� �׷��� �����
	g_graph.resize(g1cnt + 1);
	g_visited.resize(g2cnt + 1, false);
	g_matched.resize(g2cnt + 1, 0);
	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < N + 1; j++) {
			if (!chess[i][j].barrier) g_graph[chess[i][j].g1].push_back(chess[i][j].g2);
		}
	}
	int answer = 0;
	for (int i = 1; i < g1cnt + 1; i++) {
		g_visited = vector<bool>(g2cnt + 1, false);
		if (dfs(i)) answer++;
	}
	cout << answer << "\n";
}