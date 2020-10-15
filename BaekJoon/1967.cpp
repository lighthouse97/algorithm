// 1967.cpp
// 트리의 지름
// 이 문제도 트리(tree)항목이지만 그래프 bfs탐색 문제이다.
// 양방향 그래프로 풀어야 한다.
// root node로부터 거리가 가장 먼 leaf node를 찾은 다음에
// 그 leaf node에서 bfs탐색을 하여 가장 거리가 먼 node의
// 거리를 구하면 그 거리값이 바로 트리의 지름이 된다.
// 앞에서 트리의 지름를 구하는 문제(1167)과 동일하게 풀면 된다.
// 제한시간 2초에서 소요시간은 4ms(2788KB) 소요되었다.

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
#include <queue>

using namespace std;

struct node {
	int name;
	int value;
	node() {}
	node(int n, int v) : name(n), value(v) {}
};

int N;
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
	cin >> N;
	GRAPH.resize(N + 1);
	DP.resize(N + 1, -1);
	for (int i = 0; i < N - 1; i++) {
		cin >> parent >> child >> val;
		GRAPH[parent].push_back(node(child, val));
		GRAPH[child].push_back(node(parent, val));
	}
	bfs(1);
	DP = vector<int>(N + 1, -1); // reset DP
	cout << bfs(LEAF) << "\n";
}