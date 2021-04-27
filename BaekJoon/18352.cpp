// 18352.cpp
// Ư�� �Ÿ��� ���� ã��
// �̰� ���� ���� ���ͽ�Ʈ��(Dijkstra) �����̴�.
// ������ �Ÿ� 1�� �׷��� �����͸� �Է¹޾� dikjstra�� ������.
// ����� X�κ��� �ִ� �Ÿ� K�� ��� �������� ����Ѵ�. �ִ� �Ÿ� K�� ������ �ϳ��� ���� ��� -1�� ����Ѵ�.
// ���ѽð� 2�� �� 468ms(27,888KB)�� �ҿ�Ǿ���.
// ������� 182/1533�� ���� 11.87%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
//#include <list>
//#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const int INF = 987654321;
struct vertex {
	int name;
	int value;
	vertex() {}
	vertex(int n, int v) : name(n), value(v) {}
	bool operator< (const vertex& rhs) const { return value > rhs.value; } // �������� ����
};

int g_N;
vector<vector<vertex>> g_graph;
vector<int> g_dist;

void dijkstra(int start)
{
	priority_queue<vertex> mypq;
	int distance;
	vertex cur;
	mypq.push(vertex(start, 0));
	g_dist[start] = 0;
	while (!mypq.empty()) {
		cur = mypq.top();
		mypq.pop();
		if (cur.value > g_dist[cur.name]) continue;
		for (vertex i : g_graph[cur.name]) {
			distance = cur.value + i.value;
			if (distance < g_dist[i.name]) {
				g_dist[i.name] = distance;
				mypq.push(vertex(i.name, distance));
			}
		}
	}
}

int main()
{
	FAST;
	int M, K, X;
	cin >> g_N >> M >> K >> X;
	g_graph.resize(g_N + 1);
	g_dist.resize(g_N + 1, INF);

	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		g_graph[a].push_back({ b, 1 });
	}
	dijkstra(X);
	int answer = 0;
	for (int i = 1; i < g_N + 1; i++) {
		if (i == X) continue;
		if (g_dist[i] == K) {
			answer++;
			cout << i << "\n";
		}
	}
	if (!answer) cout << -1 << "\n";
}