// 11001.cpp
// 김치
// 이 문제는 DP Optimization 방법 중 Divide & Conquer Optimization을 사용한다.
// D & C Optimization이 이해가 안되어 한참을 찾아보았다.
// 김치 담는 날을 p, 김치 꺼내는 날을 q, 꺼내는 날의 온도를 T[q], 담는 날의 가치를 V[p]라 하면
// C(p, q) = T[q](q-p) + V[p] 가 되고 C(p,q)를 최대화하는 q의 값을 opt(p)라 하면
// opt(p) <= opt(p+1) 일 때 D & Q Optimization을 사용할 수 있다.
// a <= b <= c < = d 일 때 C(a,c) + C(b,d) >= C(a,d) + C(b,c) 이므로(계산하면 나옴!)
// max값을 구하는 D & Q Optimization을 사용할 수 있다.
// mid를 담는 날, k를 꺼내는 날로 잡고 구현했는데, 반대로 잡아도 된다,
// vector를 사용하지 않고 일차원 배열로 잡고 구현하면 실행 속도가 더 빨리 나올 것이다.
// 제한시간 1초 중 124ms(2,800KB)가 소요되었다.
// 맞은사람 148/167로 상위 88.62%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

typedef long long ll;

int N = 0, D = 0;
vector<int> T; // 김치 꺼낼 때의 온도
vector<int> V; // 김치 담을 때의 가치
ll answer = 0;

void kimchi(int start, int end, int left, int right)
{
	ll cost;
	ll maxv = 0;
	int optk = 0;
	if (start > end) return;
	int mid = (start + end) >> 1;
	int lo = max(mid, left);
	int hi = min(mid + D, right);
	for (int k = lo; k <= hi; k++) {
		cost = 1LL * T[k] * (k - mid) + V[mid];
		if (cost > maxv) {
			maxv = cost;
			optk = k;
		}
	}
	answer = max(answer, maxv);
	kimchi(start, mid - 1, left, optk);
	kimchi(mid + 1, end, optk, right);
}

int main()
{
	cin >> N >> D;
	T.resize(N + 1, 0);
	V.resize(N + 1, 0);

	for (int i = 1; i < N + 1; i++) cin >> T[i];
	for (int i = 1; i < N + 1; i++) cin >> V[i];

	kimchi(1, N, 1, N);
	cout << answer << "\n";
}
