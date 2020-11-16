// 15678.cpp
// ����������ũ
// University > �������б� > 2018 �������б� ��ǻ�Ͱ��а� ���α׷��� ������ȸ L��
// ���� 5977�� ������ �����̴�.
// �������α׷��ְ� deque�� �����ϸ� �ȴ�.
// DP[i]�� index i���� i-D���� ���ǿ� �°� ¡�˴ٸ� �ǳ��� ���� ���� ū ������� �Ѵٸ�,
// ��ȭ����
// DP[i] = max((max(DP[j]) + A[i]), A[i]), (i-D <= j <= i-1)
// max(DP[j])�� i-1���� D����ŭ(i-D����) deque�� �̿��ؼ�(�տ��� ���ݱ��� �ߴ� �� ó��...) ���ϸ� �ȴ�.
// �� Ǯ���!
// ���ѽð� 1�� �� 16ms(3,740KB)�� �ҿ�Ǿ���.
// ������� 29/222�� ���� 13.06%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

typedef pair<long long, int> pli;

int main()
{
	FAST;

	int N, D, k;
	long long ans;	
	deque<pli> mydq;

	cin >> N >> D;	

	long long maxval;
	cin >> maxval;
	mydq.push_back({ maxval, 1 });
	ans = maxval;
	for (int i = 2; i < N + 1; i++) {
		cin >> k;
		if (!mydq.empty() && mydq.front().second < i - D) mydq.pop_front();
		maxval = max(mydq.front().first + k, (1LL)*k);		
		ans = max(ans, maxval);
		if (i == N) break;
		while (!mydq.empty() && mydq.back().first < maxval) mydq.pop_back();
		mydq.push_back({maxval, i});						
	}
	cout << ans << "\n";
}