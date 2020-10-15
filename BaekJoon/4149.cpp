// 4149.cpp
// 큰 수 소인수분해
// 64bit 큰 수의 소인수분해라서 SQRT(N)까지 반복문으로 찾는 방식으로는 당연히 시간초과 발생한다!
// 고급 수학 알고리즘 문제이다.
// 이 문제를 풀기 위한 선결 과제는 다음과 같다.
// 1) PollardRoh 알고리즘
// 2) Miller-Rabin 소수 판정법 알고리즘
// 3) 2)를 위한 빠른 거듭 제곱 알고리즘
// Pollard-Roh 알고리즘 구현에서 헤매다가 무한루프 코드를 만들어 놓고 시간 초과 발생해서 
// 그거 찾느라 디버깅에 꼬박 하루종일 걸렸다.
// 알고리즘 잘 이해하지도 못하고 급하게 구현만 하려고 하다보니 문제가 마구마구 생긴다.
// Contest > Waterloo's local Programming Contests > 19 June, 2011 B번
// 제한시간 1초 중 44ms(1,988KB)가 소요되었다.
// 맞은사람 26/144로 상위 18.05%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
#include <cstdlib> // abs, rand
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs, hypot, round
#include <vector>
#include <algorithm> // sort, max, min, fill, swap
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <map>
#include <ctime> // time
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

typedef unsigned long long ull;
vector<ull> alist = { 2,3,5,7,11,13,17,19,23,29,31,37 };

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

ull my_gcd(ull a, ull b)
{
	ull r;
	if (a < b) swap(a, b);	
	while (b) {
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

ull fast_power(ull x, ull y, ull mod)
{
	ull result = 1;
	x %= mod;
	while (y) {
		if (y % 2) result = mulmod(x, result, mod);
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
		if (temp == n - 1) return true; // a^k % n = -1 인 경우
		if (k % 2) return (temp == 1); // a^k % n = +1 인 경우
		k >>= 1;
	}
}

bool isPrime(ull n)
{	
	if (n == 1) return false;
	if (n == 2 || n == 3) return true;
	if (n % 2 == 0) return false;

	if (n <= 10000000000ULL) {
		for (ull i = 3; i*i < n + 1; i++)
			if (n % i == 0) return false;
		return true;
	}
	
	for (int i = 0; i < 11; i++) {
		if (alist[i] == n) return true;		
		if (!miller_rabin(alist[i], n)) // a[] 모두 통과해야 소수
			return false;
	}
	return true;
}

ull pollard_roh(ull n) {
	ull x, y, c, d;
	ull diff;
	
	if (n == 1) return 1;
	if (n % 2 == 0) return 2;	
		
	x = (rand() % (n - 2)) + 2; // [2, n)
	y = x;
	c = (rand() % (n - 1)) + 1; // [1, n)
	d = 1;

	while (d == 1) {
		x = (fast_power(x, 2, n) + c + n) % n;
		y = (fast_power(y, 2, n) + c + n) % n;
		y = (fast_power(y, 2, n) + c + n) % n;
		diff = (x > y) ? x - y : y - x;
		d = my_gcd(diff, n);
		if (d == n) return pollard_roh(d);
	}
	if (isPrime(d)) return d;
	return pollard_roh(d); // 소수인 약수만 리턴하기 위함
}

int main()
{
	FAST;

	ull n, div;
	vector<ull> result;
	srand(time(NULL));

	cin >> n;

	while (!(n % 2)) { // 짝수(약수 2를 모두 찾는다)
		result.push_back(2);
		n >>= 1;
	}
	if (n > 1) {
		while (!isPrime(n)) { // 소수가 아닌 경우(소수인 약수를 모두 찾는다)
			div = pollard_roh(n);
			while (n % div == 0) {
				result.push_back(div);
				n /= div;
			}
			if (n == 1) break;
		}
		if(n > 1) result.push_back(n); // 소수인 경우
	}	  	
	sort(result.begin(), result.end());
	for (ull x : result)
		cout << x << "\n";
}