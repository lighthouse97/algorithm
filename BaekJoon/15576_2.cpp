// 15576_2.cpp
// ū �� ���� (2)
// �̹����� FTT, IFFT ��꿡�� NTT(Number Theoretic Transform) ����� �̿��ؼ� Ǭ��.
// NTT�� FFT��꿡�� �Ҽ����� ������ �Ǽ��� ����� ����(���Ҽ� �κ�)�κ��� ���ְ�
// ��� �� ������ ������ ����� �ϴ� ������ ��ü�ؼ� ��� FTT������ ������ �ϴ� ���� ���Ѵ�.
// �� ����� ����ϸ� ���� ū ���� ���� ó���� �� �Ǽ� ������ ���� �� �ִ�.
// *** �׷��� ġ������ ����(weak point)�� �ִ�.
// �ٷ� �׻� P�� ������ ���� ������ convolution ����� �ü��� �ִ�.
// �׷��� �����δ� ���� ���길 �Ѵ� ������ ���� ū �� ����� ������ ���� ����.
// ū ���� ����� �� ���ٸ� ����ð� ���鿡�� ������ ���� FTT���� �� ������.
// ������ ���� ���� ����̶� �������� ���� Ȱ���� ���� ����, �׳� �̷� ������ε� �� �� �ִٴ� �����θ�
// �����ϰ� �Ѿ��.
// �̷����� ���� ������ ������ �����Ͽ���.
// ��� ��!!!
// NTT(1�� ����) 228ms(19,472KB)
//    (2�� ����) 116ms(11,280KB)
//    (3�� ����) WA(Wrong Answer!)
// FTT(1�� ����) 352ms(52,288KB)
//    (2�� ����) 176ms(27,712KB)
//    (3�� ����)  92ms(15,424KB)
//    (4�� ����) WA

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
	while (n < sz) n <<= 1; // size���� ū 2^n�� ���� �����.
	n <<= 1; // m-n ������ ��� ��� *2 ���ش�. ����ȯ�ÿ� 2���� ũ�Ⱑ �ʿ��ϴ�. ������ Ʋ���� ��찡 �����.

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
	for (int i = digit; i > 0; i--) { // �� �ڸ��� carry ó��
		result[i - 1] += result[i] / UNIT;
		result[i] %= UNIT;
	}
	cout << result[0];
	for (int i = 1; i < (digit + 1); i++) {
		cout << setfill('0') << setw(UNIT_C) << result[i];
	}
	cout << "\n";
}