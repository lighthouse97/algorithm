// 6064.cpp
// Ä«À× ´Þ·Â

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

long long find_year(int m, int n, int x, int y)
{ 
	long long sum_x = x, sum_y = y;
	long long result = -1;

	for (sum_x = x; sum_x <= m * n; sum_x += m) {
		if ((sum_x % n == y) || (sum_x % n == 0 && n == y)) {
			result = sum_x;
			break;
		}
	}
	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	int T;
	int M, N, x, y;
	long long year;

	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> M >> N >> x >> y;
		year = find_year(M, N, x, y);
		cout << year << "\n";
	}
}