// 10816.cpp
// 수 찾기
// 숫자 카드 2
// 이분탐색의 응용. 숫자를 찾는 것 뿐만 아니라 찾은 숫자가 몇개인지를 알아야 한다.
// vector의 lower bound, upper bound를 이용하면 금방 풀 수 있으나
// 이분탐색을 이용하여 lower bound, upper bound를 직접 구현해 본다.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt

using namespace std;

vector<int> arr;
int SIZE;

int lower_bound(const int& val)
{
	int start = 0;
	int end = SIZE;
	int mid;

	while (start < end) {
		mid = (start + end) >> 1;
		if (arr[mid] >= val) end = mid;
		else start = mid + 1;
	}
	return end;
}

int upper_bound(const int& val)
{
	int start = 0;
	int end = SIZE;
	int mid;

	while (start < end) {
		mid = (start + end) >> 1;
		if (arr[mid] > val) end = mid;
		else start = mid + 1;
	}
	return end;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M, num, upper, lower;
	cin >> N;
	arr = vector<int>(N);
	for (int i = 0; i < N; i++)
		cin >> arr[i];
	sort(arr.begin(), arr.end());

	cin >> M;
	SIZE = N;
	for (int i = 0; i < M; i++) {
		cin >> num;
		upper = upper_bound(num);
		lower = lower_bound(num);
		cout << upper - lower << " ";
	}
	cout << "\n";
}