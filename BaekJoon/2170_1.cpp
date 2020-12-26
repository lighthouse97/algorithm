// 2170_1.cpp
// �տ��� �� �Ͱ� ���� ������ �ڵ带 �� �� ������ ���ƴ�.
// �־��� �ֿ��� �ߺ� ������ �����ϰ� ī��Ʈ �� ������ ���ܼ� �װ͸� ī��Ʈ�ϰ� �Ͽ���.
// ����ð��� ���� ���� ����Ǿ����� ũ�� �ǹ̴� ����.
// ���ѽð� 1�� �� 376ms(17,648KB)�� �ҿ�Ǿ���.
// ������� 130/1304�� ���� 9.96%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy, swap
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

typedef pair<int, int> pii;
vector<pii> LINE;
vector<pii> FILTER;

int main()
{
	FAST;

	int N, sum = 0;
	cin >> N;
	LINE.resize(N);
	FILTER.reserve(N);

	int s, e;
	for (int i = 0; i < N; i++) {
		cin >> s >> e;
		LINE[i] = (s < e) ? pii(s, e) : pii(e, s);
	}

	sort(LINE.begin(), LINE.end());
	FILTER.push_back(LINE[0]);
	sum += (FILTER.back().second - FILTER.back().first);
	for (int i = 1; i < N; i++) {
		if (FILTER.back().second <= LINE[i].first) { // ������ �ִ� ���
			FILTER.push_back(LINE[i]);
			sum += (FILTER.back().second - FILTER.back().first);
		}
		else if (FILTER.back().second > LINE[i].first &&
			FILTER.back().second < LINE[i].second) { // ���� �ִ� ���
			sum -= (FILTER.back().second - FILTER.back().first);
			FILTER.back().second = LINE[i].second;
			sum += (FILTER.back().second - FILTER.back().first);
		}
	}

	cout << sum << "\n";
}