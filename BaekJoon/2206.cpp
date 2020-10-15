// 2206.cpp
// �� �μ��� �̵��ϱ�
// BFS�� �̿��ؼ� �ִ� ��θ� Ž���ϴ� �����̴�.
// ��ΰ� ª�� ���� ���� �ڸ��� ������ ������.
// �� �ϳ��� �μ� �� �ִٴ� ���� �����̴�!

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
int visited[1001][1001][2] = { { { 0, }, }, };
string themap[1001];
char dir[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

struct loc {
	int row;
	int col;
	int broken;
	loc() {}
	loc(int r, int c, int b) : row(r), col(c), broken(b) {}
};

bool in_range(int row, int col)
{
	if (row < 1 || col < 1 || row > N || col > M) return false;
	return true;
}

int bfs()
{
	loc cur;
	int nrow, ncol, size;
	int count = 0;
	queue<loc> myq;
	myq.push(loc(1, 1, 0));
	visited[1][1][0] = 1;
	while (!myq.empty()) {
		size = myq.size();
		while (size--) {
			cur = myq.front();
			myq.pop();
			if (cur.row == N && cur.col == M) return (count + 1);
			for (int i = 0; i < 4; i++) {
				nrow = cur.row + dir[i][0];
				ncol = cur.col + dir[i][1];
				// visited[y][x][0]�� �μ��� �ʰ� �湮, visited[y][x][1]�� �μ��� �湮. ��ĭ�� 2���� ��찡 �����Ѵ�.
				if (in_range(nrow, ncol) && visited[nrow][ncol][cur.broken] == 0) {
					if (themap[nrow][ncol] == '0') { // ���� �ƴ� ���
						myq.push(loc(nrow, ncol, cur.broken));
						visited[nrow][ncol][cur.broken] = 1;
					}
					else { // ���� ���(�μ��� �湮�ϰų�([0]=0,[1]=1) �μ����ʰ� �湮���� �ʰų�([0]=0,[1]=0) �̴�.
						if (cur.broken == 0) { // �ѹ��̶� ���� �ν���� ������ �湮���� ���Ѵ�.
							myq.push(loc(nrow, ncol, 1));
							visited[nrow][ncol][1] = 1;
						}
					}
				}
			}
		}
		count++;
	}
	return -1;
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
		themap[i] = tmp;
	}

	cout << bfs() << "\n";
}