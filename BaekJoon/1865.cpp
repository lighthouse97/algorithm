// 1865.cpp
// ��Ȧ
// ����-���� �˰����� ����ϴ� �����̴�.
// ����-����� child�� ������Ʈ�� �� ������Ʈ�Ǵ� child�� ������� ������ �Ǵ��� �˻��Ѵ�.
// ����-����� Ǯ� negative cycle�� �ִ��� �˻��ص� ������ ���ͽ�Ʈ��� Ǯ� ������� 0���� ��������
// �˻��ص� �ȴ�.(���ͽ�Ʈ��� Ǫ�� ���� �� �� �ð��� ����ȴ�.)

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

int TC, N, M, W;
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
	bellman_ford();
	if (ncycle) cout << "YES" << "\n";
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
		ncycle = 0;
	}	
}