// 1708.cpp
// *) Graham's Scan ���
// ��� ����(Convex Hull)
// �⺻���� convex hull�� ���ϴ� �����̴�.
// �˰����� ���� �����Ͽ���,
// �־��� ���� �ð� �ݴ� �������� �����ؾ� �ϴµ� �̸� ���� ������ ������ �̿��� CCW�� ����Ѵ�.
// ���� CCW�� ������ ���� �� 3���� �Է¹޴µ�, �Ʒ��� ���� �� 2���ε� ���Ҽ� �ִ�.
// ������ ���󿡼� ������ ���� A(a1,b1) X B(a2,b2) = (0, 0, a1b2 - a2b1) = (0, 0, (x2-x1)(y3-y1)-(x3-x1)(y2-y1))
// = (0, 0, x1y2 + x2y3 + x3y1 - x2y1 - x3y2 - x1y3)
// ������ ��� ���� ���� (x2-x1), (y3-y1), (x3-x1), (y2-y1)�� �̸� ���� ������ �� ���� ������ ������ ���ؼ�
// ������ 0���� ũ�� �ð�ݴ����(+����)�� ��ġ�� �ִٰ� �� �� �����Ƿ� �̸� �������� �����Ѵ�.
// ---> ������!!!
//      comp�� �̷��� �����ϸ� �����ϴ� sort�� �� ���� ������(point[0])�� �� ������ �ݽð� ������ �����ϱ�
//      ������, ���� �� �� �� ������ ������ CCW������ �ȴ�. CCW�� 0�̸� ���� ���ο� �����Ƿ� �� ���� y, x������ �������� ���Ѵ�.
// x, y ��ǥ ������ ���밪�� 40,000�̹Ƿ� ���� ������ 80,000�̴�. int(32bit) ������ ���� �� �����Ƿ� ���� long long �������.
// ���ѽð� 2�� �� 44ms(3,552KB)�� �ҿ�Ǿ���.
// ������ �������� ������ 36ms(2772KB)�� �ҿ�ȴ�.(Graham's Scan ������ ���� ����ص� �ð��� ����.)
// ������� 430/1561�� ���� 27.54%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct point {
	int x, y;
	point() : x(0), y(0) {}
	point(int x, int y) : x(x), y(y) {}
	bool operator < (const point& rhs) const
	{
		return (y != rhs.y) ? y < rhs.y : x < rhs.x; // y ���� �������� ����
	}
	bool operator == (const point& rhs) const
	{
		return (x == rhs.x && y == rhs.y);
	}
	point operator - (const point& rhs) const
	{
		return point(x - rhs.x, y - rhs.y);
	}
	point operator - () const // unary operator(-) overloading, -P
	{
		return point(-x, -y);
	}
	point operator * (int rhs) const
	{
		return point(x * rhs, y * rhs);
	}
	double distance() const
	{
		return hypot(x, y);
	}
	long long dot(const point& rhs) const
	{
		return 1LL * x * rhs.x + 1LL * y * rhs.y;
	}
};

vector<point> vpoints; // point array

int ccw(const point& p1, const point& p2, const point& p3)
{
	long long cross = (1LL * p1.x*p2.y + 1LL * p2.x*p3.y + 1LL * p3.x*p1.y) - (1LL * p2.x*p1.y + 1LL * p3.x*p2.y + 1LL * p1.x*p3.y);
	return (cross > 0) ? 1 : (cross == 0) ? 0 : -1;
}

bool comp(const point& a, const point& b)
{
	int cross = ccw(vpoints[0], a, b);
	if (cross > 0) return true;
	else if (cross == 0) return (a.y != b.y) ? a.y < b.y : a.x < b.x;
	return false;
}

vector<int> graham_scan()
{
	vector<int> chull;
	int n = vpoints.size();

	swap(vpoints[0], *min_element(vpoints.begin(), vpoints.end())); // ���� ���� y point�� 0������
	sort(vpoints.begin() + 1, vpoints.end(), comp); // 1������ ������ �ð�ݴ�������� ����
	for (int i = 0; i < n; i++) {
		while (chull.size() >= 2 && ccw(vpoints[chull[chull.size() - 2]], vpoints[chull[chull.size() - 1]], vpoints[i]) <= 0) {
			chull.pop_back();
		}
		chull.push_back(i);
	}
	return chull;
}

int main()
{
	FAST;

	int n, size;
	vector<int> chull;

	cin >> n;
	vpoints.resize(n, { 0, 0 });
	for (int i = 0; i < n; i++)
		cin >> vpoints[i].x >> vpoints[i].y;

	chull = graham_scan();
	size = chull.size();
	cout << size << "\n";
}