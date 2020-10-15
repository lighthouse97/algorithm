// 7569.cpp
// �丶��
// BFS�� �����ϴ� �����̴�.
// ���� �丶�䰡 2D�� �ٷ���ٸ� �̹� �丶��� 3D �����̴�.
// �迭 ��� �͸� �ٸ��� ������ BFS�� Ž���ϴ� ���� �����ϴ�.

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

int N, M, H;
int box[101][101][101] = { { { 0, }, }, };
int visited[101][101][101] = { { { 0, }, }, };
char dir[6][3] = { {-1, 0, 0}, {0, -1, 0}, {0, 0, 1}, {0, 1, 0}, {0, 0, -1}, {1, 0, 0} };

struct coord {
	int height;
	int row;
	int col;
	coord() {}
	coord(int h, int r, int c) : height(h), row(r), col(c) {}
};

bool in_range(int height, int row, int col)
{
	if (height < 1 || row < 1 || col < 1 || height > H || row > N || col > M) return false;
	return true;
}

int bfs()
{
	coord cur;
	int nheight, nrow, ncol, result = 0;
	queue<coord> myq;
	for (int i = 1; i <= H; i++) {
		for (int j = 1; j <= N; j++) 
			for(int k = 1; k <= M; k++) {
				if (box[i][j][k] == 1) {
					myq.push(coord(i, j, k));
					visited[i][j][k] = 1;
			}
		}
	}
	while (!myq.empty()) {
		cur = myq.front();
		myq.pop();
		for (int i = 0; i < 6; i++) {
			nheight = cur.height + dir[i][0];
			nrow = cur.row + dir[i][1];
			ncol = cur.col + dir[i][2];
			if (in_range(nheight, nrow, ncol)) {
				if (box[nheight][nrow][ncol] != -1 && visited[nheight][nrow][ncol] == 0) {
					myq.push(coord(nheight, nrow, ncol));
					visited[nheight][nrow][ncol] = visited[cur.height][cur.row][cur.col] + 1;
				}
			}
		}
		if (visited[cur.height][cur.row][cur.col] > result) result = visited[cur.height][cur.row][cur.col];
	}
	// ��� 1 -> visited[][][] ��� 1
	// ��� -1 -> visited[][][] ��� 0
	// ���� -> visited[][][] > 0
	// �ϳ��� 0 -> visited[][][] ������� -1
	for (int i = 1; i <= H; i++)
		for (int j = 1; j <= N; j++)
			for(int k = 1; k <= M; k++)
				if (box[i][j][k] != -1 && visited[i][j][k] == 0)
					return -1;

	return (result - 1);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> M >> N >> H;
	for (int i = 1; i <= H; i++)
		for (int j = 1; j <= N; j++)
			for(int k = 1; k <= M; k++)
				cin >> box[i][j][k];

	cout << bfs() << "\n";
}