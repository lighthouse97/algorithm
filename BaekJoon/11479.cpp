// 11479.cpp
// ���� �ٸ� �κ� ���ڿ��� ���� 2
// ���� SA�� LCP�� �����ϴ� �����̴�.
// ��� ���ӵǴ� �κ� ���ڿ��� ������ ���ϴ� �����ε�...
// �����ϰ� ���ϸ� �ð��ʰ� �߻��ϹǷ�
// SA. LCP�� ���ϸ� ���� ���� �� �ִ�.
// SA �� ���� ������ ��ü �տ���(=n(n+1)/2) LCP ���� ������ ��ü ���� ���� �ȴ�.
// ������ ���� �鿩 �����ϸ�, �־��� ���ڰ� ������ ababc �� ��� SA �����ϸ� (��ȣ�� LCP)
// 1) abc
// 2) ababc (2)
// 3) bc    (0)
// 4) babc  (1)
// 5) c     (0)
// a�� ���۵� �� a, ab 2��, b�� ���۵� �� b�� ��� 3���� ��ģ��.
// ��� ���ӵ� �κй��ڿ��� 5(1����)+4(2����)+3(3����)+2(4����)+1(5����)=15����
// LCP�� �� ��ġ�� 3���� ���� ��� 12���� �ߺ� ������ ��� ���� �κ� �������� ������ �ȴ�.
// ���ڿ��� ���̰� �ִ� 1,000,000 ������ ������� int ������ �Ѿ�� long long type���� �����ؾ� �Ѵ�.
// ���ѽð� 5�� �� 500ms(27,080KB)�� �ҿ�Ǿ���.
// ������� 44/222�� ���� 19.81%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const int limit = 1000005;
const int alim = 128; // ASCII limit

int SA[limit]; // Suffix Array(���ĺ� ����)
int LCP[limit]; // LCP Array

int g[limit];
int tg[limit];
int ordered[limit];
int cnt[limit];

void getSA(const string& str)
{
	int n = (int)str.length();
	int gm = max(alim + 1, n + 1); // ó������ g�� ���ĺ������� ���� ���� ������ ���� group��ȣ�� �Ҵ�ǹǷ� ���� 0 ���� �ִ� n+1���� �� �� �ִ�.

	for (int i = 0; i < n; ++i) g[i] = str[i];
	for (int t = 1; t < n; t <<= 1) {
		// i + t �������� g �����Ͽ� ����� ordered�� ����
		// (i �������� �ϸ� �� ������, i + t�� ���� 'i or ���� i + t'������ ���� ������ ���� ������ ��������)						
		for (int i = 0; i < gm; i++) cnt[i] = 0;
		for (int i = 0; i < n; ++i) cnt[g[min(i + t, n)]]++; // i+t�� ���� counting		
		for (int i = 1; i < gm; ++i) cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; --i) ordered[--cnt[g[min(i + t, n)]]] = i; // i+t���� g�� ����

		// i + t �������� ���ĵ� ordered�� i�������� �ѹ� �� �����ؼ� ����� SA�� �����Ѵ�.
		// (i + t) && (i) 2���� ������ �����ؼ� �����ϴ� ���̴�.(i���� ���� ���ڿ� ���� �켱������ ��������)		
		for (int i = 0; i < gm; i++) cnt[i] = 0;
		for (int i = 0; i < n; ++i) cnt[g[i]]++; // i�� ���� counting		
		for (int i = 1; i < gm; ++i) cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; --i) SA[--cnt[g[ordered[i]]]] = ordered[i];

		auto cmp = [&](int i, int j) { // lamda function, [&] : variable capture(call by reference)
			if (g[i] == g[j]) return g[i + t] < g[j + t];
			return g[i] < g[j];
		};

		tg[SA[0]] = 1; // 1���� ����
		for (int i = 1; i < n; ++i) {
			if (cmp(SA[i - 1], SA[i])) tg[SA[i]] = tg[SA[i - 1]] + 1;
			else tg[SA[i]] = tg[SA[i - 1]];
		}
		for (int i = 0; i < n; i++) g[i] = tg[i]; // ���� i + t ������ ���� ���� i + t�� g�� ������Ʈ �Ѵ�. (��:t=1 ���ĵ� ���¿��� t=2 �����Ѵ�)		
		if (g[SA[n - 1]] == n) break; // t<n�̶� ������ �� �Ǿ����� �������´�
	} // for
}

void getLCP(const string& str) // SA[]�� �ʿ��ϴ�.
{
	int n = (int)str.size();
	int len = 0; // LCP length	

	for (int i = 0; i < n; i++)
		g[SA[i]] = i; // SA���� ���ĺ� ������ �ٲ��ش�.
	int k, j;
	for (int i = 0; i < n; i++) {
		k = g[i];
		if (k) {
			j = SA[k - 1];
			while (i + len < n && j + len < n && str[i + len] == str[j + len]) len++;
			LCP[k] = len;
			if (len) len--;
		}
	}
}

int main()
{
	FAST;

	int n;
	long long ans, sum = 0;
	string s;
	cin >> s;
	n = (int)s.length();

	getSA(s);
	getLCP(s);

	ans = (1LL * n) * (n + 1) / 2;
	for (int i = 1; i < n; i++) sum += LCP[i];
	ans -= sum;
	cout << ans << "\n";
}