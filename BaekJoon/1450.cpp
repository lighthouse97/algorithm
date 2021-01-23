// 1450.cpp
// 냅색 문제
// meet in the middle 방법을 사용한다.
// 앞에서(1208)에서 풀었던 것과 거의 같은데, 부분합이 특정 값이 아니고 특정 값이하의 범위이다.
// 이 경우는 map을 사용하지 않고 정렬된 vector와 upper_bound를 이용해서 범위내의 갯수를 구한다.
// 나머지는 앞에서와 같다.
// 그리고 각 원소의 수의 최대값이 10^9이라 부분합의 범위가 int를 넘을 수 있어 부분합의 자료형을 long long으로
// 해야 한다! 이거 때문에 한번 틀렸었다!
// 제한시간 1초 중 4ms(2,540KB)가 소요되었다.
// 맞은사람 124/288로 상위 43.05%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
#include <algorithm> // sort, max, min, copy, swap, unique
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

typedef long long ll;

int N, C;
vector<int> NUM;
int MID; // 가운데 지점
vector<ll> SUM_A;
vector<ll> SUM_B;
ll CNT = 0;

void dfs_a(const int& index, const ll& sum)
{
	if (index > MID) return;
	ll c_sum = sum; // current sum
	c_sum += NUM[index];
	if (c_sum <= C) {
		CNT++;
		SUM_A.push_back(c_sum);
	}

	dfs_a(index + 1, c_sum);
	dfs_a(index + 1, c_sum - NUM[index]);
}

void dfs_b(const int& index, const ll& sum)
{
	if (index > N) return;
	ll c_sum = sum; // current sum	
	c_sum += NUM[index];
	if (c_sum <= C) {
		CNT++;
		SUM_B.push_back(c_sum);
	}

	dfs_b(index + 1, c_sum);
	dfs_b(index + 1, c_sum - NUM[index]);
}

int main()
{
	FAST;

	cin >> N >> C;
	NUM.resize(N + 1, 0);
	for (int i = 1; i < N + 1; i++) cin >> NUM[i];
	int size = 1 << (N / 2);
	SUM_A.reserve(size);
	SUM_B.reserve(size);

	MID = (1 + N) / 2;
	dfs_a(1, 0);	
	dfs_b(MID + 1, 0);	
	
	sort(SUM_A.begin(), SUM_A.end());
	sort(SUM_B.begin(), SUM_B.end());
	int count;
	for (int i = 0; i < SUM_A.size(); i++) {
		count = upper_bound(SUM_B.begin(), SUM_B.end(), C - SUM_A[i]) - SUM_B.begin();
		if (count == 0) break;
		CNT += count;
	}	
	cout << CNT + 1 << "\n"; // 아무것도 넣지 않는 경우 포함
}