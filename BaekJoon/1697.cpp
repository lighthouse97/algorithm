// 1697.cpp
// ���ٲ���
// BFS�� �̿��ؼ� �ִ� ��θ� Ž���ϴ� �����̴�.
// ��ΰ� ª�� ���� ���� �ڸ��� ������ ������.
// ������ ������ 12851, 13549, 13913 �� �ִ�.

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

int N, K;
int visited[100001] = { 0, };

int move(int x, int type)
{
	if (type == 0) return x - 1;
	else if (type == 1) return x + 1;
	else return x * 2;
}

bool in_range(int loc)
{
	if (loc < 0 || loc > 100000) return false;
	return true;
}

int bfs()
{
	int temp;
	int nloc;
	queue<int> myq;
	myq.push(N);
	visited[N] = 1;
	while (!myq.empty()) {
		temp = myq.front();
		myq.pop();
		if (temp == K) break;
		for (int i = 0; i < 3; i++) {
			nloc = move(temp, i);
			if (in_range(nloc) && visited[nloc] == 0) {
				myq.push(nloc);
				visited[nloc] = visited[temp] + 1;
			}
		}
	}
	return (visited[K] - 1);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> K;

	cout << bfs() << "\n";
}