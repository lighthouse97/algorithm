// 1197_1.cpp
// �ּ� ���д� Ʈ��
// �̹����� prim algorithm���� Ǯ���.
// prim algorithm���� Ǫ�� 52ms(6588KB)�� �ҿ�Ǿ���.
// (prim���� ���ʿ��� queue�� ���ְ� �� �� ������ ����ȭ��Ű�� 48ms(6588KB)�� �� �پ���.)
// Kruskal algorithm(36ms(3316KB))�� ���� �ð��� �� ���� �ɷȴ�.
// �׷������� ������ ���� ��� �׷���(Sparse Graph)�� ��� Kruskal algorithm�� �����ϰ�,
// �׷������� ������ ���� ���� �׷���(Dense Graph)�� ��� Prim algorithm�� �����ϴ�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
#include <queue> // queue, priority_queue

using namespace std;

struct vertex {
	int name;
	int value;
	vertex() {}
	vertex(int n, int v) : name(n), value(v) {}
};

struct compare {
	bool operator() (const vertex& l, const vertex& r) const
	{
		return (l.value > r.value);
	}
};

int V, E;
vector<vector<vertex>> GRAPH;
vector<int> VISITED;

void prim()
{
	long long minval = 0;
	vertex select;
	priority_queue<vertex, vector<vertex>, compare> mypq;
	
	mypq.push(vertex(1, 0));
	while (!mypq.empty()) {
		select = mypq.top();
		mypq.pop();
		if (!VISITED[select.name]) {
			VISITED[select.name] = 1;
			minval += select.value;
			for (vertex x : GRAPH[select.name]) {
				if (!VISITED[x.name]) mypq.push(x);
			}
		}
	}
	cout << minval << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int a, b, c;
	cin >> V >> E;
	GRAPH.resize(V + 1); // V+1�ε� E+1���켭 "��Ÿ�� ����"�� �����ȴ�.
	VISITED.resize(V + 1, 0);
	for (int i = 1; i <= E; i++) {
		cin >> a >> b >> c;
		GRAPH[a].push_back(vertex(b, c));
		GRAPH[b].push_back(vertex(a, c));
	}
	prim();
}