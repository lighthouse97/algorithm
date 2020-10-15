// 11758.cpp
// CCW
// �� ������ ���� �״�� CCW �˰����� �̿��϶�� �����̴�.
// CCW �˰��� �˸� �״�� �����ؼ� �ٷ� Ǯ �� �ִ�!
// ���ѽð� 1�� �� 0ms(1984KB)�� �ҿ�Ǿ���.
// ������� 2516 �� 887�� ���� 35.25%�� rank�Ǿ���.
// ��� point ����ü �ȸ���� ccw �Լ� �ȸ���� main���� ���� �ٷ� ó���ع�����
// �޸� �Ҹ� �� �� �ٿ��� ����� �ø� �� �ִµ� ���� �׷��Ա��� �� �ʿ�� ����
// ���� �ٸ� ������ �ڵ� ������ ���ؼ� �״�� �����ϱ�� �Ѵ�.

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue

using namespace std;

struct point {
	int x;
	int y;
};

int ccw(const point& p1, const point& p2, const point& p3)
{
	return (p1.x*p2.y + p2.x*p3.y + p3.x*p1.y - (p2.x*p1.y + p3.x*p2.y + p1.x*p3.y));
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int result;
	point loc[3];
	for (int i = 0; i < 3; i++)
		cin >> loc[i].x >> loc[i].y;
	result = ccw(loc[0], loc[1], loc[2]);
	cout << (result > 0 ? 1 : result < 0 ? -1 : 0) << "\n";
}