// 14888_1.cpp
//연산자 끼워넣기
// 앞에 14888에서 푼 것도 맞지만 수행시간이 216ms로 0ms가 대부분인 상위권에 비해
// 등수가 너무 낮았다.
// 크게 의미는 없고 단지 등수를 올리기 위해 살짝 '컨닝'을 했더니 BackTracking 파라미터로
// +, -, *, / 연산자 갯수 모두를 그대로 넘겨서 각 연산자마다 recursive 호출이 따로 다 있었다.
// 다음 level로 넘길 때마다 사용된 연산자 갯수는 1씩 감소하므로 특정 level에서 0이 되면 해당 연산자는
// 더 이상 사용하지 않게 될 것이다.
// 이렇게 풀면 for문 호출이 대폭 줄어들어 수행시간이 많이 줄어 들 것으로 예상된다.
// 이렇게 함 풀어보자!
// 놀랍게도 이렇게 푸니(연산 횟수는 같지만 깊이가 줄어서 마치 병렬 연산의 효과가 나는 것 같다.)
// 수행시간이 216ms -> 0ms로 줄어들었다.
// 제한시간 2초 중 0ms(2,016KB)가 소요되었다.
// 맞은사람 5472/10649로 상위 51.38%에 rank되었다.


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

void BackTracking(const int& level, const int& sum, const int& plus, const int& minus, const int& mul, const int& div)
{
	if (level > N - 1) {
		minval = min(minval, sum);
		maxval = max(maxval, sum);
		return;
	}

	if (plus) // 현 level에서 plus 먼저
		BackTracking(level + 1, sum + NUMS[level + 1], plus - 1, minus, mul, div);
	if (minus) // 현 level에서 minus 먼저
		BackTracking(level + 1, sum - NUMS[level + 1], plus, minus - 1, mul, div);
	if (mul) // 현 level에서 multiply 먼저
		BackTracking(level + 1, sum * NUMS[level + 1], plus, minus, mul - 1, div);
	if (div) // 현 level에서 divide 먼저
		BackTracking(level + 1, sum / NUMS[level + 1], plus, minus, mul, div - 1);
}

int main()
{
	FAST;

	int plus, minus, mul, div;
	cin >> N;
	NUMS.resize(N + 1, 0);
	for (int i = 1; i < N + 1; i++) cin >> NUMS[i];
	cin >> plus >> minus >> mul >> div;
	BackTracking(1, NUMS[1], plus, minus, mul, div);

	cout << maxval << "\n";
	cout << minval << "\n";
}