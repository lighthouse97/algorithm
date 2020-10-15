// 1949.cpp
// ��� ����
// �� ������ ���� 2533(��ȸ�� ����)�� ���������� Ʈ�� Ž���ϸ鼭
// �������α׷����� �̿��Ͽ� ������ ���� ���� �ð����� ã�Ƴ��� �����̴�.
// �������α׷��� ������ �� �����ؾ� �Ѵ�.
// ���ѽð� 2�� �� 8ms(3252KB)�� �ҿ�Ǿ���.
// ������� 515 �� 344�� ���� 66.79%�� rank�Ǿ���.
// �� �� ����ȭ ��Ű�� ��Ʈ���� �Լ��� 2�� �θ��� �ʰ� �ѹ��� �ҷ��� �ذ��� �� �ִ�.
// �� �� �ҿ�ð��� 4ms���ϰ� ��ǥ�̴�.
// ����ȭ ��Ű�� ���ѽð� 2�� �� 4ms(3252KB)�� �ҿ�Ǿ���.
// ������� 515 �� 301�� ���� 58.44%�� rank�Ǿ���.
// ...
// ����ȭ���Ѽ� �ٽɿ� ���� �������� ���ϰ� �ֺ����� �ʹ� ��Ŵ��� �ð��� �ʹ� ���� ��ƸԾ���.
// ������ �ǵ��� �� �ľ��ϰ� ���� ������� �ð��� ��Ƹ԰� ������ ������ ��ġ�� �ִٴ� ���� ���� �ľ��ϰ�
// ������ ������ ���� ���ư� �� �ִ� ����� ��� �ؾ� �ڴ�.

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
vector<vector<int>> DP; // [][1] : current ����, [][0] : current ������
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