// 1949.cpp
// 우수 마을
// 이 문제도 앞의 2533(사회망 서비스)와 마찬가지로 트리 탐색하면서
// 동적프로그래밍을 이용하여 최적의 값을 제한 시간내에 찾아내는 문제이다.
// 동적프로그래밍 조건을 잘 생각해야 한다.
// 제한시간 2초 중 8ms(3252KB)가 소요되었다.
// 맞은사람 515 중 344로 상위 66.79%에 rank되었다.
// 좀 더 최적화 시키면 루트에서 함수를 2번 부르지 않고 한번만 불러서 해결할 수 있다.
// 이 때 소요시간은 4ms이하가 목표이다.
// 최적화 시키니 제한시간 2초 중 4ms(3252KB)가 소요되었다.
// 맞은사람 515 중 301로 상위 58.44%에 rank되었다.
// ...
// 정형화시켜서 핵심에 빨리 도달하지 못하고 주변에서 너무 헤매느라 시간을 너무 많이 잡아먹었다.
// 문제의 의도를 잘 파악하고 뭔가 생산없이 시간만 잡아먹고 있으면 본질을 놓치고 있다는 것을 빨리 파악하고
// 문제의 본질로 빨리 돌아갈 수 있는 노력을 계속 해야 겠다.

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt
#include <vector>
#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
//#include <queue> // queue, priority_queue

using namespace std;

int N;
vector<vector<int>> GRAPH;
vector<vector<int>> DP; // [][1] : current 포함, [][0] : current 안포함
vector<int> COUNT;

/*
int countVillage(int current, int parent, int curCheck)
{
	int& ret = DP[current][curCheck];
	if (ret != -1) return ret;
	ret = 0;
	if (curCheck) ret = COUNT[current];
	for(int v : GRAPH[current]) {
		if (v != parent) {
			if (curCheck) ret += countVillage(v, current, 0);
			else ret += max(countVillage(v, current, 0), countVillage(v, current, 1));
		}
	}
	return ret;
}
*/

void countVillage(int current, int parent)
{
	DP[current][1] += COUNT[current];
	for (int v : GRAPH[current]) {
		if (v != parent) {
			countVillage(v, current);
			DP[current][1] += DP[v][0];
			DP[current][0] += max(DP[v][0], DP[v][1]);
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int a, b;
	cin >> N;
	GRAPH.resize(N + 1);
	DP.resize(N + 1, vector<int>(2, 0));
	COUNT.resize(N + 1);
	for (int i = 1; i <= N; i++)
		cin >> COUNT[i];
	for (int i = 1; i <= N - 1; i++) {
		cin >> a >> b;
		GRAPH[a].push_back(b);
		GRAPH[b].push_back(a);
	}
	//cout << max(countVillage(1, 0, 0), countVillage(1, 0, 1)) << "\n";
	countVillage(1, 0);
	cout << max(DP[1][0], DP[1][1]) << "\n";
	return 0;
}