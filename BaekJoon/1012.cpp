// 1012.cpp
// 유기농배추
// 앞의 2667과 거의 유사한 문제이다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
//#include <queue>

using namespace std;

int T, N, M, K;
char visited[51][51] = { { 0, }, };
char mymap[51][51] = { { 0, }, };
char dir[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

bool in_range(int row, int col)
{
	if (row < 1 || col < 1 || row > N || col > M) return false;
	return true;
}

void dfs(int row, int col)
{
	int nrow, ncol;
	for (int i = 0; i < 4; i++) {
		nrow = row + dir[i][0];
		ncol = col + dir[i][1];
		if (in_range(nrow, ncol)) {
			if (mymap[nrow][ncol] == 1 && visited[nrow][ncol] == 0) {
				visited[nrow][ncol] = 1;
				dfs(nrow, ncol);
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int cnt = 0;
	int r, c;
	cin >> T;
	for (int t = 0; t < T; t++) {
		cin >> M >> N >> K;
		cnt = 0;
		memset(mymap, 0x0, sizeof(mymap));
		memset(visited, 0x0, sizeof(visited));
		for (int i = 1; i <= K; i++) {
			cin >> c >> r;
			mymap[r + 1][c + 1] = 1;
		}

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				if (mymap[i][j] == 1 && visited[i][j] == 0) {
					visited[i][j] = 1;
					cnt++;
					dfs(i, j);
				}
			}
		}

		cout << cnt << "\n";
	}
}