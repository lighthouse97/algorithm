// 3273_1.cpp
// 두 수의 합
// 투 포인터를 사용하지 않고 더 빨리 풀 수 있는 방법을 쓸쩍 보고 알게되어 풀어보았다.
// 예를 들어 X가 13이고 현재의 수가 2이면 조건을 만족하려면 언젠가는 11이 꼭 나와야 한다.
// 따라서 현재의 수가 ai이면 CHRCK[X - ai] = 1로 잡아놓고, 끝까지 수를 탐색하다가 aj가 X - ai이면.
// CHECK[aj]가 1이고 아니면 0이므로 CHECK[aj]가 1이 될 때, count를 1씩 증가시키면 된다.
// 12ms(2,408KB) -> 8ms(2,464KB)
// 제한시간 1초 중 8ms(2,464KB)가 소요되었다.
// 맞은사람 3/864로 상위 0.34%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
//#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
	FAST;

	int N, X;
	vector<int> num;
	vector<bool> check;
	cin >> N;
	num.resize(N, 0);
	for (int i = 0; i < N; i++) cin >> num[i];
	cin >> X;
	check.resize(X, false);

	int result = 0;
	for (int i = 0; i < N; i++) {
		if (X > num[i]) {
			if (check[num[i]]) result++;
			check[X - num[i]] = true;			
		}
	}
	cout << result << "\n";
}