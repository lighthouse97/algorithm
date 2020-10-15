// 9248.cpp
// Suffix Array
// Suffix Array를 구하는 맨버-마이어스 알고리즘(Manber-Myers Algorithm)과
// SA를 이용하여 LCP(Longest Common Prefix)를 구하는 알고리즘을
// 이용한다.
// 이 두가지를 직접적으로 이용하는 문제라 따로 응용은 없고 이 두가지만
// 알고 있으면 된다.
// 제한시간 3초 중 880ms(10,444KB)가 소요되었다.
// 맞은사람 457/545로 상위 83.85%에 rank되었다.
// 좀 더 최적화 시키면 524ms(8,492KB) 소요된다.
// SA구하는 함수에서 t < n 이라도 SA 정렬이 완료되면(g[SA[n - 1]] == n - 1), 루프를 빠져나오록 하였다.

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
vector<int> LCP;

void getSA(const string& str) // Manber-Myers algorithm
{
	vector<int> g; // SA group(SA 순서)
	vector<int> tg; // temporary group
	int n = (int)str.length();
	int t = 1; // 문자열에서 문자의 위치
	SA.resize(n, 0);
	g.resize(n + 1, -1); // 끝의 짧은 문자부터 이미 순서가 결정나기 때문에 n+1만 잡고 g[n] = -1 해 주면 된다. n+1 넘어가서 비교하는 경우는 없다고 봐야 한다
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
		sort(SA.begin(), SA.end(), cmp); // 특정 t에서 SA 업데이트
		tg[SA[0]] = 0;
		for (int i = 1; i < n; i++) {
			if (cmp(SA[i - 1], SA[i])) tg[SA[i]] = tg[SA[i - 1]] + 1; // 특정 t에서 tg(g) 업데이트
			else tg[SA[i]] = tg[SA[i - 1]];
		}		
		g = tg; // tg를 g에 update
		
		if (g[SA[n - 1]] == n - 1) break; // t<n이라도 정렬이 다 되었으면 빠져나온다
		t <<= 1; // t*2 적용		
	}	
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

	for (int x : SA)
		cout << x + 1 << " "; // string index가 0부터 시작하기 때문에 1부터 시작하려면 +1해준다.
	cout << "\n";
	cout << "x ";
	for (int i = 1; i < s.length(); i++)
		cout << LCP[i] << " ";		
	cout << "\n";
}