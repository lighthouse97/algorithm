// 1014.cpp
// ����
// Contest > Google Code Jam > Google Code Jam 2008 > Round 3 C1��
// '11014 ���� 2'�� ������ �����̴�. ���� N ���� �� ����.
// ���� �̺� ��Ī ������ '11014 ���� 2' �ҽ��� �״�� ������ �ᵵ Ǯ��������
// �̺� ��Ī �˰������� ���� �˰��� ��� Hopcroft-Karp �˰����� ����ؼ� Ǯ��ڴ�.
// ���ѽð� 2�� �� 0ms(2,028KB)�� �ҿ�Ǿ���.
// ������� 333/1000�� ���� 33.30%�� rank�Ǿ���.

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

struct info {
	int row, col;
	bool exist;
	info() : row(0), col(0), exist(false) {}
	info(int r, int c, bool e) : row(r), col(c), exist(e) {}
};

vector<vector<int>> g_graph;
vector<int> g_A, g_B;
vector<int> g_levA;
int g_N;
vector<info> g_seat;

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

int canCunning(int row, int col, int maxr, int maxc)
{
	int n = maxr, m = maxc;
	if (row < 1 || row > n || col < 1 || col > m) return -1;
	int loc = (row - 1) * m + col;
	return g_seat[loc].exist ? loc : -1;
}

void doTest()
{
	int n, m, count = 0, no_seat = 0;
	cin >> n >> m;
	g_N = n * m;
	g_graph.assign(g_N + 1, {});
	g_A.assign(g_N + 1, -1);
	g_B.assign(g_N + 1, -1);
	g_levA.assign(g_N + 1, -1);
	g_seat.resize(g_N + 1, { 0, 0, 0 });

	char s;
	for (int i = 1; i < n + 1; i++) { // �¼� ���� �Է�
		for (int j = 1; j < m + 1; j++) {
			cin >> s;
			g_seat[(i - 1)*m + j] = { i, j, (s == '.' ? true : false) };
		}
	}
	vector<int> left;
	left.push_back(0); // 1���� ����
	for (int i = 1; i < n * m + 1; i++) { // ��ü ���̺��� ¦������ ����
		if (g_seat[i].exist) {
			if (!(g_seat[i].col % 2)) left.push_back(i);
		}
		else no_seat++;
	}
	int cn; // �� �ڸ����� ���� �¼��� Ŀ�� ���θ� üũ�Ͽ� �̺� �׷��� ����
	for (int i = 1; i < (int)left.size(); i++) { // left ������ ���ҿ��� 6���� �������� cunning ���� üũ		
		cn = canCunning(g_seat[left[i]].row - 1, g_seat[left[i]].col - 1, n, m); // ���� ��
		if (cn > 0) g_graph[left[i]].push_back(cn);
		cn = canCunning(g_seat[left[i]].row, g_seat[left[i]].col - 1, n, m); // ����
		if (cn > 0) g_graph[left[i]].push_back(cn);
		cn = canCunning(g_seat[left[i]].row - 1, g_seat[left[i]].col + 1, n, m); // ������ ��
		if (cn > 0) g_graph[left[i]].push_back(cn);
		cn = canCunning(g_seat[left[i]].row, g_seat[left[i]].col + 1, n, m); // ������
		if (cn > 0) g_graph[left[i]].push_back(cn);
		cn = canCunning(g_seat[left[i]].row + 1, g_seat[left[i]].col + 1, n, m); // ������ �Ʒ�
		if (cn > 0) g_graph[left[i]].push_back(cn);
		cn = canCunning(g_seat[left[i]].row + 1, g_seat[left[i]].col - 1, n, m); // ���� �Ʒ�
		if (cn > 0) g_graph[left[i]].push_back(cn);
	}
	int maxMatch;
	maxMatch = hopcroft_karp(); // �̺� ��Ī
	cout << (g_N - no_seat - maxMatch) << "\n"; // ��ü �ڸ� - ���� �� ���� �ڸ� - ���� �� �� �ִ� �ڸ� = �ִ� ���� �� �� ���� �ڸ�
}

int main()
{
	FAST;
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) doTest();
}