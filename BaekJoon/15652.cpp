// 15652.cpp
// N�� M (4)
// ���õ� ������ ���������ε� ���� ���� ������ �ǹǷ�,
// 15650.cpp ���� (i <= pre) ���Ǹ� (i < pre) ��������
// �ٲ��ָ� �ȴ�.
// �ƴϸ� pre���� �����ϵ��� �ϸ� �ȴ�.(������ �̷��� �����Ͽ���.)
// ���ѽð� 1�� �� 4ms(2,016KB)�� �ҿ�Ǿ���.
// ������� 4011/7760�� ���� 51.68%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int N = 0, M = 0;
vector<int> answer;

void BackTracking(const int& level, const int& pre)
{
	if (level > M) {
		for (int i = 1; i < level; i++) cout << answer[i] << " ";
		cout << "\n";
		return;
	}
	else {
		for (int i = pre; i < N + 1; i++) {
			answer[level] = i;
			BackTracking(level + 1, i);
		}		
	}
}

int main() {

	FAST;

	cin >> N >> M;
	answer.resize(M + 1, 0);
	BackTracking(1, 1);
}