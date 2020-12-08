// 13975.cpp
// 파일 합치기 3
// priority queue를 사용해서 풀 수 있다.
// priority queue로 오름차순 정렬로 모든 원소를 집어 넣는다.
// 맨 앞의 2개를 꺼내어 이 둘의 합을 누적하여 따로 저장하고 합쳐진 2개를 다시 큐에 넣는다.
// 마지막에 큐에 한개가 남았을 때 누적된 합이 바로 정답이 된다.
// 제한시간 2초 중 808ms(18,524KB)가 소요되었다.
// 맞은사람 85/145로 상위 58.62%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min, copy, rotate, swap
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

typedef long long ll;

void DoTest()
{
	int N, fs;
	priority_queue<ll, vector<ll>, greater<ll>> mypq;
	ll answer = 0;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> fs;
		mypq.push(fs);
	}

	ll f1, f2;
	while (mypq.size() > 1) {
		f1 = mypq.top(); mypq.pop();
		f2 = mypq.top(); mypq.pop();
		f1 += f2;
		answer += f1;
		mypq.push(f1);		
	}
	cout << answer << "\n";
}

int main()
{
	FAST;

	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
		DoTest();
}