// 1760.cpp
// N-Rook
// Olympiad > Central European Olympiad in Informatics > CEOI 2002 5��
// ü������ �̿��� �̺�Ž��, �̺и�Ī �����̴�.
// '9525 ���ġ'�� ������ �����ε�, ������ �ϳ� �� �߰��� ���� �ٸ���.
// ������ �Ӽ��� ���� �׷쿡 ���ϳ� ��Ī���� ���� �� ���ٴ� ���̴�.
// �׷��� ��Ī �� ���� �� �ϳ��� �����̸� ��Ī���� ���ܽ�Ű�� �ȴ�.
// ���ѽð� 2�� �� 0ms(2,332KB)�� �ҿ�Ǿ���.
// ������� 67/281�� ���� 23.84%�� rank�Ǿ���.

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
	int option; // ��ֹ� Ÿ��, 0 : ��ĭ, 1 : ����, 2 : ��
	group() : g1(0), g2(0), option(0) {}
	group(int g1, int g2, bool o) : g1(g1), g2(g2), option(o) {}
};

int main()
{
	FAST;
	int N, M;
	cin >> N >> M;
	vector<vector<group>> chess(N + 1, vector<group>(M + 1, { 0, 0, 0 }));
	for (int i = 1; i < N + 1; i++) { // chess�� option �Է�
		for (int j = 1; j < M + 1; j++)
			cin >> chess[i][j].option;
	}

	// ���� �׷� �Է�
	bool gflag = false;
	int g1cnt = 0;
	for (int i = 1; i < N + 1; i++) {
		gflag = false; if (chess[i][1].option == 0 || chess[i][1].option == 1) g1cnt++;
		for (int j = 1; j < M + 1; j++) {
			if (chess[i][j].option == 2) gflag = true;
			else {
				if (gflag) { gflag = false; g1cnt++; }
				chess[i][j].g1 = g1cnt;
			}
		}
	}
	// ���� �׷� �Է�
	int g2cnt = 0;
	for (int j = 1; j < M + 1; j++) {
		gflag = false; if (chess[1][j].option == 0 || chess[1][j].option == 1) g2cnt++;
		for (int i = 1; i < N + 1; i++) {
			if (chess[i][j].option == 2) gflag = true;
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
		for (int j = 1; j < M + 1; j++) {
			if (chess[i][j].option == 0) g_graph[chess[i][j].g1].push_back(chess[i][j].g2);
		}
	}
	int answer = 0;
	for (int i = 1; i < g1cnt + 1; i++) {
		g_visited = vector<bool>(g2cnt + 1, false);
		if (dfs(i)) answer++;
	}
	cout << answer << "\n";
}