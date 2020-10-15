// 9240_2.cpp
// �ι�Ʈ �ĵ� PART III
// *) �̹����� Graham's Scan + O(N^2)���� ���� ����!
// ������ Graham's Scan ������ ���׷��̵� �� ����� �Ѵ�.
// ���� Graham's Scan + O(N^2)���� �ϴ� 28ms�� �ð��� ���� �پ���.
// �ð��� ���ϸ� ������ ����.
// 1. Graham's Scan + O(N^2) ->            28ms(2,784KB) (32ms(2,784KB) : �ҽ� ���� ��)
// 2. Graham's Scan + Rotating Calipers -> 32ms(2,784KB)
// 3. Gift Wrapping + O(N^2) ->           208ms(2,784KB)
// �� ������ �׽�Ʈ �������� ���� ������ ���Ƽ����� Gift Wrapping�� �ð��� ���� ���� �ɸ���.
// �������� ó�� ��ǥ�� ������ ���� ���� O(N^2)�� �� ������ �� ������ ������ Ŀ���� ���� �ð��� ���� �ɷ�
// ���� Ƚ���� ���� Rotating Calipers�� �� �����ϴ�.(���� ���� ����̴�)
// ���ѽð� 1�� �� 28ms(2,784KB)�� �ҿ�Ǿ���. (�ҽ� ���� �� : 32ms, 2,784KB)
// ������� 23/633�� ���� 3.63%�� rank�Ǿ���. (257/640, ���� 40.15% --> 23/633, ���� 3.63%)

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
#include <cmath> // pow, sqrt, fabs, hypot
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
	double ret = 0;

	cin >> n;
	vpoints.resize(n, { 0, 0 });
	for (int i = 0; i < n; i++)
		cin >> vpoints[i].x >> vpoints[i].y;
	
	chull = graham_scan();
	size = chull.size();
	// O(N^2)
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == j) continue;
			ret = max(ret, (vpoints[chull[j]] - vpoints[chull[i]]).distance());
		}
	}
	cout << fixed;
	cout.precision(8);
	cout << ret << "\n";
}