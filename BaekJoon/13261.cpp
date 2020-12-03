// 13261.cpp
// 탈옥(prison break)
// 이것도 divide & conquer optimization 문제인데, 확실이 DP문제는 어렵다.
// 실마리를 도저히 잡지 못해서 결국 힌트를 보고 풀게 되었다.
// PS가 매우 약한데, 게다가 구현도 실력이 안따라주니 매우 답답하기 그지 없다!
// 일단 점화식은 다음과 같다.
// DP[level][i]가 간수 level명까지 i번째 방을 감시할 때의 i번째 방까지의 탈옥 위험도라한다면,
// DP[level][i] = min(k < i){ DP[level-1][k] + cost(k+1, i) }
// cost(k, i)는 level 번째 간수가 k부터 i까지 방을 감시할 때의 탈옥위험도이다. 따라서,
// cost(k, i) = (SUM[i] - SUM[k-1])*(i - k + 1)
// SUM[i]는 i번째 방까지의 탈옥력 C[i]의 누적합이다.
// cost() 함수가 c(a, c) + c(b, d) <= c(a, d) + c(b, c) 사각부등식을 min값 조건으로 만족하므로 D&Q Optimization을 사용할 수 있다.
// D&Q로 접근할 때, i는 1 ~ L에서 시작, k는 0 ~ L로 시작. 이후는 D&Q rule에 따른다. (--> 잘 따져보면 그렇다!)
// level(간수)는 2부터 시작한다. level 1에서는 c(1, i)로 초가화 하면 된다.
// 만일 방의 수보다 간수가 같거나 더 많이 주어지면 간수 1명당 방 하나씩 감시하면 되므로 이 때는 계산할 것도 없이 SUM[L]이 답이 된다.
// 이외의 세부 건들을 소스 지저분해지고 실수의 소지가 많으므로 약간의 시간을 희생해도 그대로 진행한다!!!
// 실수한 점!
// prison_risk() 함수에서 for문 돌릴 때 k < hi라고 했는데, 실제로 hi가 mid일 때는 이게 맞지만 mid 가 아닐 때에는
// right값 값까지 k가 포함되어야 하는데 이 둘을 구분하지 않고 k < hi로 하여서 틀렸다(WA).
// 따로 구분 처리하면 소스가 지저분해지므로 이 둘을 다 포함하는 k <= hi로 처리하여 통과(AC)되었다.
// 제한시간 2초 중 208ms(45,444KB)가 소요되었다.
// 맞은사람 70/139로 상위 50.35%에 rank되었다.

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
const ll MAXVAL = 99e15;

int L, G;
vector<ll> SUM;
vector <vector<ll>> DP;

inline ll cost(int k, int i)
{
	return (SUM[i] - SUM[k - 1])*(i - k + 1);
}

void prison_risk(int level, int start, int end, int left, int right)
{
	ll risk = 0;
	ll minv = MAXVAL;
	int optk = 0;
	if (start > end) return;
	int mid = (start + end) >> 1;
	int lo = left;
	int hi = min(mid, right);
	for (int k = lo; k <= hi; k++) {
		risk = DP[level - 1][k] + cost(k + 1, mid);
		if (risk < minv) {
			minv = risk;
			optk = k;
		}
	}
	DP[level][mid] = minv;
	prison_risk(level, start, mid - 1, left, optk);
	prison_risk(level, mid + 1, end, optk, right);
}

int main()
{
	FAST;

	int ci;
	cin >> L >> G;
	SUM.resize(L + 1, 0);
	DP.resize(G + 1, vector<ll>(L + 1, 0));
	for (int i = 1; i < L + 1; i++) {
		cin >> ci;
		SUM[i] = SUM[i - 1] + ci;
	}

	if (L <= G) { // 방보다 간수가 같거나 더 많을 경우
		cout << SUM[L] << "\n";
		return 0;
	}

	for (int i = 1; i < L + 1; i++) { // level(간수)이 1일 때에는 cost(1, i)를 미리 적용한다.
		DP[1][i] = cost(1, i);
	}
	for (int level = 2; level < G + 1; level++) { // level 2부터 D&Q Optimization을 적용한다.
		prison_risk(level, 1, L, 0, L);
	}
	cout << DP[G][L] << "\n";
}