// 15576.cpp
// 큰 수 곱셈 (2)
// 입력된 두 수를 각각 배열(int 벡터)에 넣어서 FFT를 이용하여 convolution 연산을 한다.
// 그러면 그 결과의 각 index의 값이 곱셈의 결과의 각 자리수가 된다.
// 직접 예를 들어 계산해 보면 그렇게 나온다.
// 최종 결과 배열에서 곱셈의 자리수는 (a의 length - 1) + (b의 length - 1) + 1 만큼 자리수가 된다.
// 최종 결과 배열의 인덱스로 따지면 (a의 length - 1) + (b의 length - 1) 까지이다.
// 각 자리수에 해당하는 인덱스의 값에서 carry처리를 하고 인덱스 처음부터 차례로 출력하면 된다.
// 이 문제는 C++로만 풀어야 한다.
// 제한시간 2초 중 352ms(42,940KB)가 소요되었다.
// 맞은사람 52/135로 상위 38.51%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs, rand
#include <iostream>
//#include <cstring> // memset
#include <cmath> // pow, sqrt, fabs, hypot, round, sin, cos, round
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

	string n1, n2;
	vector<int> a, b, result;
	cin >> n1 >> n2;

	if (n1 == "0" || n2 == "0") {
		cout << 0 << "\n";
		return 0;
	}

	int l1, l2, lm;
	l1 = (int)n1.length();
	l2 = (int)n2.length();
	lm = max(l1, l2);
	a.resize(lm, 0);
	b.resize(lm, 0);
	for (int i = 0; i < lm; i++) { // 문자열 숫자를 int vector에 할당
		if (i < l1) a[i] = n1[i] - '0';
		if (i < l2) b[i] = n2[i] - '0';
	}
	poly_multiply(a, b, result); // convolution 결과(result)의 각 index의 값이 곱셈결과의 각 자리수에 해당하는 값이다.
	int digit = (l1 - 1) + (l2 - 1);
	for (int i = digit; i > 0; i--) { // 각 자리수 carry 처리
		result[i - 1] += result[i] / 10;
		result[i] %= 10;
	}
	for (int i = 0; i < (digit + 1); i++) { // result 배열의 0번 index부터 digit index까지 값을 차례로 출력하면 그게 바로 곱셈의 결과이다.
		cout << result[i];
	}
	cout << "\n";
}