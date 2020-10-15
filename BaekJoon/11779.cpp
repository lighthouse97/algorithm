// 11779.cpp
// �ּҺ�� ���ϱ�2
// '�ּҺ�� ���ϱ�(1916)'���� �ּҺ��Ӹ� �ƴ϶� �� ��α��� ����
// ���ϴ� �����̴�.
// 24ms(3332KB) �ҿ�Ǿ���.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
#include <stack>
//#include <set>
//#include <cmath> // sqrt
#include <queue> // queue, priority_queue

using namespace std;

const int MAX_VAL = 987654321;

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

int N, M;
vector<vector<vertex>> graph; // ���� �Է�
vector<vector<int>> dist; // ��������� �� �������� �Ÿ�([][0] : �ּҰŸ�, [][1] : �տ� ����� ����
priority_queue<vertex, vector<vertex>, compare> mypq; // �湮�� ������ ���� �켱���� ť

void dijksta(int start)
{
	int distance;
	vertex cur;
	mypq.push(vertex(start, 0));
	dist[start][0] = 0;
	while (!mypq.empty()) {
		cur = mypq.top();
		mypq.pop();
		if (cur.value > dist[cur.name][0]) continue; // �ִܰŸ��� ���� ������ ���� pq�� �Ÿ��� dist���� �� �ָ� �׳� ���
		for (vertex i : graph[cur.name]) { // cur ������ child �˻�
			distance = cur.value + i.value;
			if (distance < dist[i.name][0]) { // cur ������ child ���� �Ÿ����� dist[child]���� ������ ���� ��� �켱����
				dist[i.name][0] = distance;    // Ž���ؾ� �ϹǷ� pq�� �ִ´�. // pq�� name�� ���� value�� �ٸ� �������� �� �� �ִ�.
				dist[i.name][1] = cur.name; // �ִ� �Ÿ� ���� ��� ���
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
	int start, goal, cur;
	stack<int> path;
	cin >> N >> M;
	graph.resize(N + 1);
	dist.resize(N + 1, vector<int>(2));
	for (int i = 1; i <= N; i++) { // initialise the dist
		dist[i][0] = MAX_VAL;
		dist[i][1] = 0;
	}

	for (int i = 0; i < M; i++) {
		cin >> from >> to >> val;
		graph[from].push_back(vertex(to, val));
	}
	cin >> start >> goal;
	dijksta(start);
	cout << dist[goal][0] << "\n";
	// find the path
	cur = goal;
	while (1) {
		path.push(cur);
		if (cur == start) break;
		cur = dist[cur][1];
	}
	cout << path.size() << "\n";
	while (!path.empty()) {
		cout << path.top() << " ";
		path.pop();
	}
	cout << "\n";
}