// 11401.cpp
// 이항 계수 3
// 이항 계수 2의 반복문 방식을 사용하면 시간초과가 발생한다.
// 이 문제를 풀기 위해서는 페르마의 소정리를 알고 이를 이용해서 아래식을 전개해야 한다.
// nCk = n!/(K!(n-k)!)
// A = n!
// B = K!(n-k)! 일 때,
// nCk = AB^-1
// 페르마의 소정리에 의해, B^p === B (mod p) 이고
// B^(p-1)%p = 1%p => B^(p-1)%p = 1 이므로
// (AB^-1)%p = (AB^-1*1)%p = (AB^-1*B^(p-1)%p)%p = (AB^-1*B^(p-1))%p
// = (AB^(p-2))%p = ((A%p)*(B^(p-2)%p))%p
// 소요시간은 32ms에 33236KB 소요되었다.

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
	// 1부터 N까지 factorial을 구한다.
	fact[0] = fact[1] = 1;
	for (int i = 2; i <= N; i++) fact[i] = (i * fact[i - 1]) % p;
	A = fact[N];
	B = (fact[K] * fact[N - K]) % p;
	// 페르마의 소정리 이용 + 분할정복을 이용한 거듭제곱 이용
	result = ((A%p) * (power_func(B, p - 2) % p)) % p;
	cout << result << "\n";
}