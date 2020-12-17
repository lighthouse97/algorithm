// 15652_1.cpp
// N�� M (4)
// ���� 15651�� ���� ����� �ø��� �; �� �� ����ȭ ���״�.
// ��ü������ �����ϰ� ���� answer ��ºκп��� �迭�� for���� ������� �ʰ�
// string�� �̿��Ͽ� �ѹ��� ����Ͽ� ��½��� �ӵ��� �� �� ������ �Ͽ���.
// ���� �ӵ��� 4ms(2,016KB) -> 0ms(2,016KB) ���� �پ�����.
// ������� 95/7761�� ���� 1.22%�� rank�Ǿ���. (51.68% -> 1.22%)

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
//#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX, LLONG_MIN
#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int N = 0, M = 0;
string answer = "";

void BackTracking(const int& level, const int& pre)
{
	if (level > M) {
		cout << answer << "\n";
		return;
	}
	else {
		for (int i = pre; i < N + 1; i++) {
			answer.push_back(i + '0');
			answer.push_back(' ');
			BackTracking(level + 1, i);
			answer.pop_back();
			answer.pop_back();
		}
	}
}

int main() {

	FAST;

	cin >> N >> M;
	BackTracking(1, 1);
}