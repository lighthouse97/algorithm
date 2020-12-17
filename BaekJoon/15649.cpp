// 15649.cpp
// N�� M (1)
// �� ������ �����ϰ� for���� ���� �� �Ἥ Ǯ�� 100% TLE �߻��ϱ� ������
// BackTracking�� �̿��ؼ� Ǯ��� �Ѵ�.
// ������ü�� BackTracking�� Ȱ���ϴ� �⺻ �����̴�.
// �ռ� Ǯ���� N-Queen������ �����ϰ� Ǯ�� �ȴ�.
// level 1���� �ϳ� �����ϸ� �ش� column�� �ش��ϴ� |(������)�� marking�ϰ�
// ���� level�� �Ѿ��. ���� ���ý� marking �� ���� ���Ѵ�.
// BackTracking�� ���������� marking�� |(������)�� �����.
// ���� level�� �Ѿ�鼭 ������ count(M)�� ������ �� ���� ���� ���õ� ���� ����Ѵ�.
// ���ѽð� 1�� �� 20ms(2,016KB)�� �ҿ�Ǿ���.
// ������� 479/10198�� ���� 4.69%�� rank�Ǿ���.

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
vector<bool> A; // ������(|)
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
			if (A[i]) continue; // | üũ
			else {
				A[i] = true; // | ǥ��				
				answer[level] = i;				
				BackTracking(level + 1);
				A[i] = false; // | ����
			}
		}
	}
}

int main() {

	FAST;

	cin >> N >> M;
	A.resize(N + 1, false);
	answer.resize(M + 1, 0);
	BackTracking(1);
}