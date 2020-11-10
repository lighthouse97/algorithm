// 11003.cpp
// 최솟값 찾기
// 분류가 동적 계획법 최적화 항목에 있어 동적계획볍으로 풀 수도 있으나
// 문제에서 말한 대로 deque를 사용해서도 풀 수 있다.
// 일단 deque를 사용해서 풀어보고 다음에 dynamic programming으로 풀어보자.
// deque로 풀경우 i 지점에서 최소값은 A(i-L+1), A(i-L)~A(i)에서 작은 값을 구하고
// i + 1지점에서 최소값은 A(i-L)~A(i)과 A(i+1)에서 작은 값을 구한다.
// 이렇게 함으로써 L개의 구간에서 최소값 구하는 연산을 절반으로 줄일 수 있다.
// 일단 deque로 풀면 시간초과가 나오고, priority_queue를 써서 겨우 풀었다.
// 제한시간 2.4초 중 1,764ms(119,90KB)가 소요되었다.
// 맞은사람 512/1600로 상위 32.00%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
#include <utility> // pair, swap
//#include <stack>
//#include <set>
#include <queue> // queue, priority_queue
//#include <deque>
#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

typedef pair<int, int> pii;

int main()
{
	FAST;
	
	int N, L;
	vector<int> answer;
	priority_queue<pii, vector<pii>, greater<pii>> mypq;

	cin >> N >> L;
	answer.resize(N + 1, 0);

	int a;
	for (int i = 1; i < N + 1; i++) {
		cin >> a;
		mypq.push({ a, i });
		if (i - L <= 0) answer[i] = mypq.top().first;
		else {
			while (mypq.top().second <= i - L) mypq.pop();
			answer[i] = mypq.top().first;
		}
	}

	for (int i = 1; i < N + 1; i++)
		cout << answer[i] << " ";
	cout << "\n";
}