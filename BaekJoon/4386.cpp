// 4386.cpp
// ���ڸ� �����
// ���ڸ� ��ǥ ����Ʈ�� ������ �������� ������ ������ ����
// MST(Minimal Spanning Tree)�� Ǫ�� �����̴�.
// Kruskal algorithm���� Ǯ ��ȹ�̴�.
// Contest > Waterloo's local Programming Contests > 23 September, 2000 A���� �����Ǿ��� �����̴�.
// ���ѽð� 1�� �� 0ms(2324KB)�� �ҿ�Ǿ���.
// ������� 630 �� 363�� ���� 57.61%�� rank�Ǿ���.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <cmath> // pow, sqrt
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
	float value;
	vertex() {}
	vertex(int s, int e, float v) : start(s), end(e), value(v) {}
};

bool compare(const vertex& a, const vertex& b) { return (a.value < b.value); }

int N, E;
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
	int count = 0;
	float minval = 0.0;
	vertex x;
	sort(GRAPH.begin(), GRAPH.end(), compare);
	for (int i = 0; i < E; i++) {
		x = GRAPH[i];
		if (count >= N - 1) break;
		if (find_djs(x.start) != find_djs(x.end)) {
			union_djs(x.start, x.end);
			count++;
			minval += x.value;
		}
	}
	cout << fixed;
	cout.precision(2);
	cout << minval << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	float x, y, dist, p = 2.0;
	vector<vector<float>> stars;
	cin >> N;
	DJS.resize(N + 1);
	for (int i = 0; i <= N; i++) DJS[i] = i;
	// coordinate �Է�
	stars.resize(N + 1, vector<float>(2, 0.0));
	for (int i = 1; i <= N; i++) {
		cin >> x >> y;
		stars[i] = { x, y };
	}
	// ���������Է�
	for (int i = 1; i <= N - 1; i++) {
		for (int j = i + 1; j <= N; j++) {
			dist = pow(stars[j][0] - stars[i][0], p) + pow(stars[j][1] - stars[i][1], p);
			dist = sqrt(dist);
			GRAPH.push_back(vertex(i, j, dist));
		}
	}
	E = GRAPH.size();
	kruskal();
}