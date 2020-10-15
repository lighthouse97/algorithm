// 2447.cpp
// mark start - 10

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

const int max_number = 2188;

int star[max_number][max_number];

void mark_star(int y, int x, int n)
{
	int step = n / 3;

	if (n == 3) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (i == step && j == step) star[i + y][j + x] = 0;
				else star[i+y][j+x] = 1;
		return;
	}

	for (int i = 0; i < n; i+=step) {
		for (int j = 0; j < n; j+=step) {
			if (i == step && j == step) continue;
			mark_star(i+y, j+x, step);
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	for (int i = 0; i < max_number; i++)
		for (int j = 0; j < max_number; j++)
			star[i][j] = 0;

	cin >> N;
	mark_star(0, 0, N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << ((star[i][j] == 1) ? "*" : " ");
		}
		cout << "\n";
	}
}
