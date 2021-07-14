// 1516.cpp
// ���� ����
// �������� �������� �����̴�.
// �ٷ� Ǯ���!!!
// ������ ����� �������� ���ߴ�. �׸��� �ݷʸ� ����� �ɷµ� ���� ���� �����ϴ�!!!
// �� ������ ������ ������ ��� �� �� ������ �ҿ� �ð��� �ڽ��� ���� �� ���� �ð���
// ���� �ɸ��� ������ �ð��� �ڽ��� �ð��� ���ؾ� �Ѵ�.
// �ֳ��ϸ� �ٷ� ���� ���� ������ ��� ��������� ��μ� �ڽ��� ������� �� �ֱ� �����̴�.
// ���ѽð� 2�� �� 4ms(2,420KB)�� �ҿ�Ǿ���.
// ������� 980/3748�� ���� 26.14%�� rank�Ǿ���.

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
#include <algorithm> // sort, max, min, copy, swap, unique
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
vector<int> g_degree;
int g_N = 0;
///
vector<int> g_time;
vector<int> g_answer;

void topological_sort()
{
	queue<int> myq;
	for (int i = 1; i < g_N + 1; i++)
		if (g_degree[i] == 0) { myq.push(i); g_answer[i] = g_time[i]; }
	int cur;
	while (!myq.empty()) {
		cur = myq.front(); myq.pop();
		for (int to : g_graph[cur]) {
			g_degree[to]--;
			g_answer[to] = max(g_answer[to], g_answer[cur] + g_time[to]);
			if (g_degree[to] == 0)
				myq.push(to);
		}
	}
}

int main() {
	FAST;
	int N;
	cin >> N;
	g_graph.resize(N + 1);
	g_degree.resize(N + 1, 0);
	g_N = N;
	int t, b;
	g_time.resize(g_N + 1, 0);
	g_answer.resize(g_N + 1, 0);
	for (int i = 1; i < g_N + 1; i++) {
		cin >> t;
		g_time[i] = t;
		while (1) {
			cin >> b;
			if (b == -1) break;
			g_graph[b].push_back(i);
			g_degree[i]++;
		}
	}
	topological_sort();
	for (int i = 1; i < g_N + 1; i++)
		cout << g_answer[i] << "\n";
}