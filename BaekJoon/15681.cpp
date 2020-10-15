// 15681.cpp
// Ʈ���� ����
// Ʈ���� ���� �����ϰ�, Ư�� ��忡�� 
// �ڽ� ���� ���� Ʈ���� ������ ���ϴ� �����̴�.
// makeTree�� countSubTreeNodes �� �Լ��� �����ϴ� �����̴�.
// Ǯ��� Ǯ����.
// University > �������б� > 2018 �������б� ��ǻ�Ͱ��а� ���α׷��� ������ȸ PC��
// ���ѽð� 1�� �� 84ms(19524KB)�� �ҿ�Ǿ���.
// ������� 132 �� 68�� ���� 51.51%�� rank�Ǿ���.
// �߰��� TREE�� ������ �ʰ� �Էµ� ���� �������� �ٷ� sub tree count�� �ϸ�
// �� �� ���� Ǯ �� �ִ�.
/// Tree ������ �ʰ� ����ȭ��Ű�� 60ms(14016KB)�� �ҿ�Ǿ���.
/// ������� 132 �� 5�� ���� 3.78%�� rank�Ǿ���.

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
	countSubTreeNodes(R, 0); // Tree�� �ȸ���� root�� �������� �� node�� count�� ���� ���صд�. �ȱ׷��� root�� �Ź� �ٲ� ���� Ʋ����.
	for (int i = 0; i < Q; i++) {
		cin >> q;
		//countSubTreeNodes(q, 0);
		cout << TREECNT[q] << "\n";
	}
	return 0;
}
