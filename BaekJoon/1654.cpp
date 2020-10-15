// 1654.cpp
// 랜선 자르기
// 입력된 랜선의 가장 작은 길이을 기준으로 [1, len] 배열을 만들고,
// 목표갯수를 만족하는 upper bound값을 이분 탐색으로 구한다.
// 기존 upper_bound 알고리즘을 그대로 사용하면 틀린다.
// 반례가 있다. 4 4 -> 10 10 10 10 (정답은 10인데 기존 upper_bound 사용하면 9가 나온다)

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt

using namespace std;

vector<long long> arr;
long long MAX_VAL = 0;

int wire_count(long long len)
{
	int sum = 0;
	for (auto x : arr)
		if(x >= len) sum += (int)(x / len);
	return sum;
}

long long find_max(const int& val)
{
	long long start = 1;
	long long end = MAX_VAL;
	long long mid, ans=0;
	int cnt;

	while (start <= end) {
		mid = (start + end) >> 1;
		cnt = wire_count(mid);
		if (cnt >= val) {
			if (ans < mid) ans = mid;
			start = mid + 1;
		}
		else end = mid - 1;
	}
	return ans;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int K, N;
	long long result;
	cin >> K >> N;
	arr = vector<long long>(K);
	for (int i = 0; i < K; i++) {
		cin >> arr[i];
		if (MAX_VAL < arr[i]) MAX_VAL = arr[i];
	}
	result = find_max(N);
	cout << result << "\n";
}