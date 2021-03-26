// 13549_1.cpp
// 숨바꼭질3
// priority_queue를 사용하지 않고, deque를 사용하여 풀어보았다.
// 출발지점부터 deque에 넣고, 하나씩 꺼내면서 *2는 deque 맨 앞에, -1이나 +1은 deque 맨뒤에 차례로 넣는다.
// 움직인 위치가 0보다 작거나 100000보다 큰 위치는 곰곰히 따져보면 고려할 필요가 없다.
// *2들만 먼저 check, (첫번째 *2의 -1)의 *2 체크, (첫번째 *2의 +1)의 *2 체크, (두번째 *2의 -1)의 *2 체크, (두번째 *2의 +1)의 *2 체크, ...
// (첫번째 *2의 -2)의 *2 체크, (첫번째 *2의 +2)의 *2 체크, ... 
// 즉 time이 작은 값부터 위치가 작은 순서부터 차례로 체크해 나간다
// 20ms->0ms, 3,692KB->2416KB 로 수행시간 및 메모리 소요량이 줄어들었다.
// (이유는 우선순위큐는 삽입할 때마다 정렬하는데 이때 O(logN)의 시간복잡도이지만 deque의 경우는 정렬을 하지 않기 때문에 O(1)의 시간복잡도로 훨씬 빠르다)
// 제한시간 1초 중 0ms(2,416KB)가 소요되었다.
// 맞은사람 793/4034로 상위 19.65%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
//#include <vector>
#include <algorithm> // sort, max, min, copy, swap, unique, fill_n
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct go {
	int m, t;
	go() : m(0), t(0) {}
	go(int m, int t) : m(m), t(t) {}
};

int main() {
	FAST;
	int N, K;
	int exist[100001];
	cin >> N >> K;
	fill_n(exist, 100001, 0);

	deque<go> mydq;
	mydq.push_back({ N, 0 });
	exist[N] = 1;
	if (N == K) { // 당연1
		cout << 0 << "\n";
		return 0;
	}
	else if (N > K) { // 당연2 (-1외에는 갈 수 있는 방법이 없다!)
		cout << (N - K) << "\n";
		return 0;
	}
	int result;
	int loc; go cur;
	while (!mydq.empty()) {
		cur = mydq.front();
		mydq.pop_front(); // 앞에서부터 뺀다.
		if (cur.m == K) { result = cur.t; break; }
		loc = cur.m * 2;
		if (loc <= 100000 && !exist[loc]) {
			mydq.push_front({ loc, cur.t + 0 }); // *2가 우선순위가 높다
			exist[loc] = 1;
		}
		loc = cur.m - 1;
		if (loc >= 0 && !exist[loc]) {
			mydq.push_back({ loc, cur.t + 1 }); // 다음은 -1, +1 위치
			exist[loc] = 1;
		}
		loc = cur.m + 1;
		if (loc <= 100000 && !exist[loc]) {
			mydq.push_back({ loc, cur.t + 1 });
			exist[loc] = 1;
		}
	}
	cout << result << "\n";
}