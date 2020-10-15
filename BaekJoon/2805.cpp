// 2805.cpp
// ���� �ڸ���
// ���� �ڸ���(1654)�� �����ϰ� Ǯ�� �ȴ�.
// �ð��� 5896KB�� 180ms�� ���Դ�.

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

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M, max_val = 0;
	int start, end, mid, ans = 0;
	long long cnt = 0;

	cin >> N >> M;
	vector<int> arr(N);
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
		if (max_val < arr[i]) max_val = arr[i];
	}
	
	// ���� �� ������ �������� start, end ���� ���Ѵ�.
	start = 0;
	end = max_val;
	// �̺� Ž��
	while (start <= end) {
		mid = (start + end) >> 1;
		cnt = 0;
		for (int i = 0; i < N; i++)
			if (arr[i] > mid) cnt += (long long)(arr[i] - mid); // mid�� �߶� ���� �� �ִ� ������ �ѱ��̸� ���Ѵ�.
		if (cnt >= M) {
			if (ans < mid) ans = mid; // ������ mid(����)�� �ʿ��� ���� �̻� ���� �� �����Ƿ� �ϴ� �� ���� �����Ѵ�.
			start = mid + 1;
		}
		else end = mid - 1;
	}
	cout << ans << "\n";
}