// 1300.cpp
// K��° ��
// �̺� Ž������ Ǯ �� �ִ�.
// start = 1, end = K, mid�� mid��ȣ�� �־����� ���° ���ΰ��� ����Ѵ�.
// ���° ���� K���� ���ų� ũ�� (start, mid - 1)�� ������ ������
// ���° ���� K���� ������ (mid + 1, end)�� ������ Ű���.
// k��°���� k�� ��ġ�� �׻� �ڿ� ���� �� �ۿ� ���ٴ� �Ϳ� �����Ѵ�.
// ���� ��� 4�� 8��°�̰� 3�� 5��°�� ���Ǹ�, 6��° ~ 8��°�� 4�̹Ƿ�
// 7��°���� ���ϸ� 4�� �ȴ�.
// ���� ��� N�� 4�̸�,
// 01 02 03 04 (mid=4�϶�, 4/1 = 4)
// 02 04 06 08 (4/2 = 2)
// 03 06 09 12 (4/3 = 1)
// 04 08 12 16 (4/4 = 1)
// mid=4�϶� 8��°�� �ִ�.(4�� �����϶� 4�� �������� 8��°�̴�)
// mid=3�϶� 5��°�� �ִ�. (���� 6, 7, 8��°�� ��� 4�̴�)

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
//#include <vector>
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

	int N, K;
	int start, end, mid, ans = 0;
	long long cnt = 0;

	cin >> N >> K;
	
	start = 1;
	end = K;
	while (start <= end) {
		mid = (start + end) >> 1;
		cnt = 0;
		for (int i = 1; i <= N; i++)
			cnt += min(mid / i, N);
		if (cnt >= K) {
			ans = mid;
			end = mid - 1;
		}
		else start = mid + 1;
	}
	cout << ans << "\n";
}