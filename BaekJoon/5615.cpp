// 5615.cpp
// 아파트 임대
// miller-rabin 소수 판정법
// 페르마의 소 정리
// 빠른 거듭제곱과 모듈러 연산
// 이 세가지가 모두 쓰인다.
// 관찰력과 머리가 좋아야 한다. 단순히 miller-rabin만 안다고 풀 수 있는
// 문제가 아니다.
// 그림을 잘 보면.. 정말 잘 봐야 한다!!!
// 2xy + x + y + (xy + xy + x + y + 1*1)  = (2x + 1)(2y + 1) = 4xy + 2x + 2y + 1
// 4xy + 2x + 2y + 1 = 2(2xy + x + y) + 1
// 즉 '2*면적 + 1'이 소수이면 있을 수 없는 면적이다.
// 그리고 소수 판별할려면 miller base a[] 배열 모두 다 통과해야 한다!
// 주의할 점!
// miller-rabin 함수에서 if(a % n == 0) 조건 체크하는 부분이 있는데 a가 항상 소수만 입력되므로 이 조건에 맞으면 반드시 TRUE를 리턴한다.
// 만일 a가 소수, non 소수 막 섞여 들어올 경우 a가 소수가 아니면서 이 조건에 걸리면 판단할 수가 없다!
// 페르마의 소 정리 전제에 a % n = 0이 아닐 경우라는 단서가 있다.
// 물론 a가 소수만 들어온다는 전제가 있으면 a % n = 0일 때 함수 수행전에 true로 바로 리턴해 버릴 수 있다.
// Olympiad > 일본정보올림피아드 > 일본정보올림피아드 예선 > JOI 2006 모의고사 2 4번
// 제한시간 1초 중 324ms(1,984KB)가 소요되었다.
// 맞은사람 66/136로 상위 48.52%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs, hypot, round
//#include <vector>
//#include <algorithm> // sort, max, min, fill
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <map>
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

typedef unsigned long long ull;

#ifdef _MSC_VER
ull mulmod(ull x, ull y, ull mod)
{
	uint64_t x_lo = (uint64_t)(uint32_t)x;
	uint64_t x_hi = x >> 32;
	uint64_t y_lo = (uint64_t)(uint32_t)y;
	uint64_t y_hi = y >> 32;

	uint64_t p0 = x_lo * y_lo;
	uint64_t p1 = x_lo * y_hi;
	uint64_t p2 = x_hi * y_lo;
	uint64_t p3 = x_hi * y_hi;

	uint32_t carry = (uint32_t)(((uint32_t)p1 + (uint32_t)p2 + (p0 >> 32)) >> 32);

	uint64_t low = (p1 << 32) + (p2 << 32) + p0;
	uint64_t high = p3 + (p1 >> 32) + (p2 >> 32) + carry;

	uint64_t tmp = 65536 % mod;
	uint64_t m64 = tmp * tmp * tmp * tmp % mod; // 2^64 % mod
	uint64_t result = ((high % mod) * m64 + (low % mod)) % mod;
	return result;
}
#else
ull mulmod(ull x, ull y, ull mod)
{
	return ((__int128)x * y) % mod;
}
#endif

ull fast_power(ull x, ull y, ull mod)
{
	ull result = 1;
	x %= mod;
	while (y) {
		if (y % 2) result = mulmod(x, result, mod); // y(지수)가 홀수
		y >>= 1; // y/2
		x = mulmod(x, x, mod);
	}
	return result;
}

// 소수이면 true를 리턴
bool miller_rabin(ull a, ull n)
{
	ull k, temp;	
	if (a % n == 0) return true; // a가 임의의 수가 아니라 항상 소수로 들어오므로 이 조건에 맞으면 당연히 소수이다.
	k = n - 1;
	while (1) {
		temp = fast_power(a, k, n);
		if(temp == n - 1) return true; // a^k % n = -1 인 경우
		if (k % 2) return (temp == 1); // a^k % n = +1 인 경우
		k >>= 1;
	}
}

int main()
{
	FAST;
	
	int n, result = 0;
	ull area;
	ull a[] = { 2, 7, 61, 0 }; // miller-rabin base
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> area;
		area = 2 * area + 1;
		int j;
		for (j = 0; j < 3; j++) {
			if (!miller_rabin(a[j], area)) { // a[] 모두 통과해야 소수
				break;
			}			
		}
		if (j > 2) result++;
	}
	cout << result << "\n";
}