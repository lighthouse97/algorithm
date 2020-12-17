// 15650.cpp
// N�� M (2)
// ���� N�� M (1)�� ������ ���(������ �޶� �ణ �ٸ���)���� Ǯ�� �ȴ�.
// BackTracking �Լ��� ���� level�� ���õ� index�� parameter�� �߰��� �� �Ѱ��ش�.
// ���� ���õ� item�� ���� ���ο� (i <= pre) ���Ǹ�
// �߰��� �ָ� �ȴ�.
// ���ѽð� 1�� �� 0ms(2,016KB)�� �ҿ�Ǿ���.
// ������� 5115/9022�� ���� 56.69%�� rank�Ǿ���.

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
		for (int i = 1; i < N + 1; i++) {
			if (i <= pre) continue;
			else {				
				answer[level] = i;
				BackTracking(level + 1, i);				
			}
		}
	}
}

int main() {

	FAST;

	cin >> N >> M;	
	answer.resize(M + 1, 0);
	BackTracking(1, 0);
}