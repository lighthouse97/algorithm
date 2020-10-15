// 1167.cpp
// Ʈ���� ����
// �� ���� ���� Ʈ�� �׸� ���� ������ �׷��� �����̴�.
// ����� �׷����̰� ��� ������ dfs �Ǵ� bfs Ž���� �ؼ� ���� �Ÿ��� ��
// ������ �Ÿ��� ���ϸ� ������ �̷��� �ϸ� �ð��� ���� �ɸ���
// ������ �������� leaf node(���� �Ÿ��� �� ����)�� ���ϰ� �� lead node����
// Ž���� �ؼ� ���� �Ÿ��� �� ���� �Ÿ��� ���ϸ� Ʈ���� ������ ���� �� �ִ�.
// �ҿ�ð��� ���ѽð� 2�ʿ��� 88ms(8944KB) �ҿ�Ǿ���.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
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

int V;
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
	cin >> V;
	GRAPH.resize(V + 1);
	DP.resize(V + 1, -1);
	for (int i = 0; i <= V - 1; i++) {
		cin >> parent;
		while (true) {
			cin >> child;
			if (child == -1) break;
			cin >> val;
			GRAPH[parent].push_back(node(child, val));
		}
	}
	bfs(1);
	DP = vector<int>(V + 1, -1); // reset DP
	cout << bfs(LEAF) << "\n";
}
