// 2887_p.cpp
// �༺ �ͳ�
// Kruskal ������� Ǯ�� �༺�� �ִ� ������ 100,000�̰� �༺�� �ִ� ������ ��
// ������ ��� ������ ���ϸ� 100000C2 ���� ������ �̸� �迭 �Ǵ� priority_queue��
// ������ ���� �޸� 128MB���� �翬�� �޸� �ʰ��� �߻��Ѵ�!!!!!
// ���� �̷��� ������ ���� ���� �׷���(dense graph)�� ��쿡�� prim ����� ����ؾ�
// �Ѵ�.
// �޸� ���� ������ ��� ���� ������ �� ������ ������ �޸� �ʰ��� �߻��Ѵ�.
// �׷��� prim algorithm���� �ʿ��� ������ ���� ������ ����� ���� Ȱ���Ѵ�.
// --> �̷��� �ص� �޸� �ʰ� �߻��Ѵ�! �ٸ� ���̵� �ʿ��ϴ�.

#include "pch.h"
#include <cstdio> // NULL
#include <cstdlib> // abs
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

int N;
vector<vertex> GRAPH;
vector<int> VISITED;
vector<vector<int>> STARS;

void findEdge(int cur)
{
	int dx, dy, dz, dist;
	int cnt = 0;
	GRAPH.clear();
	for (int i = 1; i <= N; i++) {
		if (i == cur) continue;
		dx = abs(STARS[i][0] - STARS[cur][0]);
		dy = abs(STARS[i][1] - STARS[cur][1]);
		dz = abs(STARS[i][2] - STARS[cur][2]);
		dist = min({ dx, dy, dz });
		//GRAPH[cnt++] = vertex(i, dist);
		GRAPH.push_back(vertex(i, dist));
	}
}

void prim()
{
	long long minval = 0;
	int count = -1;
	vertex select;
	priority_queue<vertex, vector<vertex>, compare> mypq;

	mypq.push(vertex(1, 0));
	while (!mypq.empty()) {
		if (count >= N - 1) break;
		select = mypq.top();
		mypq.pop();
		if (!VISITED[select.name]) {
			VISITED[select.name] = 1;
			minval += select.value;
			count++;
			findEdge(select.name);
			for (vertex x : GRAPH) {
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

	cin >> N;
	//GRAPH.resize(N - 1);
	VISITED.resize(N + 1, 0);
	// coordinate �Է�
	STARS.resize(N + 1, vector<int>(3, 0));
	for (int i = 1; i <= N; i++)
		cin >> STARS[i][0] >> STARS[i][1] >> STARS[i][2];
	prim();
}