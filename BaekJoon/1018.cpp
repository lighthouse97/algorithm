// 1018.cpp
// 체스판, 막막해서 힌트를 보고야 말았다!

#include "pch.h"
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

// chess black
char CW[8][8] = { {'W','B','W','B','W','B','W','B'},
						{'B','W','B','W','B','W','B','W'},
						{'W','B','W','B','W','B','W','B'},
						{'B','W','B','W','B','W','B','W'},
						{'W','B','W','B','W','B','W','B'},
						{'B','W','B','W','B','W','B','W'},
						{'W','B','W','B','W','B','W','B'},
						{'B','W','B','W','B','W','B','W'} };

// chess white
char CB[8][8] = { {'B','W','B','W','B','W','B','W'},
						{'W','B','W','B','W','B','W','B'},
						{'B','W','B','W','B','W','B','W'},
						{'W','B','W','B','W','B','W','B'},
						{'B','W','B','W','B','W','B','W'},
						{'W','B','W','B','W','B','W','B'},
						{'B','W','B','W','B','W','B','W'},
						{'W','B','W','B','W','B','W','B'} };

char board[50][52] = { {0,} };

int count_diff(int x, int y)
{
	int wcount=0, bcount=0;
	for (int i = y; i < y + 8; i++) {
		for (int j = x; j < x + 8; j++) {
			if (CW[i - y][j - x] != board[i][j]) wcount++;
			if (CB[i - y][j - x] != board[i][j]) bcount++;
		}
	}
	return min(wcount, bcount);
}

int main()
{
	int N, M;
	int result = 100;
	scanf("%d %d", &N, &M);

	for (int i = 0; i < N; i++) {
			scanf("%s", &board[i]);
	}

	for (int i = 0; i < N-7; i++) {
		for (int j = 0; j < M-7; j++) {
			result = min(result, count_diff(j,i));
		}
	}
	printf("%d\n", result);
}