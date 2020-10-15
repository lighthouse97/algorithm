// 2606.cpp
// 바이러스
// DFS 또는 BFS를 이용해서 푸는데, 여기서는 DFS를 이용해서 풀어보았다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
//#include <queue>

using namespace std;

int visited[101] = { 0, };
vector<int> graph[101];

int dfs(int x)
{
	int count = 0;
	visited[x] = 1;
	count = 1;
	for (int i : graph[x]) {
		if (!visited[i]) {
			count += dfs(i);
		}
	}
	return count;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M;
	int n1, n2;
	cin >> N >> M;
	for (int i = 1; i <= M; i++) {
		cin >> n1 >> n2;
		graph[n1].push_back(n2);
		graph[n2].push_back(n1);
	}
	for (int i = 1; i <= N; i++)
		sort(graph[i].begin(), graph[i].end());
	cout << dfs(1) - 1 << "\n";
}