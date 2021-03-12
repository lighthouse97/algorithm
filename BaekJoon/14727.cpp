// 14727.cpp
// ���� �ڸ���
// University > �߾Ӵ��б� > 2017 �߾Ӵ��б� ���α׷��� ������ȸ(CPC) B��
// ������׷� ����(6549, 1725, 2104)�� �����ϴ�.
// ������׷� ������ ���� �������� ���� ������ ���� ���� ���� ������ ��ǥ ������ �����ȴ�.
// ���ѽð� 2�� �� 16ms(2,936KB)�� �ҿ�Ǿ���.
// ������� 61/239�� ���� 25.52%�� rank�Ǿ���.

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

int main()
{
	FAST;
	int n;
	vector<int> num;
	stack<int> st;

	cin >> n;
	num.resize(n + 1, 0);

	int right, left, height;
	ll area, maxval = 0;
	for (int i = 1; i < n + 1; i++) {
		cin >> num[i];
		if (st.empty()) st.push(i);
		else {
			if (num[st.top()] <= num[i]) st.push(i);
			else {
				while (!st.empty() && num[st.top()] > num[i]) {
					right = i - 1;
					height = num[st.top()];
					st.pop();
					left = st.empty() ? 1 : st.top() + 1;
					area = 1LL * (right - left + 1) * height;
					maxval = max(maxval, area);
				}
				st.push(i);
			}
		}
	}
	right = n;
	while (!st.empty()) {
		height = num[st.top()];
		st.pop();
		left = st.empty() ? 1 : st.top() + 1;
		area = 1LL * (right - left + 1) * height;
		maxval = max(maxval, area);
	}
	cout << maxval << "\n";
}