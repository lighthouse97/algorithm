// 16229.cpp
// 반복 패턴
// Z 알고리즘 응용문제이다.
// Contest > 웰노운컵 > 제2회 웰노운컵 Day 2 F번
// 일단 시행착오로 함 풀어보고 정리하자
// 문자열 응용이 안되어 풀이를 보고 한참(하루종일) 생각하고서야 알게 되었다.
// 1) 주어진 string에 대해 Z[]값을 구한다.
// 2) 1 <= i < N에 대해서 Z[i] > 0 일 때 i에서 문자열 끝까지 prefix 일치해야 하므로(그래야 패턴반복 할 수 있다)
//    i + Z[i] == N (or i + Z[i] >= N) 이어야 한다. (이거 빼먹어서 한참 헤맸다!!)
// 3) N에서 Z[i]만큼 뺀 것을 P라 하면 P가 반복되는 패턴의 글자수가 된다.
// 4) (N + K) / P 가 패턴이 K까지 합한 문자열에서 몇번 반복이 되는지 반복횟수 C가 된다.
// 5) C >=2(최소 2번이상 반복해야 하므로...)이고 P * C >= N(패턴이 C번 반복될 때 P*C가 N 길이는 넘어야 텍스트 전체가 반복된다)
//    일 때 answer = max(answer. P)가 된다. 조건을 만족하는 P중 가장 큰 값.
// 3)에서 prefix 압,뒤가 떨어져 있으면 N-Z[i]가 패턴임은 자명하다.
//        prefix 압,뒤 중 일부가 겹치면 N-Z[i]의 패턴이 앞뒤 prefix내부에서 공통으로 나타난다.
//        abababa를 예로 들면 ab가 앞뒤 prefix ababa에 공통으로 나타남을 알 수 있다.
//   0123456
//   abababa
//     abababa
//   겹치는 부분(2~6)은 겹치므로 같고 패턴 ab가 뒤 prefix 시작 ab와 같으므로 결국 ab는 패턴이 된다.(아주 한참 생각해서 알았다)
// 따라서 N - Z[i]가 반복되는 패턴의 길이가 된다.
// 제한시간 1초 중 0ms(2,748KB)가 소요되었다.
// 맞은사람 16/39로 상위 41.02%에 rank되었다.

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

vector<int> Z;

void z_algorithm(const string& str)
{
	int R = 0, L = 0;
	int n = (int)str.length();
	for (int i = 1; i < n; i++) {
		if (i > R) {
			L = R = i;
			while (R < n && str[R - L] == str[R]) R++;
			Z[i] = R - L; R--;
		}
		else { // L < i <= R
			int k = i - L; // i'
			if (i + Z[k] - 1 < R) Z[i] = Z[k];
			else {
				L = i;
				while (R < n && str[R - L] == str[R]) R++;
				Z[i] = R - L; R--;
			}
		}
	}
	Z[0] = n;
}

int main()
{
	FAST;
	
	int N, K, answer = 0;
	string str;

	cin >> N >> K;
	cin >> str;
	if (K >= N) {
		cout << N << "\n";
		return 0;
	}
	Z.resize(N, 0);
	z_algorithm(str);	
	int p, c;
	for (int i = 1; i < N; i++) {
		if (Z[i] > 0 && i + Z[i] == N) {
			p = N - Z[i]; // pattern의 길이
			c = (N + K) / p; // pattern의 반복 횟수
			if (c >= 2 && p * c >= N) answer = max(answer, p);
		}
	}
	cout << answer << "\n";
}