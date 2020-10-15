// 11404.cpp
// �÷��̵�
// �÷��̵�-�ͼ�(floyd-warshall) �˰����� �̿��ϴ� �����̴�.
// Ư�� ������� �ƴ� ��� ������ ���� �ִܰŸ��� ���Ѵ�.
// ���� ���ͽ�Ʈ��(O((V+E)logV)), ����-����(O(VE))�� ����
// �ð����⵵�� �� ����.�ſ� ���� �� ���Ѵ�.(O(V^3))
// �˰��� ��ü�� ���� ���̴�.
// ��ä������ Ʋ�ȴ�.(20.03.05)
// �ּҰ��� ã���Ƿ� ��ü ����� �ʱ� ����� INF�� �ʱ�ȭ �ϴµ� �� ���� n�ִ밪(100)*cost�ִ밪(100,000)=10,000,000
// ���� Ŀ�� �Ѵ�. �׷��� INF���� cost�ִ밪 100,000���� 100,001�� ������ cost���� ū ���������� Ʋ�� �� �ۿ� ����.
// ���ѽð� 1�� �� 24ms(2,116KB)�� �ҿ�Ǿ���.
// ������� 394/3337�� ���� 11.80%�� rank�Ǿ���.

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

int N, M;
vector<vector<int>> graph;
const int INF = 10000001;

void floyd_warshall()
{
	// ���ľ� �� ���(1~N)
	for (int k = 1; k <= N; k++) {
		// �����(1~N)
		for (int i = 1; i <= N; i++) {
			// ������(1~N)
			for (int j = 1; j <= N; j++) {
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

	int a, b, c;
	cin >> N >> M;
	graph.resize(N+1, vector<int>(N+1, INF)); // initialise to INF
	for (int i = 1; i <= N; i++)
		graph[i][i] = 0;
	
	for (int i = 0; i < M; i++) {
		cin >> a >> b >> c;
		if(c < graph[a][b]) graph[a][b] = c;
	}
	floyd_warshall();
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << (graph[i][j] == INF ? 0 : graph[i][j]) << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}
