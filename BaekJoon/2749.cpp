// 2749.cpp
// 피보나치 수 3
// 피보나치 수열을 행렬로 표시하는 공식부터 알아야 한다.
// 그리고 앞에서 한 행렬의 거듭제곱을 이용한다.
// 유사문제는 2747, 2748, 10826, 10870 이 있다.
// 피보나치로 검색하면 아주 많이 나온다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>

using namespace std;

typedef vector < vector <long long> > lmat;

const int SIZE = 2;
const int mod = 1000000;

lmat matrix_mul(lmat& A, lmat& B)
{
	lmat result(SIZE + 1, vector<long long>(SIZE + 1)); // vector n개를 vector<long long>(n)값으로 채운다
	for (int i = 1; i <= SIZE; i++)
		for (int j = 1; j <= SIZE; j++)
			for (int k = 1; k <= SIZE; k++) {
				result[i][j] += A[i][k] * B[k][j];
				result[i][j] %= mod;
			}

	return result;
}

lmat matrix_power(lmat& A, long long p)
{
	lmat result(SIZE + 1, vector<long long>(SIZE + 1));
	if (p == 1) return A;
	result = matrix_power(A, p / 2);
	result = matrix_mul(result, result);
	if (p % 2) result = matrix_mul(result, A);

	return result;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	long long N;
	cin >> N;
	lmat A(SIZE + 1, vector<long long>(SIZE + 1));
	lmat result(SIZE + 1, vector<long long>(SIZE + 1));
	for (int i = 1; i <= SIZE; i++)
		for (int j = 1; j <= SIZE; j++)
			A[i][j] = 1;
	A[SIZE][SIZE] = 0;

	if(N > 0) result = matrix_power(A, N);
	cout << ((N > 0) ? result[1][2] : 1) << "\n";
}