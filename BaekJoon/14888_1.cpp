// 14888_1.cpp
//������ �����ֱ�
// �տ� 14888���� Ǭ �͵� ������ ����ð��� 216ms�� 0ms�� ��κ��� �����ǿ� ����
// ����� �ʹ� ���Ҵ�.
// ũ�� �ǹ̴� ���� ���� ����� �ø��� ���� ��¦ '����'�� �ߴ��� BackTracking �Ķ���ͷ�
// +, -, *, / ������ ���� ��θ� �״�� �Ѱܼ� �� �����ڸ��� recursive ȣ���� ���� �� �־���.
// ���� level�� �ѱ� ������ ���� ������ ������ 1�� �����ϹǷ� Ư�� level���� 0�� �Ǹ� �ش� �����ڴ�
// �� �̻� ������� �ʰ� �� ���̴�.
// �̷��� Ǯ�� for�� ȣ���� ���� �پ��� ����ð��� ���� �پ� �� ������ ����ȴ�.
// �̷��� �� Ǯ���!
// ����Ե� �̷��� Ǫ��(���� Ƚ���� ������ ���̰� �پ ��ġ ���� ������ ȿ���� ���� �� ����.)
// ����ð��� 216ms -> 0ms�� �پ�����.
// ���ѽð� 2�� �� 0ms(2,016KB)�� �ҿ�Ǿ���.
// ������� 5472/10649�� ���� 51.38%�� rank�Ǿ���.


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

void BackTracking(const int& level, const int& sum, const int& plus, const int& minus, const int& mul, const int& div)
{
	if (level > N - 1) {
		minval = min(minval, sum);
		maxval = max(maxval, sum);
		return;
	}

	if (plus) // �� level���� plus ����
		BackTracking(level + 1, sum + NUMS[level + 1], plus - 1, minus, mul, div);
	if (minus) // �� level���� minus ����
		BackTracking(level + 1, sum - NUMS[level + 1], plus, minus - 1, mul, div);
	if (mul) // �� level���� multiply ����
		BackTracking(level + 1, sum * NUMS[level + 1], plus, minus, mul - 1, div);
	if (div) // �� level���� divide ����
		BackTracking(level + 1, sum / NUMS[level + 1], plus, minus, mul, div - 1);
}

int main()
{
	FAST;

	int plus, minus, mul, div;
	cin >> N;
	NUMS.resize(N + 1, 0);
	for (int i = 1; i < N + 1; i++) cin >> NUMS[i];
	cin >> plus >> minus >> mul >> div;
	BackTracking(1, NUMS[1], plus, minus, mul, div);

	cout << maxval << "\n";
	cout << minval << "\n";
}