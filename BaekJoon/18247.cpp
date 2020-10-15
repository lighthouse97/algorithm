// 18247.cpp
// �ܿ�ձ� Ƽ�� ����
// 2019 GoodBye ���׽�Ʈ�� ���Դ� �����̰� ���� �Ⱦ���� ���̱⿡ �ٷ� Ǯ����ȴ�!
// Contest > Good Bye, BOJ > Good Bye, BOJ 2019! A��
// ���ѽð� 1�� �� 0ms(1984KB)�� �ҿ�Ǿ���.
// ������� 126/219�� ���� 57.53%�� rank�Ǿ���.

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
//#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int T, N, M;
	int target_r = 'L' - 'A' + 1;
	int target_c = 4;
	int result;
	cin >> T;
	for (int i = 0; i < T; i++) {
		cin >> N >> M;
		if (target_r <= N && target_c <= M) {
			result = (target_r - 1)*M + target_c;
			cout << result << "\n";
		}
		else cout << -1 << "\n";
	}
}