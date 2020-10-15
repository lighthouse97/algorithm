// 9370.cpp
// 미확인 도착지
// 다익스트라로 풀 수 있는데 문제 자체를 이해를 못했다.
// 목표까지 다익스트라로 최단 거리를 구하고 이 최단 거리 경로에 g,h 두 지점이
// 포함되어져 있는지 따지면 된다. 목표까지의 경로에 g,h가 없으면 그 목표는 제외한다.
// 탐색 방법 1)
// 각 경로의 길이를 (길이)*2해서 짝수로 만들고, g, h의 경로만 (길이)*2 - 1 해서 홀수로 만든다.
// g, h를 거치지 않으면 목표까지 최단경로는 짝수로 남을 것이고 g, h를 거치면 목표까지 최단 경로는 홀수값이 된다.
// 탐색 방법 2)
// 목적지에서 역으로 출발지까지 탐색해서(dfs를 이용한다) g, h를 거치면 목표를 선택한다.
// 탐색방법1) 이 더 시간이 절약된다.

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
		return (l.value > r.value); // greater than, 오름차순
	}
};

int T, n, m, t;
int s, g, h;
vector<vector<vertex>> graph; // 정점 입력
vector<int> dist; // 출발점에서 각 정점까지 거리
priority_queue<vertex, vector<vertex>, compare> mypq; // 방문할 정점에 대한 우선순위 큐

void dijksta(int start)
{
	int distance;
	vertex cur;
	mypq.push(vertex(start, 0));
	dist[start] = 0;
	while (!mypq.empty()) {
		cur = mypq.top();
		mypq.pop();
		if (cur.value > dist[cur.name]) continue; // 최단거리라서 동일 지점에 대해 pq의 거리가 dist보다 더 멀면 그냥 통과
		for (vertex i : graph[cur.name]) { // cur 정점의 child 검색
			distance = cur.value + i.value;
			if (distance < dist[i.name]) { // cur 정점과 child 정점 거리합이 dist[child]보다 작으면 작은 경로 우선으로
				dist[i.name] = distance;    // 탐색해야 하므로 pq에 넣는다. // pq에 name은 같고 value는 다른 여러개가 들어갈 수 있다.
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