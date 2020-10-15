// 15681.cpp
// 트리와 쿼리
// 트리를 직접 구현하고, 특정 노드에서 
// 자신 포함 서브 트리의 갯수를 구하는 문제이다.
// makeTree와 countSubTreeNodes 두 함수를 구현하는 문제이다.
// 풀기는 풀었다.
// University > 연세대학교 > 2018 연세대학교 컴퓨터과학과 프로그래밍 경진대회 PC번
// 제한시간 1초 중 84ms(19524KB)가 소요되었다.
// 맞은사람 132 중 68로 상위 51.51%에 rank되었다.
// 중간에 TREE를 만들지 않고 입력된 간선 정보에서 바로 sub tree count를 하면
// 좀 더 빨리 풀 수 있다.
/// Tree 만들지 않고 최적화시키니 60ms(14016KB)가 소요되었다.
/// 맞은사람 132 중 5로 상위 3.78%에 rank되었다.

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt
#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
//#include <queue> // queue, priority_queue

using namespace std;

int N, R, Q;
vector<vector<int>> GRAPH;
//vector<vector<int>> TREE;
vector<int> TREECNT;

/*
void makeTree(int current, int parent)
{
	for (int x : GRAPH[current]) {
		if (x != parent) {
			TREE[current].push_back(x);
			makeTree(x, current);
		}
	}
}

void countSubTreeNodes(int current)
{
	if (TREECNT[current]) return;
	TREECNT[current] = 1;
	for (int x : TREE[current]) {
		countSubTreeNodes(x);
		TREECNT[current] += TREECNT[x];
	}
}
*/

int countSubTreeNodes(int current, int parent)
{
	TREECNT[current] = 1;
	for (int x : GRAPH[current]) {
		if (x != parent) {
			TREECNT[current] += countSubTreeNodes(x, current);
		}
	}
	return TREECNT[current];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int u, v, q;
	cin >> N >> R >> Q;
	GRAPH.resize(N + 1);
	//TREE.resize(N + 1);
	TREECNT.resize(N + 1, 0);
	for (int i = 0; i < N - 1; i++) {
		cin >> u >> v;
		GRAPH[u].push_back(v);
		GRAPH[v].push_back(u);
	}
	//makeTree(R, -1);
	countSubTreeNodes(R, 0); // Tree를 안만들면 root를 시작으로 각 node의 count를 먼저 구해둔다. 안그러면 root가 매번 바뀌어서 값이 틀린다.
	for (int i = 0; i < Q; i++) {
		cin >> q;
		//countSubTreeNodes(q, 0);
		cout << TREECNT[q] << "\n";
	}
	return 0;
}
