// 5615.cpp
// ����Ʈ �Ӵ�
// miller-rabin �Ҽ� ������
// �丣���� �� ����
// ���� �ŵ������� ��ⷯ ����
// �� �������� ��� ���δ�.
// �����°� �Ӹ��� ���ƾ� �Ѵ�. �ܼ��� miller-rabin�� �ȴٰ� Ǯ �� �ִ�
// ������ �ƴϴ�.
// �׸��� �� ����.. ���� �� ���� �Ѵ�!!!
// 2xy + x + y + (xy + xy + x + y + 1*1)  = (2x + 1)(2y + 1) = 4xy + 2x + 2y + 1
// 4xy + 2x + 2y + 1 = 2(2xy + x + y) + 1
// �� '2*���� + 1'�� �Ҽ��̸� ���� �� ���� �����̴�.
// �׸��� �Ҽ� �Ǻ��ҷ��� miller base a[] �迭 ��� �� ����ؾ� �Ѵ�!
// ������ ��!
// miller-rabin �Լ����� if(a % n == 0) ���� üũ�ϴ� �κ��� �ִµ� a�� �׻� �Ҽ��� �ԷµǹǷ� �� ���ǿ� ������ �ݵ�� TRUE�� �����Ѵ�.
// ���� a�� �Ҽ�, non �Ҽ� �� ���� ���� ��� a�� �Ҽ��� �ƴϸ鼭 �� ���ǿ� �ɸ��� �Ǵ��� ���� ����!
// �丣���� �� ���� ������ a % n = 0�� �ƴ� ����� �ܼ��� �ִ�.
// ���� a�� �Ҽ��� ���´ٴ� ������ ������ a % n = 0�� �� �Լ� �������� true�� �ٷ� ������ ���� �� �ִ�.
// Olympiad > �Ϻ������ø��ǾƵ� > �Ϻ������ø��ǾƵ� ���� > JOI 2006 ���ǰ�� 2 4��
// ���ѽð� 1�� �� 324ms(1,984KB)�� �ҿ�Ǿ���.
// ������� 66/136�� ���� 48.52%�� rank�Ǿ���.

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
		if (y % 2) result = mulmod(x, result, mod); // y(����)�� Ȧ��
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
		if(temp == n - 1) return true; // a^k % n = -1 �� ���
		if (k % 2) return (temp == 1); // a^k % n = +1 �� ���
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
			if (!miller_rabin(a[j], area)) { // a[] ��� ����ؾ� �Ҽ�
				break;
			}			
		}
		if (j > 2) result++;
	}
	cout << result << "\n";
}