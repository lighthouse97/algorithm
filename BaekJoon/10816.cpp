// 10816.cpp
// �� ã��
// ���� ī�� 2
// �̺�Ž���� ����. ���ڸ� ã�� �� �Ӹ� �ƴ϶� ã�� ���ڰ� ������� �˾ƾ� �Ѵ�.
// vector�� lower bound, upper bound�� �̿��ϸ� �ݹ� Ǯ �� ������
// �̺�Ž���� �̿��Ͽ� lower bound, upper bound�� ���� ������ ����.

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