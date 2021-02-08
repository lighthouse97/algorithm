// 2104.cpp
// �κй迭 ����
// ICPC > Regionals > Northern Eurasia > Northern Eurasia Finals > NEERC 2005 F��
// ���� �������� Ǯ �� ������, ���� ������׷�(6549)ó�� ������ �̿��ؼ� Ǯ ���� �ִ�.
// Ǫ�� ����� 6549�� �������� Ǭ �Ͱ� ���� �����ϴ�.
// ���ӱ����� �����ո� �߰��Ǹ� �ȴ�.
// ���ѽð� 2�� �� 16ms(3,724KB)�� �ҿ�Ǿ���.
// ������� 180/818�� ���� 22.00%�� rank�Ǿ���.

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
	vector<ll> sums;
	stack<int> st;

	cin >> n;
	num.resize(n + 1, 0);
	sums.resize(n + 1, 0);
	
	int right, left, minval;
	ll sval, score, maxscore = 0;
	for (int i = 1; i < n + 1; i++) {
		cin >> num[i];
		sums[i] = sums[i - 1] + num[i];
		if (st.empty()) st.push(i);
		else {
			if (num[st.top()] <= num[i]) st.push(i);
			else {
				while (!st.empty() && num[st.top()] > num[i]) {
					right = i - 1;
					minval = num[st.top()];
					st.pop();
					left = st.empty() ? 1 : st.top() + 1;
					sval = sums[right] - sums[left - 1];
					score = sval * minval;
					maxscore = max(maxscore, score);
				}
				st.push(i);
			}
		}
	}
	right = n;
	while (!st.empty()) {
		minval = num[st.top()];
		st.pop();
		left = st.empty() ? 1 : st.top() + 1;
		sval = sums[right] - sums[left - 1];
		score = sval * minval;
		maxscore = max(maxscore, score);		
	}
	cout << maxscore << "\n";
}