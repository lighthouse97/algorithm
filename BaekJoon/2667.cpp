// 2667.cpp
// 단지번호붙이기
// DFS 또는 BFS를 이용해서 푸는데, 여기서는 DFS를 이용해서 풀어보았다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
//#include <queue>

using namespace std;

int N;
char visited[26][26] = { { 0, }, };
string mymap[26];
int dir[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

bool in_range(int row, int col)
{
	if (row < 1 || col < 1 || row > N || col > N) return false;
	return true;
}

int dfs(int row, int col)
{
	int count = 1;
	int nrow, ncol;
	for (int i = 0; i < 4; i++) {
		nrow = row + dir[i][0];
		ncol = col + dir[i][1];
		if (in_range(nrow, ncol)) {
			if (mymap[nrow][ncol] == '1' && visited[nrow][ncol] == 0) {
				visited[nrow][ncol] = 1;
				count += dfs(nrow, ncol);
			}
		}
	}
	return count;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int cnt = 0;
	string tmp;
	vector<int> result;
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> tmp;
		tmp = '0' + tmp;
		mymap[i] = tmp;
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (mymap[i][j] == '1' && visited[i][j] == 0) {
				visited[i][j] = 1;
				cnt = dfs(i, j);
				result.push_back(cnt);
			}
		}
	}
	sort(result.begin(), result.end());
	cout << result.size() << "\n";
	for (int k : result)
		cout << k << "\n";
}