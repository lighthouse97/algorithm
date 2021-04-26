// 1956.cpp
// �
// �÷��̵�-�ͼ�(floyd-warshall) �˰����� �̿��ϴ� �����̴�.
// ���Ѵ��� �պ� ����Ŭ�� ã�Ƽ� �� �� ���� ���� ���� ���Ѵ�.
// 108ms�� �ҿ�Ǿ���.
// �ʱ�ȭ�� �� i==j�� �� 0�� ���� �ʰ� INF�� �ʱ�ȭ�Ѵ���(�������� �ణ ����) �÷��̵�-�ͼ��� ������
// graph[i][i]�� ���� �ּҰ��� ���ϸ� �ð��� �� ���� �� �ִ�.(108ms -> 100ms)


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
//#include <queue> // queue, priority_queue

using namespace std;

int V, E;
vector<vector<int>> graph;
const int INF = 10001;

void floyd_warshall()
{
	// ���ľ� �� ���(1~V)
	for (int k = 1; k <= V; k++) {
		// �����(1~V)
		for (int i = 1; i <= V; i++) {
			// ������(1~N)
			for (int j = 1; j <= V; j++) {
				if (graph[i][k] + graph[k][j] < graph[i][j])
					graph[i][j] = graph[i][k] + graph[k][j];
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int a, b, c, minval = INF;
	cin >> V >> E;
	graph.resize(V + 1, vector<int>(V + 1, INF)); // initialise to INF
	for (int i = 1; i <= V; i++)
		graph[i][i] = 0;

	for (int i = 0; i < E; i++) {
		cin >> a >> b >> c;
		graph[a][b] = c;
	}
	floyd_warshall();
	for (int i = 1; i <= V; i++) {
		for (int j = i + 1; j <= V; j++) {
			if (graph[i][j] + graph[j][i] < minval)
				minval = graph[i][j] + graph[j][i];
		}
	}
	cout << (minval == INF ? -1 : minval) << "\n";
}
