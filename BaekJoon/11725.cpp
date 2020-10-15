// 11725.cpp
// 트리의 부모찾기
// 항목은 트리지만 '루트없는 트리'라고 했기 때문에 엄밀히 말해 트리가 아니다.
// 이는 양방향 그래프로 보면 된다.
// 양방향 그래프에서 임의의 점을 루트로 잡고 루트로부터 dfs탐색을 하면서 각 노드의 부모를
// 출력하면 된다.
// 제한시간 1초에서 소요시간은 52ms(11280KB)가 나왔다.

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
//#include <queue>

using namespace std;

int N;
vector<vector<int>> GRAPH;
vector<int> VISIT;
vector<int> NP;

void dfs(int x)
{
	VISIT[x] = 1;
	for (int i : GRAPH[x]) {
		if (!VISIT[i]) {
			NP[i] = x;
			dfs(i);
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n1, n2;
	cin >> N;
	GRAPH.resize(N + 1);
	VISIT.resize(N + 1, 0);
	NP.resize(N + 1, 0);
	for (int i = 0; i < N - 1; i++) {
		cin >> n1 >> n2;
		GRAPH[n1].push_back(n2);
		GRAPH[n2].push_back(n1);
	}
	dfs(1);
	for (int i = 2; i <= N; i++)
		cout << NP[i] << "\n";
}