// 14888.cpp
// ������ �����ֱ�
// �Ｚ SW ���� �׽�Ʈ ���� ���� 1
// �� ������ BackTracking���� Ǯ �� �ִ� �����̴�.
// �������� �־����� N - 1���� �����ڿ� ���� ��ȣ�� �ٿ���
// 1 ~ N-1 ������ �տ��� N�� M ����ó�� Ǯ�� �ȴ�.
// N - 1 level���� �������� ���� ���� ��� ����� ���� min, max���� ��� ���ϸ鼭
// ��� ������ BackTracking���� �� �� �غ��� �ȴ�. ��� ���տ� ���� min, max���� ã���� �ȴ�.
// ������ ������ 1�� +, 2�� -, 3�� *, 4�� / �̷� ������ ���̸� �ȴ�.
// ���� level�� �Ѿ������� �� level������ ���� ��� ����� argument�� �Ѱ��ش�.
// �־��� �Է��� ��Ģ���� �����̰� �̸� N - 1���� ������ �������� �ʱ⿡ ����� �ش�.
// 'a + b' ������ �Ѵٸ� a�� ���� level���� �Ѿ�� sum�� �ǰ� b�� NUMS[level + 1]�� �ȴ�.
// ������ ���� �׷���.
// ��� ������ �� ������ �������� �ϱ� ������ �� ������ COL[] �迭�� �ξ� ���� ���Ǵ� ������
// ���� level���� �ߺ� ������� ���ϵ��� üũ�� �ش�.
// ���ѽð� 2�� �� 216ms(2,020KB)�� �ҿ�Ǿ���.
// ������� 8866/10649�� ���� 83.25%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy
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

int N;
int minval = 1000000999, maxval = -1000000999;
vector<int> NUMS;
vector<int> OPR; // 1(+), 2(-), 3(*), 4(/)
vector<bool> COL;

int calc(const int& a, const int& b, const int& opr)
{
	int val;
	if (opr == 1) val = a + b;
	else if (opr == 2) val = a - b;
	else if (opr == 3) val = a * b;
	else val = a / b;
	return val;
}

void BackTracking(const int& level, const int& sum)
{
	if (level > N - 1) {
		minval = min(minval, sum);
		maxval = max(maxval, sum);
		return;
	}

	int isum;
	for (int i = 1; i < N; i++) {
		if (COL[i]) continue;
		COL[i] = true;
		isum = calc(sum, NUMS[level + 1], OPR[i]);
		BackTracking(level + 1, isum);
		COL[i] = false;
	}
}

int main()
{
	FAST;

	cin >> N;
	NUMS.resize(N + 1, 0);
	OPR.resize(N, 0);
	COL.resize(N, false);
	int op, cnt = 0;
	for (int i = 1; i < N + 1; i++) cin >> NUMS[i];
	for (int i = 1; i <= 4; i++) {
		cin >> op;
		while (op--)
			OPR[++cnt] = i;		
	}
	BackTracking(1, NUMS[1]);
	cout << maxval << "\n";
	cout << minval << "\n";
}