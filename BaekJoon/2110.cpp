// 2110.cpp
// ������ ��ġ
// �̺� Ž���� �̿��ؼ� 2805(�����ڸ���)�� �����ϰ� Ǭ��.

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

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, C;
	int start, end, mid, ans = 0;
	int cnt, cur;

	cin >> N >> C;
	vector<int> arr(N);
	for (int i = 0; i < N; i++)
		cin >> arr[i];
	sort(arr.begin(), arr.end());

	start = 1;
	end = arr.back() - arr.front();
	// �̺� Ž��
	while (start <= end) {
		mid = (start + end) >> 1;
		cnt = 1;
		cur = 0;
		// ���� Ž���Ͽ� �������� �Ÿ��� mid���� ���ų� ũ�� ������ count ���� ��Ų��.
		for (int i = 1; i < N; i++) {
			if (arr[cur] + mid <= arr[i]) {
				cnt++;
				cur = i;
			}
		}
		if (cnt >= C) { // ������ count�� ��ǥ �������� ���ų� ũ�� �Ÿ�(mid)�� �� �ø���.
			if (ans < mid) ans = mid;
			start = mid + 1;
		}
		else end = mid - 1; // ������ ������ ��ǥ �������� ������ �Ÿ�(mid)�� �� ������.
	}
	cout << ans << "\n";
}