// 1920.cpp
// 수 찾기
// 이분탐색

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

bool binary_search(const int& size, const int& val)
{
	int start = 0;
	int end = size-1;
	int mid;

	while (start <= end) {
		mid = (start + end) / 2;
		if (val == arr[mid]) return true;
		else if (val < arr[mid]) {
			end = mid - 1; // 중요!
		}
		else {
			start = mid + 1;
		}
	}
	return false;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M, size, num;
	bool result = false;
	cin >> N;
	arr = vector<int>(N);
	for (int i = 0; i < N; i++)
		cin >> arr[i];
	sort(arr.begin(), arr.end());

	cin >> M;
	size = (int)arr.size();
	for (int i = 0; i < M; i++) {
		cin >> num;
		result = binary_search(size, num);
		cout << (result ? 1 : 0) << "\n";
	}
}