// 2178.cpp
// 미로탐색
// BFS를 이용해서 최단 경로를 탐색하는 문제이다.
// 경로가 짧은 것이 먼저 자리를 차지해 버린다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
#include <queue>

using namespace std;

int N, M;
int visited[101][101] = { { 0, }, };
string maze[101];
char dir[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

struct axis {
	int row;
	int col;
	axis() {}
	axis(int r, int c) : row(r), col(c) {}
};

bool in_range(int row, int col)
{
	if (row < 1 || col < 1 || row > N || col > M) return false;
	return true;
}

int bfs()
{
	axis temp;
	int nrow, ncol;
	queue<axis> myq;
	myq.push(axis(1, 1));
	visited[1][1] = 1;
	while (!myq.empty()) {
		temp = myq.front();
		myq.pop();
		if (temp.row == N && temp.col == M) break;
		for (int i = 0; i < 4; i++) {
			nrow = temp.row + dir[i][0];
			ncol = temp.col + dir[i][1];
			if (in_range(nrow, ncol)) {
				if (maze[nrow][ncol] == '1' && visited[nrow][ncol] == 0) {
					myq.push(axis(nrow, ncol));
					visited[nrow][ncol] = visited[temp.row][temp.col] + 1;
				}
			}
		}
	}
	return visited[N][M];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;
	string tmp;

	for (int i = 1; i <= N; i++) {
		cin >> tmp;
		tmp = '0' + tmp;
		maze[i] = tmp;
	}

	cout << bfs() << "\n";
}