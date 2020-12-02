// 13261.cpp
// 탈옥(prison break)
// 이것도 divide & conquer optimization 문제인데, 확실이 DP문제는 어렵다.
// 실마리를 도저히 잡지 못해서 결국 힌트를 보고 풀게 되었다.
// PS가 매우 약한데, 게다가 구현도 실력이 안따라주니 매우 답답하기 그지 없다!
// 일단 점화식은 다음과 같다.
// DP[level][i]가 간수 level명까지 i번째 방을 감시할 때의 i번째 방까지의 탈옥 위험도라한다면,
// DP[level][i] = min(k < i){ DP[level-1][k] + cost(k+1, i) }
// cost(k, i)는 level 번째 간수가 k+1부터 i까지 방을 감시할 때의 탈옥위험도이다. 따라서,
// cost(k, i) = (SUM[i] - SUM[k])*(i - k)
// SUM[i]는 i번째 방까지의 탈옥력 C[i]의 누적합이다.
// i는 1 ~ N 범위에서부터 시작해서 D&Q로 접근하면 되고 level은 1부터 L까지 loop를 돌린다.
// cost() 함수가 c(a, c) + c(b, d) <= c(a, d) + c(b, c) 사각부등식을 min값 조건으로 만족하므로 D&Q Optimization을 사용할 수 있다. 
// 추가 주의할 점
// 1) 방의 수 : N, 간수 수 : L 일 때, 만일 N <= L 이면(간수가 더 많으면) 볼 것없이 SUM[N]이 정답이다.
// 2) level마다 D & Q에서 최초 시작 범위의 마지막 값은 level 값과 관계 있는데 마지막 값이 N-(L-level)로 잡는다.
//    why? 6개의 방, 3명의 간수라면 1번째 간수 계산할때 2, 3번째 간수 몫은 남겨야 하므로 6-(3-1) = 4
//    2번째 간수 계산할 때 마찬가지로 6-(3-2) = 5, 마지막 3번째 간수 계산할 때 6-(3-3) = 6 이 된다.

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
const ll MAXVAL = 99*1e15;

int L, G;
vector<ll> SUM;
vector <vector<ll>> DP;
ll answer = MAXVAL;

void prison_risk(int level, int start, int end, int left, int right)
{

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

	if (L <= G) { // 방보다 간수가 더 많을 경우
		cout << SUM[L] << "\n";
		return 0;
	}
	for (int level = 1; level < G + 1; level++) {
		int end = L - (G - level);
		prison_risk(level, 1, end, )
	}

}