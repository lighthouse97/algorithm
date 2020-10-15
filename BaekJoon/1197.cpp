// 1197.cpp
// �ּ� ���д� Ʈ��
// �̹����� �� ������ ����ġ�� �ִ� ��쿡
// �ּ� ���� Ʈ��(MST)�� ���Ѵ�.
// Kruskal algorithm�� Prim algorithm ������ ���ؼ� ���ؼ�
// �� �ð��� ���� ����.
// ���� Kruskal algorithm���� ���غ���.
// ���ѽð� 2�� �� 36ms(3316KB)�� �ҿ�Ǿ���.
// ������� 3927 �� 64�� ���� 1.62%�� rank�Ǿ���.
// �׷������� ������ ���� ��� �׷���(Sparse Graph)�� ��� Kruskal algorithm�� �����ϰ�,
// �׷������� ������ ���� ���� �׷���(Dense Graph)�� ��� Prim algorithm�� �����ϴ�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
//#include <queue> // queue, priority_queue

using namespace std;

struct vertex {
	int start;
	int end;
	int value;
	vertex() {}
	vertex(int s, int e, int v) : start(s), end(e), value(v) {}
};

bool compare(const vertex& a, const vertex& b) { return (a.value < b.value); }

int V, E;
vector<vertex> GRAPH;
vector<int> DJS;

int find_djs(int item)
{
	if (DJS[item] == item) return item;
	else
		return DJS[item] = find_djs(DJS[item]);
}

void union_djs(int s1, int s2)
{
	int r1, r2;
	r1 = find_djs(s1);
	r2 = find_djs(s2);
	if (r1 == r2) return; // already same set!
	else
		DJS[r2] = r1;
}

void kruskal()
{
	int count = 0, minval = 0;
	vertex x;
	sort(GRAPH.begin() + 1, GRAPH.end(), compare);
	for (int i = 1; i <= E; i++) {
		x = GRAPH[i];
		if (count >= V - 1) break;
		if (find_djs(x.start) != find_djs(x.end)) {
			union_djs(x.start, x.end);
			count++;
			minval += x.value;
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
	GRAPH.resize(E + 1);
	DJS.resize(V + 1);
	for (int i = 0; i <= V; i++) DJS[i] = i;
	for (int i = 1; i <= E; i++) {
		cin >> a >> b >> c;
		GRAPH[i] = vertex(a, b, c);
	}	
	kruskal();
}