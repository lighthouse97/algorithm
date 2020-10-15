// 11046.cpp
// 팰린드롬?
// DP로도 풀 수 있고, manacher로도 풀 수 있는데
// 일단 DP로 풀어보도록  하자.
// 방법은 16163에서 했던 것을 응용한다.
// 한개짜리 DP[][]는 true
// 두개짜리 DP[L][R]는 S[L] == S[R] 일 때 true
// 3개 이상일 경우 DP[L][R]은 S[L] == S[R]이고 DP[L+1][R-1] == true 이면 true
// 이렇게 모든 범위에 대해서 결과를 저장해 둔다.
// 아니다! DP로 하게되면 입력수의 최대 갯수가 100,000이라 메모리 초과가 발생한다!
// manacher algorithm으로 풀어야 하는게 맞다!
// 원리는 주어진 문자열 전체에 대해 manacher 알고리즘에 의한 A[i]를 구한다음 문제의 부분 문자열에서 '#'(or -1)을 포함한 문자열 기준으로
// 가운데 위치를 찾아서 해당 index의 A[i]값이 문제의 부분 문자열 count값보다 같거나 크면 palindrome문자열이 된다.
// 제한시간 1초 중 452ms(21,524KB)가 소요되었다.
// 여기서 약간 최적화하여 412ms(17616KB)가 소요되었다.
// 맞은사람 19/121로 상위 15.70%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<int> A;

void manacher(const vector<int>& nums)
{
	int n = (int)nums.size();
	int range = 0, center = 0;
	for (int i = 0; i < n; i++) {
		if (i > range) A[i] = 0;
		else A[i] = min(A[2 * center - i], range - i); // center - (i - center)

		while (i - A[i] - 1 >= 0 && i + A[i] + 1 < n
			&& nums[i - A[i] - 1] == nums[i + A[i] + 1])
			A[i]++;

		if (range < i + A[i]) { // range update
			range = i + A[i];
			center = i;
		}
	}
}

bool is_palindrome(int left, int right)
{
	int cnt = right - left + 1;
	int index;
	// index = (left + right) / 2;
	// if (cnt % 2) // odd count		
	//	 index = (index - 1) * 2 + 1;
	// else  // even count
	//	 index = (index - 1) * 2 + 1 + 1;
	// 56~60L 은 (left + right) - 1 로 간소화할 수 있다.
	index = left + right - 1;

	return (A[index] >= cnt);
}

int main()
{
	FAST;

	int N, M, nums;
	vector<int> p_nums;
	cin >> N;	
	p_nums.resize(2 * N + 1, 0);
	A.resize(2 * N + 1, 0);

	for (int i = 0; i < N; i++) {
		cin >> nums;
		p_nums[i * 2] = -1;
		p_nums[i * 2 + 1] = nums;
	}
	p_nums[2 * N] = -1;

	manacher(p_nums);
	cin >> M;
	int l, r;
	for (int i = 0; i < M; i++) {
		cin >> l >> r;
		bool result = is_palindrome(l, r);
		cout << (result ? 1 : 0) << "\n";
	}
}