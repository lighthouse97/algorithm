// 3683.cpp
// ����̿� ��
// ICPC > Regionals > Europe > Northwestern European Regional Contest > NWERC 2008 C��
// ������ ���� ����� ��������. ��� Ǫ���� ������ ���� ���ߴ�. �ᱹ ���� Ǯ�̸� �ڼ��� �о�Ҵ�.
// �׷��� �� ������ ���� Ǭ ���� �ƴϴ�!
// ������ �� �о�� ������ �� ���캸�� ��ǥ�ϴ� ��� �߿��� �浹�� �߻��ϴ� ��찡 �����.
// ���� ��� ���1�� C1�� �����ߴµ� ���2�� C1�� ����߸��� ����̴�.
// �� ���1�� D1�� ����߸��µ� ���3�� D1�� �����ϴ� ��쵵 �ִ�.
// �̷��� �浹�� �߻��ϴ� ����鳢�� �̺� �׷����� ������ �ش�.
// �� �� �̺� �׷����� ������ ����̸� �����ϴ� ���, �������� ���� �����ϴ� ������� �з��Ѵ�.
// ����̸� �����ϴ� ����� �浹�� �߻��� ���� ����, ���� �����ϴ� ����� �浹�� �߻��Ҹ��� ���� ������
// �̷��� �̺� �׷����� ������ ���� �ִ�.
// ������ �̺� ��Ī�� ���� �ִ� ��Ī�� ���Ѵ�.
// �� �� �ִ� ��Ī�� ��(����)��ŭ�� ����� �浹�� ����Ű�� ��� ��츦 �����ϹǷ� ��ü ��������� ���ָ�
// ��ǥ�� �ݿ��Ǵ� ������� �ִ밪�� �ȴ�.
// �� ��  �ִ� ��Ī�� ��(����)��ŭ�� ��� ���� Minimum Vertex Cover�� �ȴ�.
// �ֳ��ϸ� Minimum Vertex Cover�� ���ϴ� ����(���)�� ��� ����(�浹�� ����Ű�� ����)�� ����Ǳ� �����̴�.
// ���ѽð� 1�� �� 28ms(2,276KB)�� �ҿ�Ǿ���.
// ������� 93/144�� ���� 64.58%�� rank�Ǿ���.

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
//#include <algorithm> // sort, max, min, copy, swap, unique, fill
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

void doTest()
{
	int c, d, v;
	cin >> c >> d >> v;
	g_graph.resize(v + 1);
	vector<vector<string>> vote(v + 1, vector<string>(2));
	for (int i = 1; i < v + 1; i++)
		cin >> vote[i][0] >> vote[i][1]; // ��ǥ �Է�

	for (int i = 1; i < v; i++) { // �̺� �׷��� ����
		for (int j = i + 1; j < v + 1; j++) {
			if (!vote[i][0].compare(vote[j][1]) || !vote[i][1].compare(vote[j][0])) { // �浹�߻�
				if (vote[i][0].at(0) == 'C') g_graph[i].push_back(j); // �̺� �׷��� ������ ����� ����, �������� �� �������� ���´�.
				else g_graph[j].push_back(i);
			}
		}
	}
	int count = 0;
	g_matched.assign(v + 1, 0); // �̺� Ž��
	for (int i = 1; i < v + 1; i++) {
		g_visited.assign(v + 1, false);
		if (dfs(i)) count++;
	}
	cout << (v - count) << "\n";
	g_graph.clear();
}

int main() {
	int T;
	cin >> T;
	while (T--) doTest();
}