// 11401_1.cpp
// ���� ��� 3
// 11401���� �ߴ� ����� �� �� ������ ó���ϱ� ���� ����ȭ��ų �� �ִ�.
// �տ��� nCk�� ���ؼ�
// A = n!
// B = k!(n-k)!
// nCk = AB^-1 �ε�,
// �̸� �� �� ����ȭ���Ѽ�,
// A = n*(n-1)*(n-2)*...*(n-k+1)
// B = ((n-k)!)^-1
// �̷��� �ϸ� factorial ���� ���� �ð��� �޸𸮰� ���� �پ���.
// n���� factorial ��ü�� �� ���� �ʿ䵵 ���� �޸𸮸� �̸� Ȯ���� �ʿ䵵 ����.
// k, (n-k) �� ���� ���� B�� ������ �Ѵ�.
// ���� ��� 5C3�� ��,
// A = 5!/3! = 5*4
// B = ((5-3)!)^-1 = (2!)^-1
// ����ȭ ��Ű�� 32ms, 33236KB --> 8ms, 1988KB �� ������ ���ȴ�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair

using namespace std;

int N, K;
const int p = 1000000007;

long long power_func(long long a, int b)
{
	long long n;
	if (b == 0) return 1;
	if (b % 2) return (power_func(a, b - 1)*a) % p;
	else
		n = power_func(a, b / 2);

	return (n * n) % p;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	long long A = 1, B = 1, result;
	cin >> N >> K;
	K = min(K, N-K);
	for (int i = 1; i <= K; i++) {
		A = (A * (N - i + 1)) % p;
		B = (B * i) % p;
	}
	// �丣���� ������ �̿� + ���������� �̿��� �ŵ����� �̿�
	result = (A * power_func(B, p - 2)) % p;
	cout << result << "\n";
}