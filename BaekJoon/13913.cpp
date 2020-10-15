// 13913.cpp
// 숨바꼭질 4
// '숨바꼭질 1'(1697)과 동일한데 최소시간의 경로까지 같이 출력해야 한다.
// BFS를 이용한 최단 경로 탐색 + 최단거리 역추적 문제이다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
#include <stack>
//#include <set>
//#include <cmath> // sqrt
#include <queue>

using namespace std;

int N, K;
int visited[100001][2] = { { 0, }, }; // [][0] : 누적시간, [][1] : 이전 위치

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
	visited[N][0] = 1;
	while (!myq.empty()) {
		temp = myq.front();
		myq.pop();
		if (temp == K) break;
		for (int i = 0; i < 3; i++) {
			nloc = move(temp, i);
			if (in_range(nloc) && visited[nloc][0] == 0) {
				myq.push(nloc);
				visited[nloc][0] = visited[temp][0] + 1;
				visited[nloc][1] = temp;
			}
		}
	}
	return (visited[K][0] - 1);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int next;
	stack<int> myst;
	cin >> N >> K;
	for (int i = 0; i < 100001; i++)
		visited[i][1] = -1;
	cout << bfs() << "\n";
	next = K;
	while (next != -1) {
		myst.push(next);
		next = visited[next][1];
	}
	while (!myst.empty()) {
		cout << myst.top() << " ";
		myst.pop();
	}
	cout << "\n";
}