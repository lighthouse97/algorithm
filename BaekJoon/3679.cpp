// 3679.cpp
// �ܼ� �ٰ���
// convex hull�� �����ϴ� �����̴�. Graham Scan�� ��ó���� y�� ���� ���� ������ �ݽð� ��������
// ���ĸ� �ϸ� Ǯ�� ������ ����ȴ�.
// �̷��Ը� Ǯ�� Ʋ����!
// �������� ������� ����Ǵ� ������ �������� �� ������ �ָ��ִ� ������ ��ġ�Ǿ�� �Ѵ�.
// ó�� ������� Ǯ�� ������ �������� ���鿡 ���ؼ��� ��ġ�� �����ָ� �ȴ�.
// ���߻� + â������ ������ �ʿ��ѵ� �̰� �����ؼ� �Ϸ縦 �����ϰ� Ǯ���� ���ߴ�!!!
// ���� �� ������ �������� 2�� �̻� �ִ� �͵� �����̰� �������� �и��� �����ִµ�, �̰� �������� �ƴ϶�� �Ǵ��ؼ�
// �ʹ� ���� �ð��� ����Ͽ���. ������ ����� �������� ���ϴ� �͵� ũ��ū �����̴�!!!
// �������� ������ �������� �����Ѵ�! �̶��� �������� ������ 180�� �̴�!!!
// ICPC > Regionals > Europe > Northwestern European Regional Contest > NWERC 2009 I��
// ���ѽð� 1�� �� 12ms(2,124KB)�� �ҿ�Ǿ���.
// ������� 16/112�� ���� 14.28%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
#include <cmath> // pow, sqrt, fabs, hypot, round
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
	int index;
	point() : x(0), y(0), index(0) {}
	point(int x, int y) : x(x), y(y), index(0) {}
	bool operator < (const point& rhs) const
	{
		return (x != rhs.x) ? x < rhs.x : y < rhs.y; // x ���� �������� ����
	}
	bool operator > (const point& rhs) const
	{
		return (x != rhs.x) ? x > rhs.x : y > rhs.y;
	}
	bool operator <= (const point& rhs) const
	{
		return !(*this > rhs);
	}
	bool operator >= (const point& rhs) const
	{
		return !(*this < rhs);
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

vector<point> vpoints;

int ccw(const point& p1, const point& p2, const point& p3)
{
	long long cross = (1LL * p1.x*p2.y + 1LL * p2.x*p3.y + 1LL * p3.x*p1.y) - (1LL * p2.x*p1.y + 1LL * p3.x*p2.y + 1LL * p1.x*p3.y);
	return (cross > 0) ? 1 : (cross == 0) ? 0 : -1;
}

bool comp_y(const point& a, const point& b)
{
	return (a.y != b.y) ? a.y < b.y : a.x < b.x;
}

bool comp_c(const point& a, const point& b)
{
	int cross = ccw(vpoints[0], a, b);
	if (cross > 0) return true;
	else if (cross == 0) return (a.y != b.y) ? a.y < b.y : a.x < b.x;
	return false;
}

void draw_polygon()
{
	vector<point> chull;	
	int n = vpoints.size();
	
	swap(vpoints[0], *min_element(vpoints.begin(), vpoints.end(), comp_y)); // ���� ���� y point�� 0������
	sort(vpoints.begin() + 1, vpoints.end(), comp_c); // 1������ ������ �ð�ݴ�������� ����
	// ������ ������ �������� �� ó��
	int cnt = 0;
	for (int i = n - 2; i >= 0; i--) {
		if(ccw(vpoints[0], vpoints[n-1], vpoints[i]) == 0) cnt++;
		else break;
	}
	reverse((vpoints.end() - 1) - cnt, vpoints.end());	
	for (point p : vpoints)
		cout << p.index << " ";
	cout << "\n";
}

void do_test()
{
	int n;
	vector<point> poly;
	cin >> n;
	vpoints.resize(n, { 0, 0 });
	for (int i = 0; i < n; i++) {
		cin >> vpoints[i].x >> vpoints[i].y;
		vpoints[i].index = i;
	}
	draw_polygon();
}

int main()
{
	FAST;

	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		do_test();
		vpoints.clear();
	}
}