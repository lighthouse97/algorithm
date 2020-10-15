// 1766.cpp
// ������
// ���� ���������� �̿��ϴµ� ���� ���ظ� �� �ؾ� �Ѵ�.
// �־��� �����ָ����� ��� ������ Ǯ �� �ִٴ� ������ �ִµ�
// ó���� �̸� �����ϰ� �־��� �������� ������ Ǯ �� �ִ� �Ϻζ��
// �����ϰ� �̸� ������ ������ Ǯ���� �ϴ� �ڲ� ����Ŭ�� ���ͼ� ������ Ǯ �� ������!!!
// �� ������ �־��� �����ָ� ������ ���� ���� �ϸ鼭 ť�� �������� �Է��� �� ���
// ���� ���� ���� ���� ó���ϸ� �ȴ�.
// �̸� ���ؼ��� �켱 ���� ť�� ����Ѵ�.
// ������ ����� �����ϰ� ���� ���� ������ �̿��ؼ� �ʹ��ʹ� ���� Ǯ �� �ִ� �����̴�.
// ���ѽð� 2�� �� 28ms(3904KB)�� �ҿ�Ǿ���.
// ������� 13/2247�� ���� 0.57%�� rank�Ǿ���.

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
#include <queue> // queue, priority_queue

using namespace std;

struct compare {
	bool operator() (const int& l, const int& r) const
	{
		return (l > r); // increasing order
	}
};

int g_N;
vector<vector<int>> g_graph;
vector<int> g_degree;

void topological_sort()
{
	priority_queue<int, vector<int>, compare> myq;
	int pick;
	for (int i = 1; i <= g_N; i++) {
		if (g_degree[i] == 0)
			myq.push(i);
	}
	while (!myq.empty()) {
		pick = myq.top();
		myq.pop();
		cout << pick << " ";
		for (int x : g_graph[pick]) {
			g_degree[x]--;
			if (g_degree[x] == 0)
				myq.push(x);
		}
	}
	cout << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int M, a, b;
	cin >> g_N;
	g_graph.resize(g_N + 1);
	g_degree.resize(g_N + 1, 0);
	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		g_graph[a].push_back(b);
		g_degree[b]++;
	}
	topological_sort();
}