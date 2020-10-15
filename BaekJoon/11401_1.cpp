// 11401_1.cpp
// 이항 계수 3
// 11401에서 했던 방식을 좀 더 빠르게 처리하기 위해 최적화시킬 수 있다.
// 앞에서 nCk에 대해서
// A = n!
// B = k!(n-k)!
// nCk = AB^-1 인데,
// 이를 좀 더 최적화시켜서,
// A = n*(n-1)*(n-2)*...*(n-k+1)
// B = ((n-k)!)^-1
// 이렇게 하면 factorial 구할 때의 시간과 메모리가 많이 줄어든다.
// n까지 factorial 전체를 다 구할 필요도 없고 메모리를 미리 확보할 필요도 없다.
// k, (n-k) 중 작은 값이 B로 가도록 한다.
// 예를 들어 5C3일 때,
// A = 5!/3! = 5*4
// B = ((5-3)!)^-1 = (2!)^-1
// 최적화 시키면 32ms, 33236KB --> 8ms, 1988KB 로 성능이 향상된다.

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
	// 페르마의 소정리 이용 + 분할정복을 이용한 거듭제곱 이용
	result = (A * power_func(B, p - 2)) % p;
	cout << result << "\n";
}