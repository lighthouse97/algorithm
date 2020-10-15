// 15576.cpp
// ū �� ���� (2)
// �Էµ� �� ���� ���� �迭(int ����)�� �־ FFT�� �̿��Ͽ� convolution ������ �Ѵ�.
// �׷��� �� ����� �� index�� ���� ������ ����� �� �ڸ����� �ȴ�.
// ���� ���� ��� ����� ���� �׷��� ���´�.
// ���� ��� �迭���� ������ �ڸ����� (a�� length - 1) + (b�� length - 1) + 1 ��ŭ �ڸ����� �ȴ�.
// ���� ��� �迭�� �ε����� ������ (a�� length - 1) + (b�� length - 1) �����̴�.
// �� �ڸ����� �ش��ϴ� �ε����� ������ carryó���� �ϰ� �ε��� ó������ ���ʷ� ����ϸ� �ȴ�.
// �� ������ C++�θ� Ǯ��� �Ѵ�.
// ���ѽð� 2�� �� 352ms(42,940KB)�� �ҿ�Ǿ���.
// ������� 52/135�� ���� 38.51%�� rank�Ǿ���.

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
	for (int i = 0; i < lm; i++) { // ���ڿ� ���ڸ� int vector�� �Ҵ�
		if (i < l1) a[i] = n1[i] - '0';
		if (i < l2) b[i] = n2[i] - '0';
	}
	poly_multiply(a, b, result); // convolution ���(result)�� �� index�� ���� ��������� �� �ڸ����� �ش��ϴ� ���̴�.
	int digit = (l1 - 1) + (l2 - 1);
	for (int i = digit; i > 0; i--) { // �� �ڸ��� carry ó��
		result[i - 1] += result[i] / 10;
		result[i] %= 10;
	}
	for (int i = 0; i < (digit + 1); i++) { // result �迭�� 0�� index���� digit index���� ���� ���ʷ� ����ϸ� �װ� �ٷ� ������ ����̴�.
		cout << result[i];
	}
	cout << "\n";
}