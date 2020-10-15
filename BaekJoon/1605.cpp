// 1605.cpp
// �ݺ� �κ� ���ڿ�
// SA�� LCP�� �̿��ϴ� ���� �ܼ��� �����̴�.
// ���� 9248���� �ߴ� �ڵ带 �̿��ϸ� �ȴ�.
// ���ѽð� 2�� �� 124ms(7,300KB)�� �ҿ�Ǿ���.
// ������� 72/329�� ���� 21.88%�� rank�Ǿ���.

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

const int limit = 200005;
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

	int n, ans = 0;
	string s;
	cin >> n >> s;
	
	getSA(s);
	getLCP(s);

	for (int i = 1; i < n; i++) ans = max(ans, LCP[i]);
	cout << ans << "\n";
}