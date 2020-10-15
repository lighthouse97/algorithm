// 7576.cpp
// 토마토
// BFS를 응용하는 문제이다.

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

int N, M;
int box[1001][1001] = { { 0, }, };
int visited[1001][1001] = { { 0, }, };
char dir[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

struct coord {
	int row;
	int col;
	coord() {}
	coord(int r, int c) : row(r), col(c) {}
};

bool in_range(int row, int col)
{
	if (row < 1 || col < 1 || row > N || col > M) return false;
	return true;
}

int bfs()
{
	coord cur;
	int nrow, ncol, result = 0;
	queue<coord> myq;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (box[i][j] == 1) {
				myq.push(coord(i, j));
				visited[i][j] = 1;
			}
		}
	}
	while (!myq.empty()) {
		cur = myq.front();
		myq.pop();
		if (visited[cur.row][cur.col] > result) result = visited[cur.row][cur.col];
		for (int i = 0; i < 4; i++) {
			nrow = cur.row + dir[i][0];
			ncol = cur.col + dir[i][1];
			if (in_range(nrow, ncol)) {
				if (box[nrow][ncol] != -1 && visited[nrow][ncol] == 0) {
					myq.push(coord(nrow, ncol));
					visited[nrow][ncol] = visited[cur.row][cur.col] + 1;
				}
			}
		}
	}
	// 모두 1 -> visited[][] 모두 1
	// 모두 -1 -> visited[][] 모두 0
	// 정상 -> visited[][] > 0
	// 하나라도 0 -> visited[][] 상관없이 -1
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			if (box[i][j] != -1 && visited[i][j] == 0)
				return -1;
			
	return (result - 1);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> M >> N;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			cin >> box[i][j];

	cout << bfs() << "\n";
}