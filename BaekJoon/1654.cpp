// 1654.cpp
// ���� �ڸ���
// �Էµ� ������ ���� ���� ������ �������� [1, len] �迭�� �����,
// ��ǥ������ �����ϴ� upper bound���� �̺� Ž������ ���Ѵ�.
// ���� upper_bound �˰����� �״�� ����ϸ� Ʋ����.
// �ݷʰ� �ִ�. 4 4 -> 10 10 10 10 (������ 10�ε� ���� upper_bound ����ϸ� 9�� ���´�)

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