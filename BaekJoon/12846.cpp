// 12846.cpp
// ������ �Ƹ�����Ʈ
// University > ���Ǵ��б� > SCCC 2016 Summer Contest H��
// �տ��� Ǭ ������׷�(6549, 1725) ������ ������ ������ ���� �ȴ�!!!
// ó���� ���� ���ظ� ���ؼ� �������� ������ ������ �� ������ ������׷� ������ ���ٴ� ���� �����ϰ� �Ǿ���.
// ���������� ������ ���׸�Ʈ Ʈ���� Ǯ�ų� ������ �̿��ؼ� Ǯ �� �ִ�.
// ������ �̿��ؼ� Ǫ�� ���� �� �����ؼ� �������� ������ Ǯ��� �Ѵ�.
// ���ѽð� 1�� �� 12ms(2,400KB)�� �ҿ�Ǿ���.
// ������� 23/323�� ���� 7.12%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;
typedef long long ll;

ll do_maxPay()
{
	int N;
	ll maxval = 0;
	vector<int> pays;
	stack<int> myst;

	cin >> N;
	pays.resize(N + 1, 0);
	int left, height, right;
	ll area;
	for (int i = 1; i < N + 1; i++) {
		cin >> pays[i];
		if (myst.empty() || pays[myst.top()] <= pays[i]) myst.push(i);
		else {
			while (!myst.empty() && pays[myst.top()] > pays[i]) {
				right = i - 1;
				height = pays[myst.top()];
				myst.pop();
				left = myst.empty() ? 1 : myst.top() + 1;
				area = 1LL * (right - left + 1) * height;
				maxval = max(maxval, area);
			}
			myst.push(i);
		}
	}
	// ���� ���� ó��
	right = N;
	while (!myst.empty()) {
		height = pays[myst.top()];
		myst.pop();
		left = myst.empty() ? 1 : myst.top() + 1;
		area = 1LL * (right - left + 1) * height;
		maxval = max(maxval, area);
	}
	return maxval;
}

int main()
{
	FAST;

	cout << do_maxPay() << "\n";
}