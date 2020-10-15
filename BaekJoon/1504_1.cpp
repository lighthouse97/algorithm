// 1504_1.cpp
// Ư���� �ִ� ���
// ��ǥ���� ���ͽ�Ʈ�� �˰����� ����Ѵ�.
// ���� ���ͽ�Ʈ�� �Լ��� ��������� �޸��ؼ� ���� �� ȣ���Ѵ�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
#include <algorithm> // sort, max, min
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

int N, E, A, B;
vector<vector<vertex>> graph; // ���� �Է�

vector<int> dijksta(int start)
{
	vector<int> dist(N + 1, INT_MAX);
	priority_queue<vertex, vector<vertex>, compare> mypq;
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
	return dist;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	vector<int> dist_1, dist_A, dist_B;
	int from, to, val;
	int result_a, result_b;
	cin >> N >> E;
	graph.resize(N + 1);

	for (int i = 0; i < E; i++) {
		cin >> from >> to >> val;
		graph[from].push_back(vertex(to, val));
		graph[to].push_back(vertex(from, val));
	}
	cin >> A >> B;
	// dijkstra()�Լ��� 6�� �θ��� �ʰ�, 3���� ȣ�������ν� ������ �޼��� �� �ִ�.
	// dijkstra(1,N), dijkstra(A,N), dijkstra(B,N)���� 
	// dijkstra(1,N) : 1 -> A, 1 -> B
	// dijkstra(A,N) : A -> B, A -> N
	// dijkstra(B,N) : B -> N, B -> A
	// ������ ���´�. �̸� ������ 1->A->B->N, 1->B->A->N�� ���� ���� �� �ִ�.
	dist_1 = dijksta(1);
	dist_A = dijksta(A);
	dist_B = dijksta(B);
	if (dist_1[A] == INT_MAX || dist_A[B] == INT_MAX || dist_B[N] == INT_MAX) result_a = -1;
	else result_a = dist_1[A] + dist_A[B] + dist_B[N];
	if (dist_1[B] == INT_MAX || dist_B[A] == INT_MAX || dist_A[N] == INT_MAX) result_b = -1;
	else result_b = dist_1[B] + dist_B[A] + dist_A[N];

	if (result_a < 0 && result_b < 0)
		cout << -1 << "\n";
	else if (result_a > 0 && result_b > 0)
		cout << min(result_a, result_b) << "\n";
	else if (result_a > 0)
		cout << result_a << "\n";
	else
		cout << result_b << "\n";
}