// 10531.cpp
// Golf Bot
// ICPC > Regionals > Europe > Southwestern European Regional Contest > SWERC 2014 C번
// FFT(DFT, IDFT) 알고리즘을 사용하는 문제이다.
// 그런데, 이걸 FFT 활용할 수 있도록 다항식의 합성곱 형식으로 변형할 수 있어야 한다.
// 이걸 못해서 결국은 풀이를 보고서야 이해했다.
// 특정 knob번호 n이 존재할 때 a(n)=1, 아니면 a(n)=0이라 하면(예, 문제예제에서 a(5)=1, a(2)=0)
// a(n) 2개를 조합해서 원하는 거리가 하나라도 나오면 된다.
// 예를 들어 거리 4를 보내려면, c(4) = a(0)a(4) + a(1)a(3) + a(2)a(2) + a(3)a(1), 이 값이 0이 아니면 거리 4로 보낼 수 있고,
// 이 값이 0이면 거리 5로 보낼 수 없게 된다. +가 or 역할. (a4한번 또는 a2 두번 또는 a3, a1 한 번씩 중 하나만 맞으면 된다)
// a(0)은 존재하지 않지만 문제 풀이를 위해 1로 둔다.
// 이를 다항식의 convolution으로 표현이 가능한데, c[m] = SIGMA(n=0~n-1)a(n)a(m-n)
// c(m)이 거리 m으로 보낼 수 있는지 여부(정확히는 거리 m으로 보낼 수 있는 경우의 수)
// 여기까지만 하면 a(n)을 FFT(결과는 A(n))변환하고 A(n)A(n)의 IFFT한 결과가 c[m]이 된다.
// 즉 2번까지만 shot을 날릴 수가 있어서 다항식의 합셩곱의 형태로 바꾸어 FFT를 이용하여 문제를 풀 수가 있지
// 3번 이상 shot이 허용되면 FFT로는 문제를 바로 풀 수가 없고 다른 어떤 방법을 또 생각해야 한다.
// 만일 FFT를 사용하지 않고 그대로 단순하게 loop 반복헤서 풀면 문제의 의도대로 당연히 시간 초과가 발생할 것이다!!!
// 제한시간 2초 중 180ms(23,484KB)가 소요되었다.
// 맞은사람 59/162로 상위 36.41%에 rank되었다.

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
const int max_num = 200001;
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

	int N, M;
	int count = 0;
	vector<int> a, dist, result;
	a.resize(max_num, 0);	

	// knob 거리 입력
	cin >> N;
	int d, maxnum = 0;
	for (int i = 0; i < N; i++) {
		cin >> d;
		a[d] = 1;
		maxnum = max(maxnum, d);
	}
	a[0] = 1;

	// hole까지의 거리 입력
	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> d;
		dist.push_back(d);
		maxnum = max(maxnum, d);
	}
	a.resize(maxnum + 1);

	poly_multiply(a, a, result); // 다항식의 합성곱 계산

	for (int x : dist) {
		if (result[x]) count++;
	}
	cout << count << "\n";
}

