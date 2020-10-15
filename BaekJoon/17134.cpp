// 17134.cpp
// ������� ����
// FFT�� Ǯ �� �ִ� �����ε� �Ǹ����� ã�� ���ؼ� �ع��� ���� ������ ���¿���
// 1% �� ������ ���Ͽ� Ǯ�̸� �����Ҵ�.
// Ǯ���� �ٽ��� '1)Ȧ�� �Ҽ� + 2)���̼Ҽ�'�� ������ �ǹǷ�
// 1), 2) ������ ���ؼ� 2���� 100,000�� �迭�� ����� �ش�Ǵ� �ε����� 1�� ǥ���Ѵ�.
// �׸��� �� �迭�� FFT�� �̿��� convolution ó���ϸ� ����� �ε����� ���� ������� ������
// �ش�Ǵ� ����(����� ��)�̴�.
// Ȧ���Ҽ� + ���̼Ҽ��� ���ձ����� �����ߴµ� �̸� �ٷ� �����ع��� ���� ��������.
// �̸� �ε��� ó���ϸ� ���� ������ Ǯ �� �ִ� ���ε�...
// ���ѽð� 2�� �� 732ms(91,020KB)�� �ҿ�Ǿ���.
// ������� 22/74�� ���� 29.72%�� rank�Ǿ���.

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

void get_prime(vector<int>& a, int size) // �����佺�׳׽��� ü(Sieve of Eratosthenes) �̿�
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
	a[2] = 0; // Ȧ���� �Ҽ��̱� ����
	poly_multiply(a, b, result);

	int T, num;
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> num;
		cout << result[num] << "\n";
	}
}