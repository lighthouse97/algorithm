// 1167.cpp
// 트리의 지름
// 이 문제 역시 트리 항목에 속해 있지만 그래프 문제이다.
// 양방향 그래프이고 모든 점에서 dfs 또는 bfs 탐색을 해서 가장 거리가 먼
// 지점의 거리를 구하면 되지만 이렇게 하면 시간이 많이 걸리고
// 임의의 한점에서 leaf node(가장 거리가 먼 지점)를 구하고 그 lead node에서
// 탐색을 해서 가장 거리가 먼 곳의 거리를 구하면 트리의 지름을 구할 수 있다.
// 소요시간은 제한시간 2초에서 88ms(8944KB) 소요되었다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
#include <queue>

using namespace std;

struct node {
	int name;
	int value;
	node() {}
	node(int n, int v) : name(n), value(v) {}
};

int V;
vector<vector<node>> GRAPH;
vector<int> DP;
int LEAF = 0; // leaf node

int bfs(int x)
{
	int temp, maxval;
	queue<int> myq;
	myq.push(x);
	DP[x] = 0;
	maxval = 0;
	while (!myq.empty()) {
		temp = myq.front();
		myq.pop();
		for (node i : GRAPH[temp]) {
			if (DP[i.name] == -1) {
				myq.push(i.name);
				DP[i.name] = DP[temp] + i.value;
				if (DP[i.name] > maxval) {
					maxval = DP[i.name];
					LEAF = i.name;
				}
			}
		}
	}
	return maxval;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int parent, child, val;
	cin >> V;
	GRAPH.resize(V + 1);
	DP.resize(V + 1, -1);
	for (int i = 0; i <= V - 1; i++) {
		cin >> parent;
		while (true) {
			cin >> child;
			if (child == -1) break;
			cin >> val;
			GRAPH[parent].push_back(node(child, val));
		}
	}
	bfs(1);
	DP = vector<int>(V + 1, -1); // reset DP
	cout << bfs(LEAF) << "\n";
}
