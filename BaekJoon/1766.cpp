// 1766.cpp
// 문제집
// 역시 위상정렬을 이용하는데 문제 이해를 잘 해야 한다.
// 주어진 순서쌍만으로 모든 문제를 풀 수 있다는 전제가 있는데
// 처음에 이를 간과하고 주어진 순서쌍이 문제를 풀 수 있는 일부라고
// 생각하고 이를 전제로 문제를 풀려고 하니 자꾸 사이클이 나와서 문제를 풀 수 없었다!!!
// 이 문제는 주어진 순서쌍만 가지고 위상 정렬 하면서 큐에 여러개가 입력이 될 경우
// 값이 작은 것을 먼저 처리하면 된다.
// 이를 위해서는 우선 순위 큐를 사용한다.
// 문제만 제대로 이해하고 나면 위상 정렬을 이용해서 너무너무 쉽게 풀 수 있는 문제이다.
// 제한시간 2초 중 28ms(3904KB)가 소요되었다.
// 맞은사람 13/2247로 상위 0.57%에 rank되었다.

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
#include <queue> // queue, priority_queue

using namespace std;

struct compare {
	bool operator() (const int& l, const int& r) const
	{
		return (l > r); // increasing order
	}
};

int g_N;
vector<vector<int>> g_graph;
vector<int> g_degree;

void topological_sort()
{
	priority_queue<int, vector<int>, compare> myq;
	int pick;
	for (int i = 1; i <= g_N; i++) {
		if (g_degree[i] == 0)
			myq.push(i);
	}
	while (!myq.empty()) {
		pick = myq.top();
		myq.pop();
		cout << pick << " ";
		for (int x : g_graph[pick]) {
			g_degree[x]--;
			if (g_degree[x] == 0)
				myq.push(x);
		}
	}
	cout << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int M, a, b;
	cin >> g_N;
	g_graph.resize(g_N + 1);
	g_degree.resize(g_N + 1, 0);
	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		g_graph[a].push_back(b);
		g_degree[b]++;
	}
	topological_sort();
}