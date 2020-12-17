// 15649.cpp
// N과 M (1)
// 이 문제는 무식하게 for문을 여러 개 써서 풀면 100% TLE 발생하기 때문에
// BackTracking을 이용해서 풀어야 한다.
// 문제자체도 BackTracking을 활용하는 기본 문제이다.
// 앞서 풀었던 N-Queen문제와 유사하게 풀면 된다.
// level 1에서 하나 선택하면 해당 column에 해당하는 |(수직선)에 marking하고
// 다음 level로 넘어간다. 다음 선택시 marking 된 것은 피한다.
// BackTracking을 빠져나오면 marking된 |(수직선)은 지운다.
// 다음 level로 넘어가면서 지정된 count(M)에 도달할 때 까지 현재 선택된 값을 출력한다.
// 제한시간 1초 중 20ms(2,016KB)가 소요되었다.
// 맞은사람 479/10198로 상위 4.69%에 rank되었다.

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
vector<bool> A; // 수직선(|)
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
			if (A[i]) continue; // | 체크
			else {
				A[i] = true; // | 표시				
				answer[level] = i;				
				BackTracking(level + 1);
				A[i] = false; // | 해제
			}
		}
	}
}

int main() {

	FAST;

	cin >> N >> M;
	A.resize(N + 1, false);
	answer.resize(M + 1, 0);
	BackTracking(1);
}