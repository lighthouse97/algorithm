// 1193.cpp
// 분수찾기

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int sum = 0, layer = 0;
	int x = 0, y = 0, count = 0;
	int N;

	cin >> N;

	if (N == 1) {
		layer = 1;
		y = x = 0;
	}
	else if (N > 1) {
		sum = 1;
		while (N >= sum) {
			layer++;
			sum += layer;
		}
		count = N - (sum - layer);
		if (layer % 2 == 0) {
			x = layer - count - 1;
			y = count;
		}
		else {
			x = count;
			y = layer - count - 1;
		}
	}
	cout << y+1 << "/" << x+1 << "\n";
}