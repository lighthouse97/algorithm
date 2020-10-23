// 9248_1.cpp
// Suffix Array
// 9248 Suffix Array�� ���ϰ� �̸� �̿��ؼ� LCP(Longest Common Prefix)��
// ���ϴ� �������� SA���� �� std�� sort(quick sort �̿�)�� �̿����� �ʰ�
// counting sort �˰����� ���� �����ؼ� �̿��Ͽ���.
// counting sort�� ������ �޸� ������ �� ���� �����ϴ� ��� �ӵ��� ������.
// SA�� �ð� ���⵵�� quick sort�� �� O(logN * NlogN)�� �ݸ� counting sort�� O(logN * N)����
// logN �� ��ŭ ó���ӵ��� ������. N�� Ŭ ���� �� ���̴� ���ϱ޼������� ��������.(N�� 100�϶� 6.64�� ���̳���)
// �׷��� counting sort�� �޸� ������ ���� �����ϱ� ������ ���ĺ��� ���� ������ ������ �����Ǿ� �ִ�
// ��쿡 ���������� ����Ѵ�.
// counting ������� Suffix Array ���ϴ� �˰����� �迭�� �ε����� ���Ƽ� �����ϴµ� ���� �ð��� �ɷȴ�!!!
// ���ѽð� 3�� �� 676ms(12,400KB)�� �ҿ�Ǿ���.
// ������� 273/545�� ���� 50.09%�� rank�Ǿ���.

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

vector<int> SA; // Suffix Array(���ĺ� ����)
vector<int> LCP; // LCP Array

void getSA(const string& str)
{
	vector<int> g, tg, ordered, cnt;
	int n = (int)str.length();
	int lim = 26 + 1; // max(257, n + 1);
	lim = max(lim, n + 1); // ó������ g�� ���ĺ������� ���� ���� ������ ���� group��ȣ�� �Ҵ�ǹǷ� ���� 0 ���� �ִ� n+1���� �� �� �ִ�.

	g.resize(n + 1);
	tg.resize(n + 1);
	SA.resize(n);
	ordered.resize(n);

	for (int i = 0; i < n; ++i) g[i] = str[i] - 'a' + 1; // ���� �� ���� 0�ϰ� 'a'�� 0�ϰ� �����ϱ� ����

	for (int t = 1; t < n; t <<= 1) {
		// i + t �������� g �����Ͽ� ����� ordered�� ����
		// (i �������� �ϸ� �� ������, i + t�� ���� 'i or ���� i + t'������ ���� ������ ���� ������ ��������)		
		cnt.clear(); cnt.resize(lim); // counting sort		
		for (int i = 0; i < n; ++i) cnt[g[min(i + t, n)]]++; // i+t�� ���� counting		
		for (int i = 1; i < lim; ++i) cnt[i] += cnt[i - 1];		
		for (int i = n - 1; i >= 0; --i) ordered[--cnt[g[min(i + t, n)]]] = i; // i+t���� g�� ����

		// i + t �������� ���ĵ� ordered�� i�������� �ѹ� �� �����ؼ� ����� SA�� �����Ѵ�.
		// (i + t) && (i) 2���� ������ �����ؼ� �����ϴ� ���̴�.(i���� ���� ���ڿ� ���� �켱������ ��������)
		cnt.clear(); cnt.resize(lim);
		for (int i = 0; i < n; ++i) cnt[g[i]]++; // i�� ���� counting		
		for (int i = 1; i < lim; ++i) cnt[i] += cnt[i - 1];		
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
		g = tg; // ���� i + t ������ ���� ���� i + t�� g�� ������Ʈ �Ѵ�. (��:t=1 ���ĵ� ���¿��� t=2 �����Ѵ�)
		if (g[SA[n - 1]] == n) break; // t<n�̶� ������ �� �Ǿ����� �������´�
	} // for
}

void getLCP(const string& str) // SA[]�� �ʿ��ϴ�.
{
	vector<int> RANK;
	int n = (int)str.size();
	int len = 0; // LCP length
	LCP.resize(n, 0);
	RANK.resize(n, 0);

	for (int i = 0; i < n; i++)
		RANK[SA[i]] = i; // SA���� ���ĺ� ������ �ٲ��ش�.
	int k, j;
	for (int i = 0; i < n; i++) {
		k = RANK[i];
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

	string s;
	cin >> s;

	getSA(s);
	getLCP(s);

	for (int x : SA) cout << x + 1 << " "; // string index�� 0���� �����ϱ� ������ 1���� �����Ϸ��� +1���ش�.
	cout << "\n";
	
	cout << "x" << " ";
	for (int i = 1; i < s.length(); i++) cout << LCP[i] << " ";		
	cout << "\n";
}