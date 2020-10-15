// 2740.cpp
// 행렬 곱셈
// 일반적으로 수학에서 다루는 식을 이용한 행렬 곱셈이다.
// 다음의 분할정복을 이용한 행렬거듭제곱을 계산하는데 필요하다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>

using namespace std;

int A[101][101] = { {0,} };
int B[101][101] = { {0,} };
int C[101][101] = { {0,} };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M, K;
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			cin >> A[i][j];

	cin >> M >> K;
	for (int i = 1; i <= M; i++)
		for (int j = 1; j <= K; j++)
			cin >> B[i][j];

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= K; j++) {
			for (int k = 1; k <= M; k++)
				C[i][j] += A[i][k] * B[k][j];
			cout << C[i][j] << " ";
		}
		cout << "\n";
	}
}