// 11725.cpp
// Ʈ���� �θ�ã��
// �׸��� Ʈ������ '��Ʈ���� Ʈ��'��� �߱� ������ ������ ���� Ʈ���� �ƴϴ�.
// �̴� ����� �׷����� ���� �ȴ�.
// ����� �׷������� ������ ���� ��Ʈ�� ��� ��Ʈ�κ��� dfsŽ���� �ϸ鼭 �� ����� �θ�
// ����ϸ� �ȴ�.
// ���ѽð� 1�ʿ��� �ҿ�ð��� 52ms(11280KB)�� ���Դ�.

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