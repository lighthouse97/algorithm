// 15652_1.cpp
// N과 M (4)
// 앞의 15651을 단지 등수를 올리고 싶어서 좀 더 최적화 시켰다.
// 전체적으로 동일하고 단지 answer 출력부분에서 배열과 for문을 사용하지 않고
// string을 이용하여 한번에 출력하여 출력시의 속도를 좀 더 빠르게 하였다.
// 실행 속도가 4ms(2,016KB) -> 0ms(2,016KB) 으로 줄어들었다.
// 맞은사람 95/7761로 상위 1.22%에 rank되었다. (51.68% -> 1.22%)

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
//#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX, LLONG_MIN
#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int N = 0, M = 0;
string answer = "";

void BackTracking(const int& level, const int& pre)
{
	if (level > M) {
		cout << answer << "\n";
		return;
	}
	else {
		for (int i = pre; i < N + 1; i++) {
			answer.push_back(i + '0');
			answer.push_back(' ');
			BackTracking(level + 1, i);
			answer.pop_back();
			answer.pop_back();
		}
	}
}

int main() {

	FAST;

	cin >> N >> M;
	BackTracking(1, 1);
}