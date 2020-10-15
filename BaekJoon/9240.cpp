// 9240.cpp
// �ι�Ʈ �ĵ�
// *) Graham's Scan + rotating calipers
// convex hull���� �� ���ư� convex hull ���� ������ ���� �� �Ÿ��� ���ϴ� �����̴�.
// �� ������ Graham's Scan + rotating calipers �˰����� �̿��Ѵ�.
// rotating calipers�� ������ ������ �˰����� �����Ͽ���.(convex hull ������ �����Ͽ���.)
// �ϴ� ���� convex hull�� ���ؾ� �ϹǷ� ���� 1708�� �ҽ��� Ȱ���Ͽ���.
// ICPC > Regionals > Europe > Northwestern European Regional Contest > Nordic Collegiate Programming Contest > NCPC 2013 D��
// ������ �����ؼ� ������ �����Ͽ���.
// �׸��� �������� �ִ� ���� ������ ������ �ʾƼ� rotating calipers �����ϰ� O(n^2)���� Ǫ�°� �� ������.
// ������ --> �ҽ� �����ϰ� ���� �����ߴµ�, ����ð��� 40ms -> 64ms�� �� ���� �ɷȴ�.
//            rotating calipers���� �� ���� ���� ���͸� while������ �ǽð����� ���ߴµ�, �� ���� �̸� ���ؾ� �ڴ�!
//            �̸� ���ϰ� �ϴ� 60ms �ɸ���. (40ms���� ���� �ҽ��� �������ؼ� �׳� �̰ɷ� ��� �ڴ�)
//            Graham, rotating calipers�Լ� �����ؼ� 32ms(2,784KB) ���´�.
// ���ѽð� 1�� �� 40ms(3,700KB)�� �ҿ�Ǿ���.(�����ҽ� : 32ms(2,784KB))
// ������� 257/640�� ���� 40.15%�� rank�Ǿ���. (52/637, 8.16%)

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

void rotating_calipers(const vector<int>& chull)
{
	int size = chull.size(), next;
	point p1 = { 0, 0 }, p2, p3;
	double maxval = 0, temp;
	next = 1;
	for (int i = 0; i < size; i++) {
		while (true) {
			p2 = vpoints[chull[(i + 1) % size]] - vpoints[chull[i]];
			p3 = vpoints[chull[(next + 1) % size]] - vpoints[chull[next]];
			if (ccw(p1, p2, p3) > 0) next = (next + 1) % size; // ccw �����̸� ���� next�� �Ѿ��.
			else break;
		}
		temp = (vpoints[chull[next]] - vpoints[chull[i]]).distance(); // ���� ���������� �����ϴٰ� ccw -> cw�� �ٲ�� ������ �� ���ؿ��� �ִ� �Ÿ��̴�.		
		maxval = max(maxval, temp);		
	}
	cout << fixed;
	cout.precision(8);
	cout << maxval << "\n";
}

int main()
{
	FAST;
	int n;
	vector<int> chull;
	double ret = 0;

	cin >> n;
	vpoints.resize(n, { 0, 0 });
	for (int i = 0; i < n; i++)
		cin >> vpoints[i].x >> vpoints[i].y;

	chull = graham_scan();	
	rotating_calipers(chull);
}