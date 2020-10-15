// 1260.cpp
// DFS¿Í BFS

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
#include <queue>

using namespace std;

int visited[1001] = { 0, };
vector<int> graph[1001];
queue<int> myq;

void dfs(int x)
{
	visited[x] = 1;
	cout << x << " ";
	for (int i : graph[x]) {
		if (!visited[i]) {
			dfs(i);
		}
	}
}

void bfs(int x)
{
	int temp;
	myq.push(x);
	visited[x] = 1;
	while (!myq.empty()) {
		temp = myq.front();
		myq.pop();
		cout << temp << " ";
		for (int i: graph[temp]) {
			if (!visited[i]) {
				myq.push(i);
				visited[i] = 1;
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, M, V;
	int n1, n2;
	cin >> N >> M >> V;
	for (int i = 1; i <= M; i++) {
		cin >> n1 >> n2;
		graph[n1].push_back(n2);
		graph[n2].push_back(n1);
	}
	for (int i = 1; i <= N; i++)
		sort(graph[i].begin(), graph[i].end());
	dfs(V);
	cout << "\n";
	for (int i = 1; i <= 1000; i++) visited[i] = 0;
	bfs(V);
	cout << "\n";
}