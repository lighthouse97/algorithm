// 15576_1.cpp
// ū �� ���� (2)
// �ռ� �ߴ� 15576.cpp�� ������� �ص� ���� ������ ������, ���� ū���� ���
// �׸�ŭ �迭�� ũ�Ⱑ Ŀ���� FFT���꿡�� ��ȿ������ ������ �ִ�.
// �̸� �� �� ȿ�������� ������Ű���� �Է¼��ڸ� ���� �ϳ��� �߶� �迭�� �ִ°� �ƴ϶�
// ���� ���̸�ŭ �߶� �迭�� ������ �׸�ŭ �迭�� ũ�Ⱑ �۾����� ���� �� ���� �����̶�
// �� �� ȿ�������� ���� ����� ���� �ִ�.
// �׷��� �󸶸�ŭ �߶�� �ϴ����� ������ �ִµ�, 64bit long long ���� �迭�� ����� ���,
// �̷������δ� 8�ڸ����� �����ϳ� FFT���� double ������ casting�ؼ� ����ϴ� �������� ���е�
// ������ �����.
// �ᱹ �������� �־����� data�� ���� �޶����µ� �� ���������� 3�ڸ� ������ �ڸ��� pass�ϴ� �� ����.
// ** �ڸ� �� ���ڸ� ���� �߶�� �Ѵ�. ���ڸ����� �ڸ��� ������ ���� �ڸ����� �ڸ��� �������� ������ ���������.
// ** ����� �� �ι�° �迭���ʹ� �տ� 0�� �ִ� ���� 0���� �����ؼ� ����ؾ� �ڸ����� �´�!
// ---
// �׷���, ������ �־��� ��츦 �������� double���� ��� ��ȿ�� �Ǽ� ������ 15~16�ڸ��̹Ƿ� 15�ڸ��� ����,
// �Է� �� ���� �ִ� 300,000�ڸ��̰� ��� 9�� ä�����ٸ�, 5�ڸ� ���� �� �����ϴ�.
// (99,999 * 99,999 * (300,000/5) = 599,988,000,060,000 (15�ڸ�)), 6�ڸ� ������ 17�ڸ� ���´�.
// 5�ڸ����� ���ڸ��� �÷����� ������ test data�� ���� ������θ� ���� �ȴ�.
// ** �׸���, FFT���� long long(64bit)�� double�� casting�ϸ� ���� �߸� �� �ִٴ� warning�� ���� ���´�.
// *** �����ؼ� Ǯ��� double ���� ���� �Ǽ������� �־� 3�ڸ� ������ �°� ���Ĵ� ��� Ʋ����(WA, Wrong Answer)
//     �� ū �ڸ����� NTT(Number Theoretic Transform)�� �̿��ؾ� �Ѵ�.
// �ϴ� 3�ڸ������� �ؼ�
// ���ѽð� 2�� �� 92ms(15,424KB)�� �ҿ�Ǿ���.
// ������� 9/138�� ���� 6.52%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs, rand
#include <iomanip> // setfill, setw
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
typedef long long ll;
const ll UNIT = (ll)1e3;
const int UNIT_C = 3;

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

void poly_multiply(vector<ll>& a, vector<ll>& b, vector<ll>& result)
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
		result[i] = (ll)round(real(fa[i]));
	}
}

int main()
{
	FAST;

	string n1, n2;
	vector<ll> a, b, result;
	cin >> n1 >> n2;

	if (n1 == "0" || n2 == "0") {
		cout << 0 << "\n";
		return 0;
	}

	int l1, l2;
	l1 = (int)n1.length();
	l2 = (int)n2.length();
	for (int i = 0; i < l1; i++) { // ���ڿ� -> ���� �迭(7�ڸ�) // ���������� �ڸ��� ������ �¾ƾ� �Ѵ�!
		if ((l1 - i) % UNIT_C == 0 || a.empty()) {
			a.push_back(n1[i] - '0');
		}
		else {
			a.back() *= 10;
			a.back() += (n1[i] - '0');
		}
	}
	for (int i = 0; i < l2; i++) { // ���ڿ� -> ���� �迭(7�ڸ�)
		if ((l2 - i) % UNIT_C == 0 || b.empty()) {
			b.push_back(n2[i] - '0');
		}
		else {
			b.back() *= 10;
			b.back() += (n2[i] - '0');
		}
	}

	int digit = ((int)a.size() - 1) + ((int)b.size() - 1);
	poly_multiply(a, b, result); // convolution ���(result)�� �� index�� ���� ��������� �� �ڸ����� �ش��ϴ� ���̴�.
	for (int i = digit; i > 0; i--) { // �� �ڸ��� carry ó��
		result[i - 1] += result[i] / UNIT;
		result[i] %= UNIT;
	}
	cout << result[0];
	for (int i = 1; i < (digit + 1); i++) { // result �迭�� 0�� index���� digit index���� ���� ���ʷ� ����ϸ� �װ� �ٷ� ������ ����̴�.
		cout << setfill('0') << setw(UNIT_C) << result[i]; // 2��° �迭���� �տ� 0�� ������ 0 �ٿ��� ����Ѵ�.
	}
	cout << "\n";
}