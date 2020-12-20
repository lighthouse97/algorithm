// 14888.cpp
// 연산자 끼워넣기
// 삼성 SW 역량 테스트 기출 문제 1
// 이 문제도 BackTracking으로 풀 수 있는 문제이다.
// 문제에서 주어지는 N - 1개의 연산자에 각각 번호를 붙여서
// 1 ~ N-1 까지를 앞에서 N과 M 문제처럼 풀면 된다.
// N - 1 level까지 진행했을 때의 최종 계산 결과에 대해 min, max값을 계속 비교하면서
// 모든 조합을 BackTracking으로 다 비교 해보면 된다. 모든 조합에 대해 min, max값을 찾으면 된다.
// 연산자 구분은 1은 +, 2는 -, 3은 *, 4는 / 이런 씩으로 붙이면 된다.
// 다음 level로 넘어기기전에 현 level에서의 누적 계산 결과를 argument로 넘겨준다.
// 주어진 입력은 사칙연산 단위이고 이를 N - 1개의 연산자 집합으로 초기에 만들어 준다.
// 'a + b' 연산을 한다면 a가 이전 level에서 넘어온 sum이 되고 b는 NUMS[level + 1]이 된다.
// 따지고 보면 그렇다.
// 모든 연산이 한 번씩만 쓰여져야 하기 때문에 열 단위의 COL[] 배열을 두어 현재 사용되는 연산은
// 다음 level에서 중복 사용하지 못하도록 체크해 준다.
// 제한시간 2초 중 216ms(2,020KB)가 소요되었다.
// 맞은사람 8866/10649로 상위 83.25%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int N;
int minval = 1000000999, maxval = -1000000999;
vector<int> NUMS;
vector<int> OPR; // 1(+), 2(-), 3(*), 4(/)
vector<bool> COL;

int calc(const int& a, const int& b, const int& opr)
{
	int val;
	if (opr == 1) val = a + b;
	else if (opr == 2) val = a - b;
	else if (opr == 3) val = a * b;
	else val = a / b;
	return val;
}

void BackTracking(const int& level, const int& sum)
{
	if (level > N - 1) {
		minval = min(minval, sum);
		maxval = max(maxval, sum);
		return;
	}

	int isum;
	for (int i = 1; i < N; i++) {
		if (COL[i]) continue;
		COL[i] = true;
		isum = calc(sum, NUMS[level + 1], OPR[i]);
		BackTracking(level + 1, isum);
		COL[i] = false;
	}
}

int main()
{
	FAST;

	cin >> N;
	NUMS.resize(N + 1, 0);
	OPR.resize(N, 0);
	COL.resize(N, false);
	int op, cnt = 0;
	for (int i = 1; i < N + 1; i++) cin >> NUMS[i];
	for (int i = 1; i <= 4; i++) {
		cin >> op;
		while (op--)
			OPR[++cnt] = i;		
	}
	BackTracking(1, NUMS[1]);
	cout << maxval << "\n";
	cout << minval << "\n";
}