// 9248_1.cpp
// Suffix Array
// 9248 Suffix Array를 구하고 이를 이용해서 LCP(Longest Common Prefix)를
// 구하는 문제에서 SA구할 때 std의 sort(quick sort 이용)를 이용하지 않고
// counting sort 알고리즘을 직접 구현해서 이용하였다.
// counting sort의 이점은 메모리 공간은 더 많이 차지하는 대신 속도가 빠르다.
// SA의 시간 복잡도가 quick sort일 때 O(logN * NlogN)인 반면 counting sort는 O(logN * N)으로
// logN 배 만큼 처리속도가 빠르다. N이 클 수록 그 차이는 기하급수적으로 벌어진다.(N이 100일때 6.64배 차이난다)
// 그러나 counting sort는 메모리 공간을 많이 차지하기 때문에 알파벳과 같이 원소의 범위가 한정되어 있는
// 경우에 제한적으로 사용한다.
// counting 방식으로 Suffix Array 구하는 알고리즘이 배열과 인덱스가 많아서 이해하는데 무지 시간이 걸렸다!!!
// 제한시간 3초 중 676ms(12,400KB)가 소요되었다.
// 맞은사람 273/545로 상위 50.09%에 rank되었다.

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

vector<int> SA; // Suffix Array(알파벳 순서)
vector<int> LCP; // LCP Array

void getSA(const string& str)
{
	vector<int> g, tg, ordered, cnt;
	int n = (int)str.length();
	int lim = 26 + 1; // max(257, n + 1);
	lim = max(lim, n + 1); // 처음에는 g가 알파벳이지만 이후 정렬 순서에 따라 group번호로 할당되므로 끝에 0 포함 최대 n+1까지 올 수 있다.

	g.resize(n + 1);
	tg.resize(n + 1);
	SA.resize(n);
	ordered.resize(n);

	for (int i = 0; i < n; ++i) g[i] = str[i] - 'a' + 1; // 문자 끝 다음 0하고 'a'의 0하고 구분하기 위함

	for (int t = 1; t < n; t <<= 1) {
		// i + t 기준으로 g 정렬하여 결과를 ordered에 저장
		// (i 기준으로 하면 안 맞지만, i + t에 의해 'i or 직전 i + t'에서의 같은 문자일 때의 순서는 정해진다)		
		cnt.clear(); cnt.resize(lim); // counting sort		
		for (int i = 0; i < n; ++i) cnt[g[min(i + t, n)]]++; // i+t에 대한 counting		
		for (int i = 1; i < lim; ++i) cnt[i] += cnt[i - 1];		
		for (int i = n - 1; i >= 0; --i) ordered[--cnt[g[min(i + t, n)]]] = i; // i+t에서 g를 정렬

		// i + t 기준으로 정렬된 ordered를 i기준으로 한번 더 정렬해서 결과를 SA에 저장한다.
		// (i + t) && (i) 2개의 기준을 적용해서 정렬하는 셈이다.(i에서 같은 문자에 대한 우선순위가 정해진다)
		cnt.clear(); cnt.resize(lim);
		for (int i = 0; i < n; ++i) cnt[g[i]]++; // i에 대한 counting		
		for (int i = 1; i < lim; ++i) cnt[i] += cnt[i - 1];		
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
		g = tg; // 다음 i + t 적용을 위해 현재 i + t로 g를 업데이트 한다. (예:t=1 정렬된 상태에서 t=2 정렬한다)
		if (g[SA[n - 1]] == n) break; // t<n이라도 정렬이 다 되었으면 빠져나온다
	} // for
}

void getLCP(const string& str) // SA[]가 필요하다.
{
	vector<int> RANK;
	int n = (int)str.size();
	int len = 0; // LCP length
	LCP.resize(n, 0);
	RANK.resize(n, 0);

	for (int i = 0; i < n; i++)
		RANK[SA[i]] = i; // SA값을 알파벳 순서로 바꿔준다.
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

	for (int x : SA) cout << x + 1 << " "; // string index가 0부터 시작하기 때문에 1부터 시작하려면 +1해준다.
	cout << "\n";
	
	cout << "x" << " ";
	for (int i = 1; i < s.length(); i++) cout << LCP[i] << " ";		
	cout << "\n";
}