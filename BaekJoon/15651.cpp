// 15651.cpp
// N�� M (3)
// ���� ���� �ߺ��� ����ϹǷ� 15649 �� N�� M (1)���� �̹� ���õ�
// column������ ���ϴ� �κи� ���� �ȴ�.
// ��� ��츦 �� �غ��� �Ŷ� ����ð��� �� �� �ɸ� ������ �����ȴ�.
// ���ѽð� 1�� �� 368ms(2,016KB)�� �ҿ�Ǿ���.
// ������� 789/8144�� ���� 9.68%�� rank�Ǿ���.

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

void BackTracking(int level)
{
	if (level > M) {
		for (int i = 1; i < level; i++) cout << answer[i] << " ";
		cout << "\n";
		return;
	}
	else {
		for (int i = 1; i < N + 1; i++) {
			answer[level] = i;
			BackTracking(level + 1);
		}
	}
}

int main() {

	FAST;

	cin >> N >> M;
	answer.resize(M + 1, 0);
	BackTracking(1);
}