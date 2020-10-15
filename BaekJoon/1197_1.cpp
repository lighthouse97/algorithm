// 1197_1.cpp
// 최소 스패닝 트리
// 이번에는 prim algorithm으로 풀어본다.
// prim algorithm으로 푸니 52ms(6588KB)가 소요되었다.
// (prim에서 불필요한 queue를 없애고 좀 더 간단히 최적화시키니 48ms(6588KB)로 더 줄었다.)
// Kruskal algorithm(36ms(3316KB))에 비해 시간이 더 많이 걸렸다.
// 그래프내에 간선이 적은 희소 그래프(Sparse Graph)의 경우 Kruskal algorithm이 유리하고,
// 그래프내에 간선이 많은 밀집 그래프(Dense Graph)의 경우 Prim algorithm이 유리하다.

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
	int value;
	vertex() {}
	vertex(int n, int v) : name(n), value(v) {}
};

struct compare {
	bool operator() (const vertex& l, const vertex& r) const
	{
		return (l.value > r.value);
	}
};

int V, E;
vector<vector<vertex>> GRAPH;
vector<int> VISITED;

void prim()
{
	long long minval = 0;
	vertex select;
	priority_queue<vertex, vector<vertex>, compare> mypq;
	
	mypq.push(vertex(1, 0));
	while (!mypq.empty()) {
		select = mypq.top();
		mypq.pop();
		if (!VISITED[select.name]) {
			VISITED[select.name] = 1;
			minval += select.value;
			for (vertex x : GRAPH[select.name]) {
				if (!VISITED[x.name]) mypq.push(x);
			}
		}
	}
	cout << minval << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int a, b, c;
	cin >> V >> E;
	GRAPH.resize(V + 1); // V+1인데 E+1로헤서 "런타임 에러"가 나버렸다.
	VISITED.resize(V + 1, 0);
	for (int i = 1; i <= E; i++) {
		cin >> a >> b >> c;
		GRAPH[a].push_back(vertex(b, c));
		GRAPH[b].push_back(vertex(a, c));
	}
	prim();
}