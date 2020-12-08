// 13975.cpp
// ���� ��ġ�� 3
// priority queue�� ����ؼ� Ǯ �� �ִ�.
// priority queue�� �������� ���ķ� ��� ���Ҹ� ���� �ִ´�.
// �� ���� 2���� ������ �� ���� ���� �����Ͽ� ���� �����ϰ� ������ 2���� �ٽ� ť�� �ִ´�.
// �������� ť�� �Ѱ��� ������ �� ������ ���� �ٷ� ������ �ȴ�.
// ���ѽð� 2�� �� 808ms(18,524KB)�� �ҿ�Ǿ���.
// ������� 85/145�� ���� 58.62%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min, copy, rotate, swap
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

typedef long long ll;

void DoTest()
{
	int N, fs;
	priority_queue<ll, vector<ll>, greater<ll>> mypq;
	ll answer = 0;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> fs;
		mypq.push(fs);
	}

	ll f1, f2;
	while (mypq.size() > 1) {
		f1 = mypq.top(); mypq.pop();
		f2 = mypq.top(); mypq.pop();
		f1 += f2;
		answer += f1;
		mypq.push(f1);		
	}
	cout << answer << "\n";
}

int main()
{
	FAST;

	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
		DoTest();
}