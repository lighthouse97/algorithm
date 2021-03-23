// 1707.cpp
// 이분 그래프(Bipartite Graph)
// 이분 그래프를 구분하는 문제인데 BFS를 이용해서 모든 정점을 탐색하면 아주 쉽게 구할 수 있다.
// 모든 정점이 연결이 안되어 있을 수 있으므로 모든 정점에 대해 bfs를 돌려봐야 한다.
// 제한시간 2초 중 260ms(6,344KB)가 소요되었다.
// 맞은사람 561/6293로 상위 8.91%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
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

vector<vector<int>> g_graph;
vector<int> g_visited; // 1, -1로 정점의 색을 구분

bool bfs()
{
	queue<int> myq;
	int root;

	int n = (int)g_graph.size() - 1;
	bool partite = true;
	for (int i = 1; i < n + 1; i++) {
		if (g_visited[i]) continue;
		root = i;
		myq.push(root);
		g_visited[root] = 1;
		int check;		
		while (!myq.empty()) {
			check = myq.front();
			myq.pop();
			for (int x : g_graph[check]) {
				if (g_visited[x] == 0) { // 방문 No
					myq.push(x);
					g_visited[x] = g_visited[check] * -1; // 서로 다른 색 지정
				}
				else { // 방문 YES
					if (g_visited[x] * g_visited[check] > 0) { // 같은 색
						partite = false;
						break;
					}
				}
			}
			if (!partite) break;
		}
		if (!partite) break;
	}
	return partite;
}

void doTest()
{
	int v, e; // 정점의 갯수, 간선의 갯수		
	cin >> v >> e;
	g_graph.resize(v + 1);
	g_visited.resize(v + 1, 0);
	int v1, v2;
	for (int i = 0; i < e; i++) {
		cin >> v1 >> v2;
		g_graph[v1].push_back(v2);
		g_graph[v2].push_back(v1);
	}
	cout << (bfs() == true ? "YES" : "NO") << "\n";
	g_graph.clear();
	g_visited.clear();
}

int main()
{
	FAST;

	int K;
	cin >> K;
	for (int i = 0; i < K; i++) doTest();
}