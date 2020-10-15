// 9248.cpp
// Suffix Array
// Suffix Array�� ���ϴ� �ǹ�-���̾ �˰���(Manber-Myers Algorithm)��
// SA�� �̿��Ͽ� LCP(Longest Common Prefix)�� ���ϴ� �˰�����
// �̿��Ѵ�.
// �� �ΰ����� ���������� �̿��ϴ� ������ ���� ������ ���� �� �ΰ�����
// �˰� ������ �ȴ�.
// ���ѽð� 3�� �� 880ms(10,444KB)�� �ҿ�Ǿ���.
// ������� 457/545�� ���� 83.85%�� rank�Ǿ���.
// �� �� ����ȭ ��Ű�� 524ms(8,492KB) �ҿ�ȴ�.
// SA���ϴ� �Լ����� t < n �̶� SA ������ �Ϸ�Ǹ�(g[SA[n - 1]] == n - 1), ������ ���������� �Ͽ���.

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
vector<int> LCP;

void getSA(const string& str) // Manber-Myers algorithm
{
	vector<int> g; // SA group(SA ����)
	vector<int> tg; // temporary group
	int n = (int)str.length();
	int t = 1; // ���ڿ����� ������ ��ġ
	SA.resize(n, 0);
	g.resize(n + 1, -1); // ���� ª�� ���ں��� �̹� ������ �������� ������ n+1�� ��� g[n] = -1 �� �ָ� �ȴ�. n+1 �Ѿ�� ���ϴ� ���� ���ٰ� ���� �Ѵ�
	tg.resize(n + 1, -1);

	for (int i = 0; i < n; i++) { // initialize
		SA[i] = i;
		g[i] = str[i] - 'a';
	}

	auto cmp = [&](int i, int j) { // lamda function, [&] : variable capture(call by reference)
		if (g[i] == g[j]) return g[i + t] < g[j + t];
		return g[i] < g[j];
	};

	while (t <= n) {
		sort(SA.begin(), SA.end(), cmp); // Ư�� t���� SA ������Ʈ
		tg[SA[0]] = 0;
		for (int i = 1; i < n; i++) {
			if (cmp(SA[i - 1], SA[i])) tg[SA[i]] = tg[SA[i - 1]] + 1; // Ư�� t���� tg(g) ������Ʈ
			else tg[SA[i]] = tg[SA[i - 1]];
		}		
		g = tg; // tg�� g�� update
		
		if (g[SA[n - 1]] == n - 1) break; // t<n�̶� ������ �� �Ǿ����� �������´�
		t <<= 1; // t*2 ����		
	}	
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

	for (int x : SA)
		cout << x + 1 << " "; // string index�� 0���� �����ϱ� ������ 1���� �����Ϸ��� +1���ش�.
	cout << "\n";
	cout << "x ";
	for (int i = 1; i < s.length(); i++)
		cout << LCP[i] << " ";		
	cout << "\n";
}