// 11479.cpp
// 서로 다른 부분 문자열의 개수 2
// 역시 SA와 LCP를 응용하는 문제이다.
// 모든 연속되는 부분 문자열의 개수를 구하는 문제인데...
// 무식하게 구하면 시간초과 발생하므로
// SA. LCP만 구하면 쉽게 구할 수 있다.
// SA 각 원소 갯수의 전체 합에서(=n(n+1)/2) LCP 원소 갯수의 전체 합을 뻬면 된다.
// 원리는 예를 들여 설명하며, 주어진 문자가 문제의 ababc 인 경우 SA 정렬하면 (괄호는 LCP)
// 1) abc
// 2) ababc (2)
// 3) bc    (0)
// 4) babc  (1)
// 5) c     (0)
// a로 시작될 때 a, ab 2개, b로 시작될 때 b개 모두 3개가 겹친다.
// 모든 연속된 부분문자열은 5(1글자)+4(2글자)+3(3글자)+2(4글자)+1(5글자)=15에서
// LCP의 합 겹치는 3개를 빼면 모두 12개가 중복 제외한 모든 연속 부분 문지열의 개수가 된다.
// 뮨자열의 길이가 최대 1,000,000 까지라 결과값이 int 범위가 넘어가서 long long type으로 저장해야 한다.
// 제한시간 5초 중 500ms(27,080KB)가 소요되었다.
// 맞은사람 44/222로 상위 19.81%에 rank되었다.

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

int SA[limit]; // Suffix Array(알파벳 순서)
int LCP[limit]; // LCP Array

int g[limit];
int tg[limit];
int ordered[limit];
int cnt[limit];

void getSA(const string& str)
{
	int n = (int)str.length();
	int gm = max(alim + 1, n + 1); // 처음에는 g가 알파벳이지만 이후 정렬 순서에 따라 group번호로 할당되므로 끝에 0 포함 최대 n+1까지 올 수 있다.

	for (int i = 0; i < n; ++i) g[i] = str[i];
	for (int t = 1; t < n; t <<= 1) {
		// i + t 기준으로 g 정렬하여 결과를 ordered에 저장
		// (i 기준으로 하면 안 맞지만, i + t에 의해 'i or 직전 i + t'에서의 같은 문자일 때의 순서는 정해진다)						
		for (int i = 0; i < gm; i++) cnt[i] = 0;
		for (int i = 0; i < n; ++i) cnt[g[min(i + t, n)]]++; // i+t에 대한 counting		
		for (int i = 1; i < gm; ++i) cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; --i) ordered[--cnt[g[min(i + t, n)]]] = i; // i+t에서 g를 정렬

		// i + t 기준으로 정렬된 ordered를 i기준으로 한번 더 정렬해서 결과를 SA에 저장한다.
		// (i + t) && (i) 2개의 기준을 적용해서 정렬하는 셈이다.(i에서 같은 문자에 대한 우선순위가 정해진다)		
		for (int i = 0; i < gm; i++) cnt[i] = 0;
		for (int i = 0; i < n; ++i) cnt[g[i]]++; // i에 대한 counting		
		for (int i = 1; i < gm; ++i) cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; --i) SA[--cnt[g[ordered[i]]]] = ordered[i];

		auto cmp = [&](int i, int j) { // lamda function, [&] : variable capture(call by reference)
			if (g[i] == g[j]) return g[i + t] < g[j + t];
			return g[i] < g[j];
		};

		tg[SA[0]] = 1; // 1부터 시작
		for (int i = 1; i < n; ++i) {
			if (cmp(SA[i - 1], SA[i])) tg[SA[i]] = tg[SA[i - 1]] + 1;
			else tg[SA[i]] = tg[SA[i - 1]];
		}
		for (int i = 0; i < n; i++) g[i] = tg[i]; // 다음 i + t 적용을 위해 현재 i + t로 g를 업데이트 한다. (예:t=1 정렬된 상태에서 t=2 정렬한다)		
		if (g[SA[n - 1]] == n) break; // t<n이라도 정렬이 다 되었으면 빠져나온다
	} // for
}

void getLCP(const string& str) // SA[]가 필요하다.
{
	int n = (int)str.size();
	int len = 0; // LCP length	

	for (int i = 0; i < n; i++)
		g[SA[i]] = i; // SA값을 알파벳 순서로 바꿔준다.
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