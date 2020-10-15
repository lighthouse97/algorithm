// 15576_2.cpp
// 큰 수 곱셈 (2)
// 이번에는 FTT, IFFT 계산에서 NTT(Number Theoretic Transform) 방법을 이용해서 푼다.
// NTT는 FFT계산에서 소수점이 나오는 실수를 만드는 지수(복소수 부분)부분을 없애고
// 대신 이 지수와 동일한 기능을 하는 정수로 대체해서 모든 FTT연산을 정수로 하는 것을 말한다.
// 이 방법을 사용하면 아주 큰 수에 대해 처리할 때 실수 오차를 줄일 수 있다.
// *** 그러나 치명적인 약점(weak point)가 있다.
// 바로 항상 P의 값보다 작은 값만이 convolution 결과로 올수가 있다.
// 그래서 실제로는 정수 연산만 한다 뿐이지 아주 큰 수 계산의 잇점이 전혀 없다.
// 큰 수를 사용할 수 없다면 수행시간 측면에서 오히려 기존 FTT보다 더 느리다.
// 장점이 별로 없는 방법이라 문제에서 실제 활용은 거의 없고, 그냥 이런 방법으로도 할 수 있다는 정도로만
// 이해하고 넘어가자.
// 이론적인 것은 별도의 문서에 정리하였다.
// 결과 비교!!!
// NTT(1개 묶음) 228ms(19,472KB)
//    (2개 묶음) 116ms(11,280KB)
//    (3개 몪음) WA(Wrong Answer!)
// FTT(1개 묶음) 352ms(52,288KB)
//    (2개 묶음) 176ms(27,712KB)
//    (3개 묶음)  92ms(15,424KB)
//    (4개 묶음) WA

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs, rand
#include <iomanip> // setfill, setw
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs, hypot, round, sin, cos
#include <vector>
#include <algorithm> // sort, max, min, fill, swap
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <map>
//#include <ctime> // time
//#include <complex> // complex number
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

typedef long long ll;
const int A = 119, B = 23, P = (A << B) + 1, R = 3; // P = 998,244,353
const int UNIT = (int)1e2;
const int UNIT_C = 2;

int fast_power(int x, int y, int m)
{
	int result = 1;
	x %= m;
	while (y) {
		if (y & 1) result = (ll)result * x % m;
		y >>= 1; // y/2
		x = (ll)x * x % m;
	}
	return result;
}

void fft(vector<int>& a, bool inv)
{
	int n = (int)a.size();
	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		while (!((j ^= bit) & bit)) bit >>= 1;
		if (i < j) swap(a[i], a[j]);
	}

	for (int i = 1; i < n; i <<= 1) {
		int w = fast_power(R, (P - 1) / (2 * i), P);
		if (inv)
			w = fast_power(w, P - 2, P);		
		for (int j = 0; j < n; j += i << 1) {
			int wn = 1;
			for (int k = 0; k < i; k++) {
				int tmp = (ll)a[i + j + k] * wn % P;
				a[i + j + k] = a[j + k] - tmp;
				if (a[i + j + k] < 0) a[i + j + k] += P;
				a[j + k] += tmp;
				if (a[j + k] >= P) a[j + k] -= P;
				wn = (ll)wn * w % P;
			}
		}
	}

	if (inv) {
		int nn = fast_power(n, P - 2, P);
		for (int i = 0; i < n; i++)
			a[i] = (ll)a[i] * nn % P;			
	}
}

void poly_multiply(vector<int>& a, vector<int>& b, vector<int>& result)
{
	vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int sz = (int)max(a.size(), b.size());
	int n = 1;
	while (n < sz) n <<= 1; // size보다 큰 2^n의 수를 만든다.
	n <<= 1; // m-n 음수인 경우 고려 *2 해준다. 역변환시에 2배의 크기가 필요하다. 빠지면 틀리는 경우가 생긴다.

	fa.resize(n);
	fb.resize(n);
	fft(fa, false); // FFT
	fft(fb, false);
	for (int i = 0; i < n; i++) {
		fa[i] = (ll)fa[i] * fb[i] % P;
	}
	fft(fa, true); // IFFT
	result = vector<int>(fa.begin(), fa.end());
}

int main()
{
	FAST;

	string n1, n2;
	vector<int> a, b, result;
	cin >> n1 >> n2;

	if (n1 == "0" || n2 == "0") {
		cout << 0 << "\n";
		return 0;
	}

	int l1, l2;
	l1 = (int)n1.length();
	l2 = (int)n2.length();
	for (int i = 0; i < l1; i++) {
		if ((l1 - i) % UNIT_C == 0 || a.empty()) {
			a.push_back(n1[i] - '0');
		}
		else {
			a.back() *= 10;
			a.back() += (n1[i] - '0');
		}
	}
	for (int i = 0; i < l2; i++) {
		if ((l2 - i) % UNIT_C == 0 || b.empty()) {
			b.push_back(n2[i] - '0');
		}
		else {
			b.back() *= 10;
			b.back() += (n2[i] - '0');
		}
	}

	int digit = ((int)a.size() - 1) + ((int)b.size() - 1);
	poly_multiply(a, b, result);
	for (int i = digit; i > 0; i--) { // 각 자리수 carry 처리
		result[i - 1] += result[i] / UNIT;
		result[i] %= UNIT;
	}
	cout << result[0];
	for (int i = 1; i < (digit + 1); i++) {
		cout << setfill('0') << setw(UNIT_C) << result[i];
	}
	cout << "\n";
}