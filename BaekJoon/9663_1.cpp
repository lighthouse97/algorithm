// 9663_1.cpp
// N-Queen
// 좀 자료를 찾아보니 backtracking방식을 사용하는 것은 맞는데,
// 앞의 IsPromising() 함수를 좀 더 빠르고 효율적으로 만들 수 있는 방법이
// 있었다. for loop로 상위 level의 점들을 하나한 찾으며 일일이 수직, 대각선을 계산하는 것보다
// 각 level에 점이 하나 찍힐 때마다 |(수직선), /(대각선1), \(대각선2)에 해당하는 점들을
// 한꺼번에 marking해서 다음 level에 점 찍을 때에는 여기 찍힌 위치만 피해서 marking해 나가면 된다.
// 수평선은 어치피 각 level에 하나의 점만 찍기 때문에 수평선에 대한 check는 더 필요가 없다.
// 수직선, 대각선1, 대각선2 각각에 해당하는 3개의 비열이 필요하며,
// |(수직선)에 해당하는 배열은 각 column을 index로 true,false로 marking 하면 되고,
// /(대각선1)에 해당하는 배열은 row를 i, column을 j라 했을 때, i + j를 index로 true/false를 marking한다.
// \(대각선2)에 해당하는 배열은 row를 i, column을 j라 했을 때, i - j + N + 1 를 index로 true/false를 marking한다.
// \(대각선2)의 원리는 몇 개 sample로 뽑아서 맞춰보면 그렇게 나온다.
// 이렇게 점 하나 찍을 때마다 갈 수 없는 곳들을 미리 한번에 표시해 두면 앞의 방법보다 훨씬 더 빨리 가능한 점을 찾을 수 있다.
// 그리고 backtracking으로 점 하나 지우면서 level이 올라 갈 때에는 지우는 점의 표시한 것을 다시 지워주어야 한다.
// https://rebas.kr/761 참조하였다.
// 확실히 시간이 줄어들었다.
// 4,096ms(2,016KB) -> 2,112ms(2,016KB)
// 제한시간 10초 중 2,112ms(2,016KB)가 소요되었다.
// 맞은사람 2788/10706로 상위 26.04%에 rank되었다.

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

int N = 0;
int cnt = 0;
vector<bool> A; // 수직선(|)
vector<bool> B; // 대각선1(/)
vector<bool> C; // 대각선2(\)

void BackTracking(int level)
{
	if (level > N) {
		cnt++;
		return;
	}
	else {
		for (int i = 1; i < N + 1; i++) {
			if (A[i] || B[level + i] || C[level - i + N + 1]) continue; // |, /, \ 체크
			else {
				A[i] = B[level + i] = C[level - i + N + 1] = true; // |, /, \ 표시
				BackTracking(level + 1);
				A[i] = B[level + i] = C[level - i + N + 1] = false; // |, /, \ 해제
			}			
		}
	}
}

int main() {

	FAST;

	cin >> N;
	A.resize(N + 1, false);
	B.resize(N + N + 1, false);
	C.resize(N + N + 1, false);
	BackTracking(1);
	cout << cnt << "\n";
}