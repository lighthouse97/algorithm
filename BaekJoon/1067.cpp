// 1067.cpp
// �̵�
// �������� FFT�� �̿��ϴ� �����̴�.
// ������ ���ÿ��� X={1,2,3,4}, Y={6,7,8,5} �̸�,
// X, Y�� ũ�⸦ ��� 2��÷���, a[n] = {1,2,3,4,1,2,3,4}, b[n] = {5,8,7,6,0,0,0,0}
// ���� �ΰ� FFT�� �̿��ؼ� convolution�� ���ϸ� �������� �䱸�ϴ� ��� ����� ����
// �� �� �ְ� �ȴ�. �� �߿��� ���� ū ���� ���� �ȴ�.
// �˰��� ������ ���ε�, ������ �������� ���ؼ� �ٸ� ��� Ǯ�̸� ���� ������ �����ϰ���
// �˰� �Ǿ���.
// convolution ������ ���Ǵ�� �ϳ��� ¦�� ���缭 n=8���� ������ ���� �ᱹ �������� �䱸�ϴ�
// ��� ����� ���� �� �غ��� �� ���̴�.
// ���ѽð� 2�� �� 88ms(13,052KB)�� �ҿ�Ǿ���.
// ������� 180/305�� ���� 59.01%�� rank�Ǿ���.

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
	while (n < sz) n <<= 1; // size���� ū 2^n�� ���� �����.
	n <<= 1; // m-n ������ ��� ��� *2 ���ش�. ����ȯ�ÿ� 2���� ũ�Ⱑ �ʿ��ϴ�. ������ Ʋ���� ��찡 �����.

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

	poly_multiply(a, b, result); // ���׽��� �ռ��� ���
	for (int x : result)
		S = max(S, x);
	cout << S << "\n";
}