// 1865_1.cpp
// ��Ȧ
// ���ͽ�Ʈ�� �̿��ؼ� Ǯ� �ð��� �� �� ������� ����.
// ���ͽ�Ʈ��� Ǯ�� �� ������ ��� priority queue�� ����ϸ� �޸� �ʰ��� �߻��ϱ� ������ queue�� ����ؾ� �ȴ�.
// ��������� Ǯ ��� 36ms, ���ͽ�Ʈ��� Ǯ�� 4ms�� �ҿ�ȴ�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
//#include <algorithm> // sort, max, min
#include <climits> // INT_MAX
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

int TC, N, M, W;
vector<vector<vertex>> graph;
vector<int> dist;
queue<vertex> myq;

void dijksta(int start)
{
	int distance;
	vertex cur;
	myq.push(vertex(start, 0));
	dist[start] = 0;
	while (!myq.empty()) {
		cur = myq.front();
		myq.pop();
		if (cur.name == start && cur.value < 0) break;
		if (cur.value > dist[cur.name]) continue;
		for (vertex i : graph[cur.name]) {
			distance = cur.value + i.value;
			if (distance < dist[i.name]) {
				dist[i.name] = distance;
				myq.push(vertex(i.name, distance));
			}
		}
	}
}

void do_test()
{
	int s, e, t;
	cin >> N >> M >> W;
	graph.resize(N + 1);
	dist.resize(N + 1, INT_MAX);
	for (int i = 1; i <= M; i++) {
		cin >> s >> e >> t;
		graph[s].push_back(vertex(e, t));
		graph[e].push_back(vertex(s, t));
	}
	for (int i = 1; i <= W; i++) {
		cin >> s >> e >> t;
		graph[s].push_back(vertex(e, -t));
	}
	dijksta(1);
	if (dist[1] < 0) cout << "YES" << "\n";
	else cout << "NO" << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> TC;
	while (TC--) {
		do_test();
		graph.clear();
		dist.clear();
		while (!myq.empty()) myq.pop();
	}
}