// 1916.cpp
// �ּҺ�� ���ϱ�
// ���ͽ�Ʈ�� ������ �ִܰ��(1753)���� �ߴ� �Ͱ� ������ ����̴�.
// ��, ������� �־����� �� �������� ��� ������ �ƴϰ� Ư�� ��ġ��
// ������ �� ���� �ٸ���.
// 24ms(3304KB) �ҿ�Ǿ���.

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
vector<int> dist; // ��������� �� �������� �Ÿ�
priority_queue<vertex, vector<vertex>, compare> mypq; // �湮�� ������ ���� �켱���� ť

void dijksta(int start)
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
	int start, goal;
	cin >> N >> M;
	graph.resize(N + 1);
	dist.resize(N + 1, MAX_VAL);

	for (int i = 0; i < M; i++) {
		cin >> from >> to >> val;
		graph[from].push_back(vertex(to, val));
	}
	cin >> start >> goal;
	dijksta(start);
	cout << dist[goal] << "\n";
}