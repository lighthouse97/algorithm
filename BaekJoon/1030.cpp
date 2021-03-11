// 1030.cpp
// ����Ż ���(fractal plane)
// ���� ���������� �̿��ϴ� �����̴�.
// ���� ������ �ݺ��Ǵ� ���¶� �����ؼ� ��� �ɰ��� ������ ������ Ǯ �� �ִ�.
// ������ �ð��� �ſ� ����(�ּ� �Ϸ�) �ɷȴ�.
// ó������ ���� ��ü�� �߸��Ǿ���!!!
// ���ϴ� ������ �ּ� fractal �������� ������ �װ��� ���ۿ� �����Ϸ��� �ߴµ�, ������ �ʹ� �����ϰ�
// �������� �ſ� �������� ���� �߻� ���ɼ��� ���Ƽ� �� ����� ����ϱ�� �Ѵ�!!!!!
// �׳� ���ϴ� ������ �� �ϳ��ϳ����� ���������� fractal �ܰ躰(s, s-1, s-2,... 1)�� ���������鼭 ��� �����̳� �ƴϳķ�
// �����Ͽ� ����� 0(white) �Ǵ� 1(black)�� �����ϱ�� �Ѵ�.
// fractal �ܰ� �Ѿ ��, ��� ������ �� �ܰ��� ��ǥ��ȯ�� �����ؾ� �Ѵ�!!!
// ���ѽð� 2�� �� 0ms(2,028KB)�� �ҿ�Ǿ���.
// ������� 150/254�� ���� 59.05%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
//#include <vector>
//#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int g_N, g_K;
int g_CS, g_CE; // center area
int g_ANS[50][50] = { {-1, }, };

int powerk(int n, int k)
{
	if (k == 0) return 1;
	int num = powerk(n, k / 2);
	if (k % 2) return num * num * n;
	else return num * num;
}

int func(int s, int r, int c)
{
	if (s == 0) return 0; // s�� 0�� �� ���� �ϳ��ۿ� ����.
	int unit = powerk(g_N, s - 1);
	int cs = g_CS * unit; // N^(S-1)���� center ����
	int ce = g_CE * unit + unit - 1;
	if (cs <= r && r <= ce && cs <= c && c <= ce) return 1; // ��� ����, black
	else {
		if (s == 1) return 0; // N^1���� ��� ������ �ƴϸ� white�̴�.
		int lr, lc, nr, nc;
		lr = r / unit; // N^(S-1) �������� ���� ��ġ ����.
		lc = c / unit;
		nr = r - (lr * unit); // N^(S-1) �������� ��ȯ�� ��ǥ ����.
		nc = c - (lc * unit);
		return func(s - 1, nr, nc);
	}
}

int main() {
	FAST;
	int s, r1, r2, c1, c2;
	cin >> s >> g_N >> g_K >> r1 >> r2 >> c1 >> c2;
	g_CS = (g_N - g_K) / 2;
	g_CE = (g_N + g_K - 2) / 2;

	for (int i = r1; i <= r2; i++)
		for (int j = c1; j <= c2; j++) {
			cout << func(s, i, j);
			if (j == c2) cout << "\n";
		}
}