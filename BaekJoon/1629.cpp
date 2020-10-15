// 1629.cpp
// ����
// ��������(����Լ�)���� �ŵ������� ����Ѵ�.
// n�� m�� ���Ѵٰ� �Ҷ�,
// f(n, m) = n*f(n, m-1) // m�� 0�̸� 1�� ����
// �̷����ϸ� ���� Ƚ���� ���� ��
// f(n,m) = f(n, m/2)*f(n,m/2) // m�� ¦��
// f(n,m) = f(n, m-1)*n // m�� Ȧ��

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // getline, string, stoi
//#include <utility> // pair
//#include <map> // map
//#include <stack>
//#include <deque>

using namespace std;

long long A, B, C;

long long power_num(long long a, long long b)
{
	long long n;
	if (b == 0) return 1;
	if (b % 2) return (power_num(a, b - 1)*a) % C;
	else
		n = power_num(a, b / 2);

	return (n * n) % C;
}

int main()
{
	cin >> A >> B >> C;
	cout << power_num(A, B) << "\n";
}