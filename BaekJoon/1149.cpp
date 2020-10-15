// 1149.cpp
// R,G,B, Dynamic Programming이 필요하다.

#include "pch.h"
#include <iostream>
//#include <cstdio>
//#include <utility> // pair
//#include <vector> // vector
#include <algorithm> // min
//#include <string>

using namespace std;

int cost[1001][3] = { {0,0,0}, };
int tc[1001][3] = { {0,0,0}, }; // total cost

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N;
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> cost[i][0] >> cost[i][1] >> cost[i][2];

	tc[1][0] = cost[1][0];
	tc[1][1] = cost[1][1];
	tc[1][2] = cost[1][2];
	for (int i = 2; i <= N; i++) {
		tc[i][0] = min(tc[i - 1][1], tc[i - 1][2]) + cost[i][0];
		tc[i][1] = min(tc[i - 1][0], tc[i - 1][2]) + cost[i][1];
		tc[i][2] = min(tc[i - 1][0], tc[i - 1][1]) + cost[i][2];
	}
	cout << min({ tc[N][0], tc[N][1], tc[N][2] }) << "\n";
}
