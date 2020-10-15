// 10217.cpp
// KCM Travel
// �ִ� ��θ� ã�µ� ����� ���� ������ ������ ����̴�.
// ���� ���ͽ�Ʈ��� �ִ� ��θ� ã��,
// �ִ� �Ÿ��� �����ϴ� dist�迭�� �� ������ �ִ� �Ÿ� �ϳ���
// �����ϴ� ���� �ƴ϶� ��뺰�� ������ �Ǵ� ������ �迭�� ����Ǿ�� �Ѵ�.
// ���� ���������� ��� �ʰ��� �����ϰ� ������ �ִ� �Ÿ� �ĺ��� �� ���� ����
// ���� �����Ѵ�.

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

struct vertex {
	int name;
	int cost;
	int time;
	vertex() {}
	vertex(int n, int c, int t) : name(n), cost(c), time(t) {}
};

struct compare {
	bool operator() (const vertex& l, const vertex& r) const
	{
		return (l.time > r.time); // greater than, ��������
	}
};

int T, N, M, K;
vector<vector<vertex>> graph;
vector<vector<int>> dist;
priority_queue<vertex, vector<vertex>, compare> mypq; // �湮�� ������ ���� �켱���� ť
const int INF = 999999;

void dijkstra(int start)
{
	int dur, exp;
	vertex cur;
	mypq.push(vertex(start, 0, 0));
	dist[start][0] = 0;
	while (!mypq.empty()) {
		cur = mypq.top();
		mypq.pop();
		if (cur.cost >= M) continue;
		if (cur.time > dist[cur.name][cur.cost]) continue; // ���� �������� ����� ������ �ð��� ���� ���� ����.
		for (vertex i : graph[cur.name]) {
			dur = cur.time + i.time;
			exp = cur.cost + i.cost;
			if (exp <= M && dur < dist[i.name][exp]) {
				dist[i.name][exp] = dur;
				mypq.push(vertex(i.name, exp, dur));
			}
		}
	}
}

void do_test()
{
	int u, v, c, d;
	int result = INF;
	cin >> N >> M >> K;
	graph.resize(N + 1);
	dist.resize(N + 1, vector<int>(10001, INF)); // ����� 10000���� ������ �ֱ� ������ ��뿡 ���� �ð����� �����Ѵ�.
	for (int i = 0; i < K; i++) {
		cin >> u >> v >> c >> d;
		graph[u].push_back(vertex(v, c, d));
	}
	dijkstra(1);
	for (int i = 1; i <= M; i++) {
		if (dist[N][i] < result) {
			result = dist[N][i];
		}
	}
	if (result == INF) cout << "Poor KCM" << "\n";
	else cout << result << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> T;
	while (T--) {
		do_test();
		graph.clear();
		dist.clear();
	}
}