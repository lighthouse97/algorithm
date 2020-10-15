// 17386.cpp
// ���� ���� 1
// ��ǥ���� CCW ���� �����̴�.
// ���� AB, CD�� ���� ���
// CCW(A,B,C)*CCW(A,B,D)�� CCW(C,D,A)*CCW(C,D,B)
// �� ���� ��ȣ�� ���� �� ������ �����ϴ��� �Ǵ��Ѵ�.
// 17386�� 17387�� ��� �ϳ��� Ǯ��� �Ѵ�.
// T1 = CCW(A,B,C)*CCW(A,B,D)
// T2 = CCW(C,D,A)*CCW(C,D,B)
// ��� �� ��,
// if(T1 == 0 && T2 == 0) --> A,B,C,D ��ġ ���ؼ� �Ǵ�
// else if(T1 <= 0 && T2 <= 0) --> true�� ����, �̿��� ���� ��� false�� �������� ����
// (T1 ==0 && T2 > 0) �̰ų� (T1 > 0 && T2 == 0)�� ���� ���� ���� ����!!!
// ��ǥ�� pair�� ������ < ������ A, B �Ǵ� C, D�� ��� ���� �� ū�� �� �� �ִ�.
// (first���� ���� ���ϰ� ������ second ���Ѵ�)
// A < B�� ��� �� ���� �ٲٴ� ���� std::swap()�� �̿��ϸ� �ȴ�.
// ���ǻ���!! --> ccw�� ���ϰ��� long long���� ��Ƶ� ccw*ccw�������� long long type�� overflow�� �߻��Ѵ�.
// �̷� ���� ccw ���ϰ��� ��ȣ�� üũ�Ͽ� 1, -1, 0 �߿� �ϳ��� �����ϵ��� �Ѵ�.
// �̰� ��ġä�� ���ؼ� �� Ʋ�����ȴ�!!!!!
// ���ѽð� 0.25�� �� 0ms(1984KB)�� �ҿ�Ǿ���.
// ������� 97 �� 31�� ���� 31.95%�� rank�Ǿ���.

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
#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue

using namespace std;

struct point {
	long long x;
	long long y;
};

bool operator<  (const point& lhs, const point& rhs)
{
	return lhs.x < rhs.x || (!(rhs.x < lhs.x) && lhs.y < rhs.y);
}

bool operator>  (const point& lhs, const point& rhs)
{
	return lhs.x > rhs.x || (!(rhs.x > lhs.x) && lhs.y > rhs.y);
}

bool operator<=  (const point& lhs, const point& rhs)
{
	return !(lhs > rhs);
}

bool operator>=  (const point& lhs, const point& rhs)
{
	return !(lhs < rhs);
}

int ccw(const point& p1, const point& p2, const point& p3)
{
	long long result = p1.x*p2.y + p2.x*p3.y + p3.x*p1.y - (p2.x*p1.y + p3.x*p2.y + p1.x*p3.y);
	return (result > 0 ? 1 : result < 0 ? -1 : 0);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int ab, cd;
	bool result;
	point line[4];
	// A B : 0 1
	// C D : 2 3
	for (int i = 0; i < 4; i++)
		cin >> line[i].x >> line[i].y;
	ab = ccw(line[0], line[1], line[2])*ccw(line[0], line[1], line[3]);
	cd = ccw(line[2], line[3], line[0])*ccw(line[2], line[3], line[1]);
	if (ab == 0 && cd == 0) {
		if (line[0] > line[1]) swap(line[0], line[1]);
		if (line[2] > line[3]) swap(line[2], line[3]);
		result = (line[2] <= line[1] && line[0] <= line[3]);
	}
	else result = (ab <= 0 && cd <= 0);
	cout << result << "\n";
}