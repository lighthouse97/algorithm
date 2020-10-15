// 1753.cpp
// �ִ� ���
// ��ǥ���� ���ͽ�Ʈ�� �˰����� ����Ѵ�.
// O((V+E)logV)�� �ð����⵵�� ������.

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

struct compare {
	bool operator() (const vertex& l, const vertex& r) const
	{
		return (l.value > r.value); // greater than, ��������
	}
};

int V, E, K;
vector<vector<vertex>> graph; // ���� �Է�
vector<int> dist; // ��������� �� �������� �Ÿ�
priority_queue<vertex, vector<vertex>, compare> mypq; // �湮�� ������ ���� �켱���� ť

void dijkstra(int start)
{
	int distance;
	vertex cur;
	mypq.push(vertex(start, 0));
	dist[start] = 0;
	while (!mypq.empty()) {
		cur = mypq.top();
		mypq.pop();
		if (cur.value > dist[cur.name]) continue; // �ִܰŸ��� ���� ������ ���� pq�� �Ÿ��� dist���� �� �ָ� �׳� ���
		for (vertex i : graph[cur.name]) { // cur ������ child �˻�
			distance = cur.value + i.value;
			if (distance < dist[i.name]) { // cur ������ child ���� �Ÿ����� dist[child]���� ������ ���� ��� �켱����
				dist[i.name] = distance;    // Ž���ؾ� �ϹǷ� pq�� �ִ´�. // pq�� name�� ���� value�� �ٸ� �������� �� �� �ִ�.
				mypq.push(vertex(i.name, distance));
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int from, to, val;
	cin >> V >> E >> K;
	graph.resize(V + 1);
	dist.resize(V + 1, INT_MAX); // INF������ �ʱ�ȭ�Ѵ�.

	for (int i = 0; i < E; i++) {
		cin >> from >> to >> val;
		graph[from].push_back(vertex(to, val));
	}
	dijkstra(K);
	for (int i = 1; i <= V; i++) {
		if (dist[i] == INT_MAX) cout << "INF" << "\n";
		else cout << dist[i] << "\n";
	}
}
