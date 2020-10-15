// 9370.cpp
// ��Ȯ�� ������
// ���ͽ�Ʈ��� Ǯ �� �ִµ� ���� ��ü�� ���ظ� ���ߴ�.
// ��ǥ���� ���ͽ�Ʈ��� �ִ� �Ÿ��� ���ϰ� �� �ִ� �Ÿ� ��ο� g,h �� ������
// ���ԵǾ��� �ִ��� ������ �ȴ�. ��ǥ������ ��ο� g,h�� ������ �� ��ǥ�� �����Ѵ�.
// Ž�� ��� 1)
// �� ����� ���̸� (����)*2�ؼ� ¦���� �����, g, h�� ��θ� (����)*2 - 1 �ؼ� Ȧ���� �����.
// g, h�� ��ġ�� ������ ��ǥ���� �ִܰ�δ� ¦���� ���� ���̰� g, h�� ��ġ�� ��ǥ���� �ִ� ��δ� Ȧ������ �ȴ�.
// Ž�� ��� 2)
// ���������� ������ ��������� Ž���ؼ�(dfs�� �̿��Ѵ�) g, h�� ��ġ�� ��ǥ�� �����Ѵ�.
// Ž�����1) �� �� �ð��� ����ȴ�.

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

int T, n, m, t;
int s, g, h;
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

void solve()
{
	int a, b, d, tmp;
	int x;
	vector<int> result;
	cin >> n >> m >> t;
	cin >> s >> g >> h;
	graph.resize(n + 1);
	dist.resize(n + 1, INT_MAX);
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> d;
		if ((a == g && b == h) || (a == h && b == g)) tmp = d * 2 - 1;
		else tmp = d * 2;
		graph[a].push_back(vertex(b, tmp));
		graph[b].push_back(vertex(a, tmp));
	}
	dijksta(s);
	for (int i = 0; i < t; i++) {
		cin >> x;
		if (dist[x] != INT_MAX && (dist[x] % 2))
			result.push_back(x);
	}
	sort(result.begin(), result.end());
	for (int x : result)
		cout << x << " ";
	cout << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> T;
	while (T--) {
		solve();
		graph.clear();
		dist.clear();
	}
}