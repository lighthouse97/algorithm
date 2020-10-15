// 9248_2.cpp
// 9248_1 방법을 좀 더 빠르게 최적화 시킨다.
// 단순 연습이므로 크게 의미를 둘 필요는 없다!
// 1) 시간 많이 잡아먹는 vector를 배열로 바꾸고,
// 2) SA구하는 함수에서 t < n 이라도 SA 정렬이 완료되면(g[SA[n - 1]] == n)
//    루프를 빠져나오도록 해서 루프의 횟수를 줄였다.
// 1) + 2) => 272ms(14,596KB)
// 2) only => 288ms(12,400KB)
// vector에 의한 요인은 16ms(약5%) 정도 밖에 안된다.
// 제한시간 3초 중 272ms(14,596KB)가 소요되었다.
// 맞은사람 117/545로 상위 21.46%에 rank되었다.

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

const int limit = 500005;
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

	string s;
	cin >> s;
	int n = (int)s.length();

	getSA(s);
	getLCP(s);
	
	for (int i = 0; i < n; i++) cout << SA[i] + 1 << " "; // string index가 0부터 시작하기 때문에 1부터 시작하려면 +1해준다.
	cout << "\n";

	cout << "x" << " ";
	for (int i = 1; i < n; i++) cout << LCP[i] << " ";
	cout << "\n";
}