// 12015.cpp
// 가장 긴 증가하는 부분 수열 2
// 수열의 크기가 1,000,000이기 때문에 기존 DP 방법으로는 2중 for문에 의해
// 계산 시간이 많이 걸려 시간 초과가 발생한다.(O(N^2))
// 이 경우는 가장 긴 증가하는 부분 수열과 비슷한 유형이기는 하나 풀이는
// DP가 아닌 다른 방법을 이용해야 한다.
// 이분 탐색을 하는 std::lower_bound()를 이용하한다.(O(NlogN))
// 이분 탐색은 std::binary_search(), std::lower_bound(), std::upper_bound()가 있다.
// 이분 탐색은 이미 정렬된 수에 대해 탐색하는 방법으로 문제의 성격에도 잘 맞다.
// LIS(Longest Increasing Sequence)문제는 DP를 이용한 이중 for문을 이용하는 방법과
// lower_bound를 이용하는 방법이 있는데 이 경우는 lower_bound를 이용해야 한다.
// example : 10 20 30 40 1 2 3
// 10
// 10 20
// 10 20 30
// 10 20 30 40
// 1  20 30 40 => 1보다 같거나 크면서 가장 앞쪽의 index를 찾는다.
// 1  2  30 40
// 1  2  3  40 ==> vector의 size는 4이다.
// LIS의 크기는 구하지만 LIS에 해당하는 정확한 수열은 알 수 없다.
// 수열까지 알려면 다른 방법을 더 찾아야 한다.

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm> // lower_bound

using namespace std;

int AR[1000001] = { 0, };
vector<int> DP;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N;
	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> AR[i];
		if (i == 1) DP.push_back(AR[1]);
		else {
			if (DP.back() < AR[i]) DP.push_back(AR[i]);
			else 
				DP[lower_bound(DP.begin(), DP.end(), AR[i]) - DP.begin()] = AR[i];
		}
	}
	cout << DP.size() << "\n";
}