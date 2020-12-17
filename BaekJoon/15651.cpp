// 15651.cpp
// N과 M (3)
// 같은 숫자 중복을 허용하므로 15649 의 N과 M (1)에서 이미 선택된
// column인지를 비교하는 부분만 빼면 된다.
// 모든 경우를 다 해보는 거라 수행시간은 좀 더 걸릴 것으로 생각된다.
// 제한시간 1초 중 368ms(2,016KB)가 소요되었다.
// 맞은사람 789/8144로 상위 9.68%에 rank되었다.

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

void BackTracking(int level)
{
	if (level > M) {
		for (int i = 1; i < level; i++) cout << answer[i] << " ";
		cout << "\n";
		return;
	}
	else {
		for (int i = 1; i < N + 1; i++) {
			answer[level] = i;
			BackTracking(level + 1);
		}
	}
}

int main() {

	FAST;

	cin >> N >> M;
	answer.resize(M + 1, 0);
	BackTracking(1);
}