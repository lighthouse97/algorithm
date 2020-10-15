// 10830.cpp
// ��� ����
// ��İ���(2740)�� ���������� �̿��� �ŵ�����(1629)�� �����Ͽ�
// ������ Ǭ��.

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

int N;
long long B;
const int mod = 1000;

lmat matrix_mul(lmat& A, lmat& B)
{
	lmat result(N+1, vector<long long>(N+1)); // vector n���� vector<long long>(n)������ ä���
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			for (int k = 1; k <= N; k++) {
				result[i][j] += A[i][k] * B[k][j];
				result[i][j] %= mod;
			}
			
	return result;
}

lmat matrix_power(lmat& A, long long p)
{
	lmat result(N + 1, vector<long long>(N + 1));
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

	cin >> N >> B;
	lmat A(N+1, vector<long long>(N+1));
	lmat result(N+1, vector<long long>(N+1));
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			cin >> A[i][j];
	
	result = matrix_power(A, B);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			cout << ((B == 1) ? result[i][j] % mod : result[i][j]) << " "; // B = 1 �� ���� ����ؾ� �Ѵ�!
		cout << "\n";
	}
}