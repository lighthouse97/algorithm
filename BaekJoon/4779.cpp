// 4779.cpp
// 칸토어 집합
// ICPC > Regionals > North America > Mid-Atlantic Regional > 2002 Mid-Atlantic Regional Programming Contest G번
// 분할 정복으로 쪼개 나가면 쉽게 풀 수 있는 문제이다.
// 제한시간 1초 중 32ms(2,536KB)가 소요되었다.
// 맞은사람 103/209로 상위 49.28%에 rank되었다.
// 좀 더 최적화시켜서,
// 제한시간 1초 중 32ms(2,016KB)가 소요되었다.
// 맞은사람 102/209로 상위 48.80%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
//#include <vector>
//#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int powerk(int n, int k)
{
	if (k == 0) return 1;
	int num = powerk(n, k / 2);
	if (k % 2) return num * num * n;
	else return num * num;
}

void func(int n)
{
	if (n == 0) {
		cout << '-';
		return;
	}
	int unit;
	unit = powerk(3, n - 1);
	func(n - 1);
	for (int i = 1; i < unit + 1; i++) cout << ' '; // 가운데 공백 처리
	func(n - 1);
}

int main()
{
	FAST;
	int N;
	while (cin >> N) {
		func(N);
		cout << "\n";
	}
}