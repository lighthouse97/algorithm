// 4149.cpp
// ū �� ���μ�����
// 64bit ū ���� ���μ����ض� SQRT(N)���� �ݺ������� ã�� ������δ� �翬�� �ð��ʰ� �߻��Ѵ�!
// ��� ���� �˰��� �����̴�.
// �� ������ Ǯ�� ���� ���� ������ ������ ����.
// 1) PollardRoh �˰���
// 2) Miller-Rabin �Ҽ� ������ �˰���
// 3) 2)�� ���� ���� �ŵ� ���� �˰���
// Pollard-Roh �˰��� �������� ��Ŵٰ� ���ѷ��� �ڵ带 ����� ���� �ð� �ʰ� �߻��ؼ� 
// �װ� ã���� ����뿡 ���� �Ϸ����� �ɷȴ�.
// �˰��� �� ���������� ���ϰ� ���ϰ� ������ �Ϸ��� �ϴٺ��� ������ �������� �����.
// Contest > Waterloo's local Programming Contests > 19 June, 2011 B��
// ���ѽð� 1�� �� 44ms(1,988KB)�� �ҿ�Ǿ���.
// ������� 26/144�� ���� 18.05%�� rank�Ǿ���.

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

// �Ҽ��̸� true�� ����
bool miller_rabin(ull a, ull n)
{
	ull k, temp;
	if (a % n == 0) return true; // a�� ������ ���� �ƴ϶� �׻� �Ҽ��� �����Ƿ� �� ���ǿ� ������ �翬�� �Ҽ��̴�.
	k = n - 1;
	while (1) {
		temp = fast_power(a, k, n);
		if (temp == n - 1) return true; // a^k % n = -1 �� ���
		if (k % 2) return (temp == 1); // a^k % n = +1 �� ���
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
		if (!miller_rabin(alist[i], n)) // a[] ��� ����ؾ� �Ҽ�
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
	return pollard_roh(d); // �Ҽ��� ����� �����ϱ� ����
}

int main()
{
	FAST;

	ull n, div;
	vector<ull> result;
	srand(time(NULL));

	cin >> n;

	while (!(n % 2)) { // ¦��(��� 2�� ��� ã�´�)
		result.push_back(2);
		n >>= 1;
	}
	if (n > 1) {
		while (!isPrime(n)) { // �Ҽ��� �ƴ� ���(�Ҽ��� ����� ��� ã�´�)
			div = pollard_roh(n);
			while (n % div == 0) {
				result.push_back(div);
				n /= div;
			}
			if (n == 1) break;
		}
		if(n > 1) result.push_back(n); // �Ҽ��� ���
	}	  	
	sort(result.begin(), result.end());
	for (ull x : result)
		cout << x << "\n";
}