// 1520.cpp
// 내리막 길
// DP 문제이다.
// recursive로 풀어서 수행시간은 24ms 걸렸다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
#include <cstring> // memset
//#include <vector>
//#include <algorithm> // max
//#include <climits> // INT_MAX
//#include <string>
//#include <utility> // pair

using namespace std;

int M, N;
int PATH[501][501] = { { 0, }, };
int DP[501][501] = { { 0, }, };

int function(int i, int j)
{
	if (DP[i][j] != -1) return DP[i][j];
	if (i > M || j > N || i < 1 || j < 1) return 0;
	if (i == M && j == N) return 1;
	DP[i][j] = 0;
	if (PATH[i][j] > PATH[i][j + 1]) DP[i][j] += function(i, j+1);
	if(PATH[i][j] > PATH[i+1][j]) DP[i][j] += function(i+1, j);
	if(PATH[i][j] > PATH[i-1][j]) DP[i][j] += function(i - 1, j);
	if (PATH[i][j] > PATH[i][j-1]) DP[i][j] += function(i, j - 1);
	return DP[i][j];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	memset(DP, -1, sizeof(DP));
	cin >> M >> N;
	for (int i = 1; i <= M; i++)
		for (int j = 1; j <= N; j++)
			cin >> PATH[i][j];

	cout << function(1,1) << "\n";
}