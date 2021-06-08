// 5398.cpp
// ICPC > Regionals > Europe > Northwestern European Regional Contest > Benelux Algorithm Programming Contest > BAPC 2010 J��
// Ʋ�����ϴ�.
// �̰͵� �̺� ��Ī �����̴�. ���� minimum vertex cover ������ �ľ��ϴ� �����̱⵵ �ϴ�.
// ���� �ܾ�� ���� �ܾ��� ��ġ�� ��ġ�� ���ڰ� �ٸ� ��� �浹�� �߻��ϰ� �浹 ��ġ�� ��ǥ�� �ε����� �̺� �׷����� �����.
// ������� �̺� �׷����� �̺� ��Ī�� �ϰ� �̺� ��Ī�� ����ŭ �浹�� �߱��ϴ� �ܾ��̹Ƿ� ��ü �ܾ� ������ �� �ܾ���� ����
// ������ �ȴ�.
// �� �� �̺� ��Ī�� ����� minimum vertex cover�� �ȴ�.(��Ī�� ������ŭ�� �ܾ�� ��� �浹�� ����� ���� ����� �� �� �ִ�)
// �Ǽ��� ��)
// ���� �ܾ��� y��ǥ�� ���� x ��ǥ�� �ٸ� ��� ���� �ٸ� �ܾ�� ó���ؾ� �ϴµ� �̸� ���� �� �ܾ�� ó���ؼ� Ʋ�ȴ�!!!
// (���� �ܾ��� ��쵵 ���������� �� �� �Ͽ���.) ���� �ٸ� �ܾ ���� �ܾ�� ��������� �̺и�Ī ��� ��ü�� �ٸ��� ���´�!!!
// �ܾ��� ���� ��ǥ�� ��ü�� ������ �̺� �׷����� ����� �̷� �Ǽ��� �ϰ� �ǰ�, �ܾ�� ��� ���� �ٸ��� index���� �ξ,
// �� ���δܾ��� index��, ���δܾ��� index������ �̺� ��Ī�� �ǽ��ؾ� �Ѵ�.
// ���ѽð� 1�� �� 120ms(22,116KB)�� �ҿ�Ǿ���.
// ������� 46/113�� ���� 40.70%�� rank�Ǿ���.

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
#include <algorithm> // sort, max, min, copy, swap, unique, fill
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
char g_tbl[2001][2001];
int g_index[2001][2001];

bool dfs(int from)
{
	for (int to : g_graph[from]) {
		if (g_visited[to]) continue;
		else g_visited[to] = true;
		if (g_matched[to] == -1 || dfs(g_matched[to])) {
			g_matched[to] = from;
			return true;
		}
	}
	return false;
}

void doTest()
{
	int H, V;
	cin >> H >> V;
	int range = max(H, V);
	fill(&g_tbl[0][0], &g_tbl[2000][2001], 0);
	fill(&g_index[0][0], &g_index[2000][2001], 0);
	int x, y;
	string str;
	for (int i = 1; i < H + 1; i++) { // ���� word �Է�
		cin >> x >> y;
		cin >> str;
		for (int j = 0; j < str.length(); j++) {
			g_tbl[y][x + j] = str[j];
			g_index[y][x + j] = i;
		}
	}
	g_graph.resize(range + 1);
	for (int i = 1; i < V + 1; i++) { // ���� word �Է�
		cin >> x >> y;
		cin >> str;
		for (int j = 0; j < str.length(); j++) {
			if (!g_tbl[y + j][x]) g_tbl[y + j][x] = str[j];
			else { // �浹 �߻�!
				if (g_tbl[y + j][x] != str[j]) g_graph[g_index[y + j][x]].push_back(i);
			}
		}
	}
	int count = 0;
	g_matched.assign(range + 1, -1);
	for (int i = 0; i < range + 1; i++) {
		g_visited.assign(range + 1, false);
		if (dfs(i)) count++;
	}
	cout << (H + V) - count << "\n"; // Minumum Vertex Cover
	g_graph.clear();
}

int main()
{
	FAST;
	int T;
	cin >> T;
	while (T--) doTest();
}