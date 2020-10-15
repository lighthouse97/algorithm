// 10254_1.cpp
// ��ӵ���
// *) ������ �ع� ���(�ð��ʰ�)
// convex hull�� rotating calipers�� ���ÿ� ����ϴ� �����̴�.
// ��... �����Ͽ� �ִ� rotating calipers ����� ����ϸ� ���⼭ �ð� �ʰ��� �߻��Ѵ�!!! (���⼭�� �� ��� ���!)
// ã�ƺ��� unit vector �Ⱦ��� ���� �ε��Ҽ��� ���굵 ���ϰ� ������������ �� ������ �� �� �ִ� ����� �ִµ� �� �����
// ����ؾ� �ڴ�!!!
// ����(9240)�� Ǭ ���� �����Ͽ� �� Ǯ���!
// ICPC > Regionals > Asia Pacific > Korea > Nationwide Internet Competition > Daejeon Nationalwide Internet Competition 2014 E��
// �ð� �ʰ� �߻���!!!

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
	double x, y;
	point() : x(0), y(0) {}
	point(double x, double y) : x(x), y(y) {}
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
	point operator * (double rhs) const
	{
		return point(x * rhs, y * rhs);
	}
	double distance() const
	{
		return hypot(x, y);
	}
	point normalize() const
	{
		double dist = distance();
		return point(x / dist, y / dist);
	}
	double dot(const point& rhs) const
	{
		return x * rhs.x + y * rhs.y;
	}
};

struct twopoint {
	double x1, y1, x2, y2;
	twopoint() : x1(0), y1(0), x2(0), y2(0) {}
	twopoint(double x1, double y1, double x2, double y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
};

vector<point> vpoints; // point array

int ccw(const point& p1, const point& p2, const point& p3)
{
	long long x1 = p1.x, y1 = p1.y, x2 = p2.x, y2 = p2.y, x3 = p3.x, y3 = p3.y;
	long long cross = (x1 * y2 + x2 * y3 + x3 * y1) - (x2 * y1 + x3 * y2 + x1 * y3);
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
	int first, second, next;
	int n = vpoints.size();

	swap(vpoints[0], *min_element(vpoints.begin(), vpoints.end())); // ���� ���� y point�� 0������
	sort(vpoints.begin() + 1, vpoints.end(), comp); // 1������ ������ �ð�ݴ�������� ����

	chull.push_back(0); // first
	chull.push_back(1); // second
	next = 2; // next
	while (next < n) {
		while (chull.size() >= 2) {
			second = chull.back();
			chull.pop_back();
			first = chull.back();
			if (ccw(vpoints[first], vpoints[second], vpoints[next]) > 0) { // �ð� �ݴ� ����. ��ϲ��� OK
				chull.push_back(second); // second �ٽ� �ְ�(������ first�� ��)
				break;
			}
		}
		chull.push_back(next++); // next push(������ second�� ��)
	}
	reverse(chull.begin(), chull.end()); // ������� �ð� ���� ������ ��ġ�ȴ�
	return chull;
}

twopoint rotating_calipers(const vector<int>& chull)
{
	int left, right, size;
	point calipers_a;
	vector<point> unitv; // �� ���������� ���� ������������ unit vector(����ȭ���� �̸� ���صд�)

	size = chull.size();
	unitv.resize(size, { 0, 0 });
	left = right = 0;
	double tmpl, tmpr, current;
	tmpl = tmpr = vpoints[chull[0]].x;
	for (int i = 0; i < size; i++) { // convex hull �迭���� ���� ���ʰ� ���� ������ ������ ã�´�.
		current = vpoints[chull[i]].x;
		if (current < tmpl) { tmpl = current; left = i; }
		if (current > tmpr) { tmpr = current; right = i; }
		// unit vector�� ���Ѵ�
		unitv[i] = (vpoints[chull[(i + 1) % size]] - vpoints[chull[i]]).normalize();
	}

	double maxval = (vpoints[chull[right]] - vpoints[chull[left]]).distance(); // �ʱ� max value	
	calipers_a = { 0, 1 }; // calipers �ʱⰪ ����(||)
	int movel = left, mover = right;	
	double cosL, cosR;
	int maxl = left, maxr = right; // for 2 point where max distance
	double maxdist;
	while (movel != right || mover != left) {
		cosL = calipers_a.dot(unitv[movel]); // caliper a�� ���� ������ ������ ���� �����̿�(������ cos���� ����)
		cosR = -calipers_a.dot(unitv[mover]);
		if (cosL >= cosR) { // 180�� �̳����� cos���� �� ū ���� ���� �� ���� ���̴�. ���� calipers A�� ���� ���
			calipers_a = unitv[movel]; // �� ���� ���� ���� calipers�� �ȴ�.			
			movel = (movel + 1) % size; // ���� ���� �������� �̵�			
		}
		else { // ������ calipers B�� ���� ���			
			calipers_a = -unitv[mover];
			mover = (mover + 1) % size;
		}		
		maxdist = (vpoints[chull[mover]] - vpoints[chull[movel]]).distance();
		if (maxdist > maxval) {
			maxval = maxdist;
			maxl = movel;
			maxr = mover;
		}
	}
	return twopoint(vpoints[chull[maxl]].x, vpoints[chull[maxl]].y, vpoints[chull[maxr]].x, vpoints[chull[maxr]].y);
}

void do_test()
{
	int n;
	vector<int> chull;
	twopoint answer(0, 0, 0, 0);

	cin >> n;
	vpoints.resize(n, { 0, 0 });
	for (int i = 0; i < n; i++)
		cin >> vpoints[i].x >> vpoints[i].y;

	chull = graham_scan();
	answer = rotating_calipers(chull);
	cout << fixed;
	cout.precision(0);
	cout << answer.x1 << " " << answer.y1 << " " << answer.x2 << " " << answer.y2 << "\n";
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