// 15576_1.cpp
// 큰 수 곱셈 (2)
// 앞서 했던 15576.cpp의 방법으로 해도 전혀 문제가 없지만, 아주 큰수의 경우
// 그만큼 배열의 크기가 커져서 FFT연산에서 비효율적인 측면이 있다.
// 이를 좀 더 효율적으로 개선시키려면 입력숫자를 숫자 하나씩 잘라서 배열에 넣는게 아니라
// 일정 길이만큼 잘라서 배열에 넣으면 그만큼 배열의 크기가 작아져서 같은 두 수의 곱셈이라도
// 좀 더 효율적으로 빨리 계산할 수가 있다.
// 그러면 얼마만큼 잘라야 하느냐의 문제가 있는데, 64bit long long 형의 배열로 잡았을 경우,
// 이론적으로는 8자리까지 가능하나 FFT에서 double 형으로 casting해서 계산하는 과정에서 정밀도
// 오차가 생긴다.
// 결국 문제에서 주어지는 data에 따라 달라지는데 이 문제에서는 3자리 정도로 자르면 pass하는 거 같다.
// ** 자를 때 뒷자리 부터 잘라야 한다. 앞자리부터 자르면 마지막 남은 자리수가 자르는 갯수보다 작으면 오류생긴다.
// ** 출력할 때 두번째 배열부터는 앞에 0이 있는 수는 0까지 포함해서 출력해야 자리수가 맞다!
// ---
// 그런데, 엄밀히 최악의 경우를 따져보면 double형의 경우 유효한 실수 범위가 15~16자리이므로 15자리로 보고,
// 입력 두 수가 최대 300,000자리이고 모두 9로 채워진다면, 5자리 끊을 때 안전하다.
// (99,999 * 99,999 * (300,000/5) = 599,988,000,060,000 (15자리)), 6자리 끊으면 17자리 나온다.
// 5자리부터 한자리씩 올려가며 문제의 test data에 따라 통과여부를 보면 된다.
// ** 그리고, FFT에서 long long(64bit)을 double로 casting하면 값이 잘릴 수 있다는 warning이 많이 나온다.
// *** 적용해서 풀어보니 double 형에 대한 실수오차가 있어 3자리 까지만 맞고 이후는 모두 틀린다(WA, Wrong Answer)
//     더 큰 자리수는 NTT(Number Theoretic Transform)를 이용해야 한다.
// 일단 3자리까지만 해서
// 제한시간 2초 중 92ms(15,424KB)가 소요되었다.
// 맞은사람 9/138로 상위 6.52%에 rank되었다.

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
	for (int i = 0; i < l1; i++) { // 문자열 -> 숫자 배열(7자리) // 끝에서부터 자르는 단위가 맞아야 한다!
		if ((l1 - i) % UNIT_C == 0 || a.empty()) {
			a.push_back(n1[i] - '0');
		}
		else {
			a.back() *= 10;
			a.back() += (n1[i] - '0');
		}
	}
	for (int i = 0; i < l2; i++) { // 문자열 -> 숫자 배열(7자리)
		if ((l2 - i) % UNIT_C == 0 || b.empty()) {
			b.push_back(n2[i] - '0');
		}
		else {
			b.back() *= 10;
			b.back() += (n2[i] - '0');
		}
	}

	int digit = ((int)a.size() - 1) + ((int)b.size() - 1);
	poly_multiply(a, b, result); // convolution 결과(result)의 각 index의 값이 곱셈결과의 각 자리수에 해당하는 값이다.
	for (int i = digit; i > 0; i--) { // 각 자리수 carry 처리
		result[i - 1] += result[i] / UNIT;
		result[i] %= UNIT;
	}
	cout << result[0];
	for (int i = 1; i < (digit + 1); i++) { // result 배열의 0번 index부터 digit index까지 값을 차례로 출력하면 그게 바로 곱셈의 결과이다.
		cout << setfill('0') << setw(UNIT_C) << result[i]; // 2번째 배열부터 앞에 0이 있으면 0 붙여서 출력한다.
	}
	cout << "\n";
}