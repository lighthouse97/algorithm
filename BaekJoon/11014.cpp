// 11014.cpp
// ���� 2
// "�̺� �׷������� �ִ� ��Ī + �ִ� ���� ���� = ���� ����" ������ ����Ͽ� Ǫ�� ����
// ��� �Ѵ�.
// ���ϴ� ����� ������ ����.
// 1) ��ü �¼��� �迭�� �����(�� �¼����� row, column, exist�� ������ ����)
// 2) ��ü �¼����� �����ϴ� �¼�(.ǥ��) �� ¦����(Ȥ�� Ȧ����)���� �̺� �׷����� left �迭�� �ִ´�.
//    (Ȧ�������� Ȥ�� ¦���������� ����� Ŀ���� �� �� ���� �����̴�)
// 3) left �迭�� �� ���ҿ��� 6�������� Ŀ�� ���θ� üũ�Ͽ� Ŀ���� ������ �ڸ��� �׷����� �ش� �ε����� �߰��Ѵ�.
// 4) �̺� �׷����� �ϼ��Ǹ� �׷��� ��ü�� ���ؼ� �̺� �׷����� �ִ� ��Ī(dfs)�� ������.
// 5) ���⼭ ���� ī��Ʈ���� �ִ�� ������ �� �ִ� �ּ��� �ο����̰� �� �ּ� ���ؽ� Ŀ���� ���� �ȴ�.
// 6) ��ü �л� ������ ���� �� ���� �ڸ��� �����ϰ� ������ �ڸ����� 5)�� ī��Ʈ�� ���� Ŀ���� �� �� ���� �ִ����� �л����� ��������.
//    �� �� ���� ����� �������� �ִ� ���� ������ ���� �ȴ�.
// ��Ե� ����� ����� �̺� �׷����� �����. �ִ� ��Ī�� �ּҷ� ��ü ������ �� �ִ� �ڸ��̹Ƿ�
// �� �ڸ��� �� �������� �ִ� ���� �����̰� �� �ִ� ���� ������ ������ ���ϸ� �ȴ�.
// Contest > Google Code Jam > Google Code Jam 2008 > Round 3 C2��
// ���ѽð� 2�� �� 16ms(2,504KB)�� �ҿ�Ǿ���.
// ������� 25/275�� ���� 9.09%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs, hypot, round
#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct info {
	int row, col;
	bool exist;
};

vector<vector<int>> g_graph;
vector<bool> g_visited;
vector<int> g_matched;
int g_n, g_m;
vector<info> g_seat;

bool dfs(int from)
{
	for (int to : g_graph[from]) {
		if (!g_visited[to] && !g_matched[to]) {
			g_visited[to] = true;
			g_matched[to] = from;
			return true;
		}
	}
	for (int to : g_graph[from]) {
		if (!g_visited[to]) {
			g_visited[to] = true;
			if (!g_matched[to] || dfs(g_matched[to])) {
				g_matched[to] = from;
				return true;
			}
		}
	}
	return false;
}

int canCunning(int row, int col)
{
	if (row < 1 || row > g_n || col < 1 || col > g_m) return -1;
	int loc = (row - 1) * g_m + col;
	return g_seat[loc].exist ? loc : -1;	
}

void do_test()
{	
	int n, m, count = 0, no_seat = 0;	

	cin >> g_n >> g_m;
	n = g_n; m = g_m;
	
	g_seat.resize(n * m + 1, { 0, 0, 0 }); // row���� col���� �������� 1 ~ n*m ��ȣ �ű��.
	char s;	
	// �¼� ���� �Է�
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < m + 1; j++) {
			cin >> s;			
			g_seat[(i - 1)*m + j] = { i, j, (s == '.' ? true : false) };
		}
	}
	vector<int> left;
	// �¼��� �ְ� ¦�����̸� left�� �ִ´�.
	for (int i = 1; i < n * m + 1; i++) {
		if (g_seat[i].exist) {
			if (!(g_seat[i].col % 2)) left.push_back(i);			
		}
		else no_seat++;
	}
	left.insert(left.begin(), 0); // index 1 ���� ����	
	g_graph.resize(n * m + 1);
	g_visited.resize(n * m + 1, false);
	g_matched.resize(n * m + 1, 0);
	// �� �ڸ����� ���� �¼��� Ŀ�� ���θ� üũ�Ͽ� �̺� �׷��� ����
	int cn;
	for (int i = 1; i < (int)left.size(); i++) { // left ������ ���ҿ��� 6���� �������� cunning ���� üũ		
		cn = canCunning(g_seat[left[i]].row - 1, g_seat[left[i]].col - 1); // ���� ��
		if (cn > 0) g_graph[left[i]].push_back(cn);
		cn = canCunning(g_seat[left[i]].row, g_seat[left[i]].col - 1); // ����
		if (cn > 0) g_graph[left[i]].push_back(cn);
		cn = canCunning(g_seat[left[i]].row - 1, g_seat[left[i]].col + 1); // ������ ��
		if (cn > 0) g_graph[left[i]].push_back(cn);
		cn = canCunning(g_seat[left[i]].row, g_seat[left[i]].col + 1); // ������
		if (cn > 0) g_graph[left[i]].push_back(cn);
		cn = canCunning(g_seat[left[i]].row + 1, g_seat[left[i]].col + 1); // ������ �Ʒ�
		if (cn > 0) g_graph[left[i]].push_back(cn);
		cn = canCunning(g_seat[left[i]].row + 1, g_seat[left[i]].col - 1); // ���� �Ʒ�
		if (cn > 0) g_graph[left[i]].push_back(cn);
	}
	// �̺� ��Ī
	for (int i = 1; i < (int)g_graph.size(); i++) {
		g_visited = vector<bool>(g_visited.size(), false);
		if (dfs(i)) count++;
	}
	// "��ü �л� ������ - ���� �� ���� �ڸ� - �̺� ��Ī�� ��"�� (�ִ� ���� ����)���� ������ �� ���� �ִ� �л� ���̴�.
	cout << (n * m - no_seat - count) << "\n";
	// clear all the global vector
	g_graph.clear();
	g_visited.clear();
	g_matched.clear();
	g_seat.clear();
	g_n = g_m = 0;
}

int main()
{
	FAST;

	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		do_test();
	}
}