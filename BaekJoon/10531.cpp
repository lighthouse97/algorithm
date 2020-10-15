// 10531.cpp
// Golf Bot
// ICPC > Regionals > Europe > Southwestern European Regional Contest > SWERC 2014 C��
// FFT(DFT, IDFT) �˰����� ����ϴ� �����̴�.
// �׷���, �̰� FFT Ȱ���� �� �ֵ��� ���׽��� �ռ��� �������� ������ �� �־�� �Ѵ�.
// �̰� ���ؼ� �ᱹ�� Ǯ�̸� ������ �����ߴ�.
// Ư�� knob��ȣ n�� ������ �� a(n)=1, �ƴϸ� a(n)=0�̶� �ϸ�(��, ������������ a(5)=1, a(2)=0)
// a(n) 2���� �����ؼ� ���ϴ� �Ÿ��� �ϳ��� ������ �ȴ�.
// ���� ��� �Ÿ� 4�� ��������, c(4) = a(0)a(4) + a(1)a(3) + a(2)a(2) + a(3)a(1), �� ���� 0�� �ƴϸ� �Ÿ� 4�� ���� �� �ְ�,
// �� ���� 0�̸� �Ÿ� 5�� ���� �� ���� �ȴ�. +�� or ����. (a4�ѹ� �Ǵ� a2 �ι� �Ǵ� a3, a1 �� ���� �� �ϳ��� ������ �ȴ�)
// a(0)�� �������� ������ ���� Ǯ�̸� ���� 1�� �д�.
// �̸� ���׽��� convolution���� ǥ���� �����ѵ�, c[m] = SIGMA(n=0~n-1)a(n)a(m-n)
// c(m)�� �Ÿ� m���� ���� �� �ִ��� ����(��Ȯ���� �Ÿ� m���� ���� �� �ִ� ����� ��)
// ��������� �ϸ� a(n)�� FFT(����� A(n))��ȯ�ϰ� A(n)A(n)�� IFFT�� ����� c[m]�� �ȴ�.
// �� 2�������� shot�� ���� ���� �־ ���׽��� �ռͰ��� ���·� �ٲپ� FFT�� �̿��Ͽ� ������ Ǯ ���� ����
// 3�� �̻� shot�� ���Ǹ� FFT�δ� ������ �ٷ� Ǯ ���� ���� �ٸ� � ����� �� �����ؾ� �Ѵ�.
// ���� FFT�� ������� �ʰ� �״�� �ܼ��ϰ� loop �ݺ��켭 Ǯ�� ������ �ǵ���� �翬�� �ð� �ʰ��� �߻��� ���̴�!!!
// ���ѽð� 2�� �� 180ms(23,484KB)�� �ҿ�Ǿ���.
// ������� 59/162�� ���� 36.41%�� rank�Ǿ���.

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

	int N, M;
	int count = 0;
	vector<int> a, dist, result;
	a.resize(max_num, 0);	

	// knob �Ÿ� �Է�
	cin >> N;
	int d, maxnum = 0;
	for (int i = 0; i < N; i++) {
		cin >> d;
		a[d] = 1;
		maxnum = max(maxnum, d);
	}
	a[0] = 1;

	// hole������ �Ÿ� �Է�
	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> d;
		dist.push_back(d);
		maxnum = max(maxnum, d);
	}
	a.resize(maxnum + 1);

	poly_multiply(a, a, result); // ���׽��� �ռ��� ���

	for (int x : dist) {
		if (result[x]) count++;
	}
	cout << count << "\n";
}

