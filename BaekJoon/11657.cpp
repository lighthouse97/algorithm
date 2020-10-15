// 11657.cpp
// Ÿ�Ӹӽ�
// ����-���� �˰����� ����ϴ� �����̴�.
// ������ ��ο� -���� �־� ���ͽ�Ʈ�� �˰������δ� ������
// Ǯ �� ���� ����-���� �˰������� ������ Ǭ��.
// ���̽�Ʈ�� �˰����� O((V+E)logV)�� �ð����⵵�� �����µ� ����,
// O(E*V)�� �ð����⵵�� ������. (�ð����⵵�� ��������� ū�� ��� ���� ��ο� ���ؼ��� ó���� �� �ִ�.)

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
//#include <queue> // queue, priority_queue

using namespace std;

struct vertex {
	int name;
	int value;
	vertex() {}
	vertex(int n, int v) : name(n), value(v) {}
};

int N, M;
int ncycle = 0; // negative cycle
vector<vector<vertex>> graph; // ���� �Է�
vector<int> dist; // ��������� �� �������� �Ÿ�

void bellman_ford()
{
	int distance;
	dist[1] = 0;
	for (int i = 1; i <= N; i++) { // ������Ʈ �� �������� Ž���� ���߸��� �ʱ� ���� n-1��(n-1���� ����)���� ������.(n��°�� Ȯ�ο�) 
		for (int j = 1; j <= N; j++) {
			for (vertex x : graph[j]) { // �� ���� ��� child�� ����
				distance = dist[j] + x.value;
				if (dist[j] != INT_MAX && distance < dist[x.name]) { // �� ���� �ִ� ��θ� ������Ʈ�Ѵ�.(�ִܰ�� update�� ���� ����)
					dist[x.name] = distance;
					if (i == N) ncycle = 1; // i�� n-1 ���� n��°���� update�� ���� ����� �̰��� negative cycle�� ���� ���̴�.
				}
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int a, b, c;
	cin >> N >> M;
	graph.resize(N + 1);
	dist.resize(N + 1, INT_MAX);
	for (int i = 1; i <= M; i++) {
		cin >> a >> b >> c;
		graph[a].push_back(vertex(b, c));
	}
	bellman_ford();
	if (ncycle) cout << -1 << "\n"; // negative cycle exist!
	else {
		for (int i = 2; i <= N; i++) {
			cout << ((dist[i] == INT_MAX) ? -1 : dist[i]) << "\n";
		}
	}
}
