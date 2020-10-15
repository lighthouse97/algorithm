// 3878.cpp
// �� �и�
// 3878�� isInside() �Լ��� ������ x��ǥ�� ������ �ʰ� ���� ���� ��� ���� CCW������ CCW > 0�ΰ���
// üũ�ϴ� �� ������ �Լ��� �����Ͽ���.
// isInside() �Լ��� �� ���������� �����ϰ� ��������� ��ü ����ð��� 8ms(1,988KB)�� 3878�� ����� �����ϴ�!!
// ��... �� ������ �������� ������ convex hull�� ���� ���Ѵ��� �� convex hull�� ���� ��ġ����
// Ȯ���� ���� �ȴ�.
// ��ġ������ ���� Ȯ����
// 1) �ٱ��� ����(y, x�� �� ���� ����)�� ������ ���� ��ȸ�ϸ鼭 �ݴ��� ������ �� ���� ���� ������ �ִ��� üũ�Ѵ�.
// 2) �ݴ��� ������ �ٱ��� ������ ������ ���ʿ� �ִ��� üũ�Ѵ�.
// 1), 2) �� �ϳ��� �����ϸ� ������ ��ħ.
// 1), 2) ��� �������� ������ ������ ��ġ�� �ʴ´�.
// 2)�� ���� �˰��� ��� ������ �����Ͽ� ������ isInside() �Լ� ���� �� �̷��� �����Ͽ���.
// 2)�� ������ x��ǥ�� ���ص� ������, �ٱ� ������ ��� ���� ���� ���� ���� CCW�� ������ ����� �׻� > 0�� ���´�.(�̰� �� �����ϰڴ�)
// ICPC > Regionals > Asia Pacific > Japan > Asia Regional Contest 2009 in Tokyo D��
// ���ѽð� 1�� �� 8ms(1,988KB)�� �ҿ�Ǿ���.
// ������� 11/143�� ���� 7.69%�� rank�Ǿ���.

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
	point() : x(0), y(0) {}
	point(int x, int y) : x(x), y(y) {}
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

vector<point> graham_scan()
{
	vector<point> chull;
	int n = vpoints.size();

	swap(vpoints[0], *min_element(vpoints.begin(), vpoints.end(), comp_y)); // ���� ���� y point�� 0������
	sort(vpoints.begin() + 1, vpoints.end(), comp_c); // 1������ ������ �ð�ݴ�������� ����
	for (int i = 0; i < n; i++) {
		while (chull.size() >= 2 && ccw(chull[chull.size() - 2], chull[chull.size() - 1], vpoints[i]) <= 0) {
			chull.pop_back();
		}
		chull.push_back(vpoints[i]);
	}
	return chull;
}

bool isInside(const point& p, const vector<point>& ch) // �� p�� ���� ch(convex hull)�� ���ԵǾ� �ִ��� ���� üũ
{
	int size = ch.size(), j;
	bool result;
	
	for (int i = 0; i < size; i++) {
		j = (i + 1) % size;
		result = ccw(ch[i], ch[j], p) > 0;
		if (!result) break;
	}
	return result;
}

bool intersect(const vector<point>& ch_b, const vector<point>& ch_w) // ���� ���� �Ǻ�
{
	int size_b, size_w;
	bool result = false; // �����ϸ� true, �������� ������ false

	// �ϳ��� �ٰ����� �ٸ� �ٰ����� ���ʿ� �� �ִ��� ���� üũ
	if (isInside(ch_b[0], ch_w) || isInside(ch_w[0], ch_b)) return true; // �ȿ� ������ �����ϴ� ������ ��

	// �� ������ ���� ���� ���� üũ
	size_b = ch_b.size(); size_w = ch_w.size();
	point a, b, c, d;
	int ab, cd;
	for (int i = 0; i < size_b; i++) {
		for (int j = 0; j < size_w; j++) {
			a = ch_b[i]; b = ch_b[(i + 1) % size_b];
			c = ch_w[j]; d = ch_w[(j + 1) % size_w];
			ab = ccw(a, b, c) * ccw(a, b, d);
			cd = ccw(c, d, a) * ccw(c, d, b);
			if (ab == 0 && cd == 0) {
				if (a > b) swap(a, b);
				if (c > d) swap(c, d);
				result = (c <= b && a <= d);
			}
			else result = (ab <= 0 && cd <= 0);
			if (result) break;
		}
		if (result) break;
	}
	return result;
}

void do_test()
{
	int n, m;
	vector<point> chull_b, chull_w;
	bool result;

	cin >> n >> m;
	vpoints.resize(n, { 0, 0 });
	for (int i = 0; i < n; i++)
		cin >> vpoints[i].x >> vpoints[i].y;
	chull_b = graham_scan(); // convex hull black

	vpoints.clear();
	vpoints.resize(m, { 0, 0 });
	for (int i = 0; i < m; i++)
		cin >> vpoints[i].x >> vpoints[i].y;
	chull_w = graham_scan(); // convex hull white

	result = intersect(chull_b, chull_w);
	cout << (result ? "NO" : "YES") << "\n";
}

int main()
{
	FAST;

	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		do_test();
		vpoints.clear();
	}
}