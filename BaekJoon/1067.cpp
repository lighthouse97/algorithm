// 1067.cpp
// 이동
// 전형적인 FFT를 이용하는 문제이다.
// 문제의 예시에서 X={1,2,3,4}, Y={6,7,8,5} 이면,
// X, Y의 크기를 모두 2배늘려서, a[n] = {1,2,3,4,1,2,3,4}, b[n] = {5,8,7,6,0,0,0,0}
// 으로 두고 FFT를 이용해서 convolution을 구하면 문제에서 요구하는 모든 경우의 수가
// 다 모여 있게 된다. 이 중에서 가장 큰 값만 고르면 된다.
// 알고보면 간단한 것인데, 원리를 이해하지 못해서 다른 사람 풀이를 보고 한참을 연구하고서야
// 알게 되었다.
// convolution 연산의 정의대로 하나씩 짝을 맞춰서 n=8까지 전개해 보면 결국 문제에서 요구하는
// 모든 경우의 수를 다 해보게 될 것이다.
// 제한시간 2초 중 88ms(13,052KB)가 소요되었다.
// 맞은사람 180/305로 상위 59.01%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs, rand
#include <iostream>
//#include <cstring> // memset
#include <cmath> // pow, sqrt, fabs, hypot, round, sin, cos, round
#include <vector>
#include <algorithm> // sort, max, min, fill, swap
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <map>
//#include <ctime> // time
#include <complex> // complex number
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

typedef complex<double> base;
#ifdef _MSC_VER
const double M_PI = 3.14159265358979323846;
#endif

// fast fourier transform algorithm
void fft(vector<base>& a, bool inv)
{
	int n = (int)a.size();
	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		while (!((j ^= bit) & bit)) bit >>= 1;
		if (i < j) swap(a[i], a[j]);
	}

	for (int i = 1; i < n; i <<= 1) {
		double x = inv ? M_PI / i : -M_PI / i;
		base w = { cos(x), sin(x) };
		for (int j = 0; j < n; j += i << 1) {
			base th = { 1, 0 };
			for (int k = 0; k < i; k++) {
				base tmp = a[i + j + k] * th;
				a[i + j + k] = a[j + k] - tmp;
				a[j + k] += tmp;
				th *= w;
			}
		}
	}

	if (inv) {
		for (int i = 0; i < n; i++) {
			a[i] /= n;
		}
	}
}

void poly_multiply(vector<int>& a, vector<int>& b, vector<int>& result)
{
	vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int sz = (int)max(a.size(), b.size());
	int n = 1;
	while (n < sz) n <<= 1; // size보다 큰 2^n의 수를 만든다.
	n <<= 1; // m-n 음수인 경우 고려 *2 해준다. 역변환시에 2배의 크기가 필요하다. 빠지면 틀리는 경우가 생긴다.

	fa.resize(n);
	fb.resize(n);
	fft(fa, false); // FFT
	fft(fb, false);
	for (int i = 0; i < n; i++) {
		fa[i] *= fb[i];
	}
	fft(fa, true); // IFFT
	result.resize(n);

	for (int i = 0; i < n; i++) {
		result[i] = (int)round(real(fa[i]));
	}
}

int main()
{
	FAST;

	int N, S = 0;
	vector<int> a, b, result;

	cin >> N;
	a.resize(N*2, 0);
	b.resize(N*2, 0);

	int num;
	for (int i = 0; i < N; i++) { // a = {1,2,3,4,1,2,3,4}
		cin >> num;
		a[i] = a[i + N] = num;		
	}
	for (int i = 0; i < N; i++) { // b = {5,8,7,6,0,0,0,0}
		cin >> b[N - i - 1];
	}

	poly_multiply(a, b, result); // 다항식의 합성곱 계산
	for (int x : result)
		S = max(S, x);
	cout << S << "\n";
}