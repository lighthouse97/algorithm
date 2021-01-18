// 3273_1.cpp
// �� ���� ��
// �� �����͸� ������� �ʰ� �� ���� Ǯ �� �ִ� ����� ��½ ���� �˰ԵǾ� Ǯ��Ҵ�.
// ���� ��� X�� 13�̰� ������ ���� 2�̸� ������ �����Ϸ��� �������� 11�� �� ���;� �Ѵ�.
// ���� ������ ���� ai�̸� CHRCK[X - ai] = 1�� ��Ƴ���, ������ ���� Ž���ϴٰ� aj�� X - ai�̸�.
// CHECK[aj]�� 1�̰� �ƴϸ� 0�̹Ƿ� CHECK[aj]�� 1�� �� ��, count�� 1�� ������Ű�� �ȴ�.
// 12ms(2,408KB) -> 8ms(2,464KB)
// ���ѽð� 1�� �� 8ms(2,464KB)�� �ҿ�Ǿ���.
// ������� 3/864�� ���� 0.34%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
//#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
	FAST;

	int N, X;
	vector<int> num;
	vector<bool> check;
	cin >> N;
	num.resize(N, 0);
	for (int i = 0; i < N; i++) cin >> num[i];
	cin >> X;
	check.resize(X, false);

	int result = 0;
	for (int i = 0; i < N; i++) {
		if (X > num[i]) {
			if (check[num[i]]) result++;
			check[X - num[i]] = true;			
		}
	}
	cout << result << "\n";
}