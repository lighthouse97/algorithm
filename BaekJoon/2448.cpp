// 2448.cpp

#include "pch.h"
#include <iostream>

using namespace std;

const int MAX = 3072;

char canvas[MAX][MAX * 2];

void mark(int n, int y, int x) // y, x는 상단 꼭지점 위치
{
	if (n == 3) { // 기저 조건
		canvas[y][x] = '*';
		canvas[y + 1][x - 1] = '*';
		canvas[y + 1][x + 1] = '*';
		for (int i = 0; i < 5; i++) canvas[y + 2][x - 2 + i] = '*';
		return;
	}
	mark(n/2, y, x ); // 중앙 상단 삼각형
	mark(n/2, y+n/2, x-(n/2)); // 왼쪽 한단 삼각형
	mark(n/2, y+n/2, x+(n/2)); // 오른쪽 하단 삼각형
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	cin >> N;

	// initialize an array
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX * 2; j++)
			canvas[i][j] = ' ';
			
	if (N >= 3) {
		mark(N, 0, N - 1); // N, y coordinate, x coordinate
	}

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < 2 * N - 1; x++) {
			cout << canvas[y][x];
		}
		cout << "\n";
	}
}