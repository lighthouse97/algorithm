// 1967.cpp
// Ʈ���� ����
// �� ������ Ʈ��(tree)�׸������� �׷��� bfsŽ�� �����̴�.
// ����� �׷����� Ǯ��� �Ѵ�.
// root node�κ��� �Ÿ��� ���� �� leaf node�� ã�� ������
// �� leaf node���� bfsŽ���� �Ͽ� ���� �Ÿ��� �� node��
// �Ÿ��� ���ϸ� �� �Ÿ����� �ٷ� Ʈ���� ������ �ȴ�.
// �տ��� Ʈ���� ������ ���ϴ� ����(1167)�� �����ϰ� Ǯ�� �ȴ�.
// ���ѽð� 2�ʿ��� �ҿ�ð��� 4ms(2788KB) �ҿ�Ǿ���.

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