// 17134.cpp
// 르모앙의 추측
// FFT로 풀 수 있는 문제인데 실마리를 찾지 못해서 해법에 거의 근접한 상태에서
// 1% 더 나가지 못하여 풀이를 보고말았다.
// 풀이의 핵심은 '1)홀수 소수 + 2)세미소수'로 구성이 되므로
// 1), 2) 각각에 대해서 2개의 100,000개 배열을 만들고 해당되는 인덱스에 1을 표시한다.
// 그리고 두 배열을 FFT를 이용한 convolution 처리하면 결과의 인덱스의 값이 르모앙의 추측에
// 해당되는 갯수(경우의 수)이다.
// 홀수소수 + 세미소수의 조합까지는 생각했는데 이를 바로 적용해버린 것이 문제였다.
// 이를 인덱스 처리하면 아주 간단히 풀 수 있는 것인데...
// 제한시간 2초 중 732ms(91,020KB)가 소요되었다.
// 맞은사람 22/74로 상위 29.72%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs, rand
//#include <iomanip> // setfill, setw
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

void get_prime(vector<int>& a, int size) // 에라토스테네스의 체(Sieve of Eratosthenes) 이용
{
	a[0] = a[1] = 0;
	for (int i = 2; i*i < size; i++) {
		if (a[i] == 0) continue;
		for (int j = 2*i; j < size; j+=i) {
			a[j] = 0;
		}
	}
}

int main()
{
	FAST;

	int max_num = 1000001;
	vector<int> a(max_num, 1), b(max_num, 0), result;
	get_prime(a, max_num);
	for (int i = 0; i < max_num / 2; i++) {
		if (a[i]) b[i * 2] = 1;
	}
	a[2] = 0; // 홀수인 소수이기 때문
	poly_multiply(a, b, result);

	int T, num;
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> num;
		cout << result[num] << "\n";
	}
}