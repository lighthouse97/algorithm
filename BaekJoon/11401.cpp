// 11401.cpp
// ���� ��� 3
// ���� ��� 2�� �ݺ��� ����� ����ϸ� �ð��ʰ��� �߻��Ѵ�.
// �� ������ Ǯ�� ���ؼ��� �丣���� �������� �˰� �̸� �̿��ؼ� �Ʒ����� �����ؾ� �Ѵ�.
// nCk = n!/(K!(n-k)!)
// A = n!
// B = K!(n-k)! �� ��,
// nCk = AB^-1
// �丣���� �������� ����, B^p === B (mod p) �̰�
// B^(p-1)%p = 1%p => B^(p-1)%p = 1 �̹Ƿ�
// (AB^-1)%p = (AB^-1*1)%p = (AB^-1*B^(p-1)%p)%p = (AB^-1*B^(p-1))%p
// = (AB^(p-2))%p = ((A%p)*(B^(p-2)%p))%p
// �ҿ�ð��� 32ms�� 33236KB �ҿ�Ǿ���.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair

using namespace std;

int N, K;
long long fact[4000001] = { 0, };
const int p = 1000000007;

long long power_func(long long a, long long b)
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
	long long A, B, result;
	cin >> N >> K;
	// 1���� N���� factorial�� ���Ѵ�.
	fact[0] = fact[1] = 1;
	for (int i = 2; i <= N; i++) fact[i] = (i * fact[i - 1]) % p;
	A = fact[N];
	B = (fact[K] * fact[N - K]) % p;
	// �丣���� ������ �̿� + ���������� �̿��� �ŵ����� �̿�
	result = ((A%p) * (power_func(B, p - 2) % p)) % p;
	cout << result << "\n";
}