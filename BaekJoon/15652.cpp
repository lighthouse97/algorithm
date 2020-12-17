// 15652.cpp
// N과 M (4)
// 선택된 수열이 오름차순인데 같은 수도 포함이 되므로,
// 15650.cpp 에서 (i <= pre) 조건만 (i < pre) 조건으로
// 바꿔주면 된다.
// 아니면 pre부터 시작하도록 하면 된다.(실제로 이렇게 구현하였다.)
// 제한시간 1초 중 4ms(2,016KB)가 소요되었다.
// 맞은사람 4011/7760로 상위 51.68%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min, copy
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

int N = 0, M = 0;
vector<int> answer;

void BackTracking(const int& level, const int& pre)
{
	if (level > M) {
		for (int i = 1; i < level; i++) cout << answer[i] << " ";
		cout << "\n";
		return;
	}
	else {
		for (int i = pre; i < N + 1; i++) {
			answer[level] = i;
			BackTracking(level + 1, i);
		}		
	}
}

int main() {

	FAST;

	cin >> N >> M;
	answer.resize(M + 1, 0);
	BackTracking(1, 1);
}