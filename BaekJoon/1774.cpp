// 1774.cpp
// ���ֽŰ��� ����
// �ּҽ���Ʈ��(MST)���� kruskal �˰������� Ǭ��.
// 4386(���ڸ������)�� ���� �����ϰ� Ǫ�µ�, ������ ����� ������
// �ֱ� ������ �̸� �̸� �۾��� �ΰ� ó���Ѵ�.
// Olympiad > USA Computing Olympiad > 2007-2008 Season > USACO December 2007 Contest > Silver 2��
// ���ѽð� 2�� �� 64ms(14480KB)�� �ҿ�Ǿ���.
// ������� 499 �� 197�� ���� 39.47%�� rank�Ǿ���.
// --> ����ȭ�� �Ͽ� vector, std::sort�� ���� ������ ���� priority_queue�� ����ؼ� �����ϴ� ������ �ٲپ���.
//     (�������� Ǯ�̹�� ����), �̷��� Ǫ�� 20ms(14476KB)�ҿ�Ǿ���. ���� ��� 499 �� 16�� ���� 3.20%�� rank�Ǿ���.
//     �� ���������� sort���� priority_queue�� �� ���� ������ ���ٴ� ���� �� �� �ִ�.
//     �߰��� prim algorithm���� Ǯ�� �� ������ �� ���� �� �ִ�.
//     sort�� (��� O(nlogn), �־� O(n^2))������ priority_queue�� �׻� O(nlogn)���� ���´�.
/// ����! -> �Ÿ� ����� �� ������ ���� �ſ� Ŭ �� �ֱ� ������ long long���� �����ؾ� �Ѵ�.(�̰� ������ ��û���� Ʋ�ȴ�!!!)

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <cmath> // pow, sqrt
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
	int start;
	int end;
	double value;
	vertex() {}
	vertex(int s, int e, double v) : start(s), end(e), value(v) {}
};

struct compare {
	bool operator() (const vertex& l, const vertex& r) const
	{
		return (l.value > r.value); // greater than, ��������
	}
};

int N, M;
priority_queue<vertex, vector<vertex>, compare> GRAPH;
vector<int> DJS;

int find_djs(int item)
{
	if (DJS[item] == item) return item;
	else
		return DJS[item] = find_djs(DJS[item]);
}

bool union_djs(int s1, int s2)
{
	int r1, r2;
	r1 = find_djs(s1);
	r2 = find_djs(s2);
	if (r1 == r2) return false; // already same set!
	else
		DJS[r2] = r1;
	return true;
}

void kruskal()
{
	int count = 0, start, end;
	double minval = 0.0;
	vertex select;
	// ���� ����� ���� ó��
	for (int i = 0; i < M; i++) {
		cin >> start >> end;
		if (union_djs(start, end)) count++;
	}
	while (!GRAPH.empty()) {
		select = GRAPH.top();
		GRAPH.pop();
		if (count >= N - 1) break;
		if (union_djs(select.start, select.end)) {
			count++;
			minval += select.value;
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

	long long t1, t2;
	double dist;
	vector<vector<int>> stars;
	cin >> N >> M;
	DJS.resize(N + 1);
	for (int i = 0; i <= N; i++) DJS[i] = i;
	// coordinate �Է�
	stars.resize(N + 1, vector<int>(2, 0));
	for (int i = 1; i <= N; i++) {
		cin >> stars[i][0] >> stars[i][1];
	}
	// ���������Է�
	for (int i = 1; i <= N - 1; i++) {
		for (int j = i + 1; j <= N; j++) {
			t1 = stars[j][0] - stars[i][0]; // diff x
			t2 = stars[j][1] - stars[i][1]; // diff y
			dist = sqrt(t1*t1 + t2*t2);
			GRAPH.push(vertex(i, j, dist));
		}
	}
	kruskal();
}
