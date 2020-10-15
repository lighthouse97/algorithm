// 7420.cpp
// �͵� �溮(Wall)
// �� ���� ����� ������ �����ε� ���� ��µ� �Ϸ����� �ɷȴ�.
// ������ �����ִ� �׸��� �ٷ� ���� Ǯ�� ����̴�.
// convex hull�� ���Ѵ��� �̸� ������ ���� ���̸� ���Ѵ�.
// ó�� �����ߴ��� �� Ʋ�ȴ�! �ٽ� ����!
// 1) �� �������� �����ϴ� �ٰ����� ���� ��ü ���̸� ���Ѵ�.
// 2) �� ���������� ���� ����� ���� ������ ������ �̾��ִ� ��ȣ�� ���̸� ���Ѵ�.
// 1) + 2) = ���ϴ� ���� ��ü ���� �̴�.
// 2)�� ���ϱ� ���ؼ� �׸��� �׷� �� �����ϸ� �� ���������� ������ ������ (180��-��ȣ�� ��) �̴�.
// �������� n�� ������ ������ ���� n*PI - (theta1 + ... thetan) = (n-2)PI �̴�. (�ٰ����� ������ ���� (n-2)PI �̴�)
// Ǯ� �����ϸ� (theta1 + ... thetan) = 2PI �̴�
// �ٰ������� �������� 2��(1���� ���� ���࿡�� ���� ���� ����) �� ���� �� �Ŀ� �־ ������ ���������ε� �� ���� 180���� ���� 2PI�̴�.
// ��� �������� ��ȣ�� ���� ������ (theta1 + ... thetan)/2PI * 2PI*r = (theta1 + ... thetan)*r = 2PI*r�̴�. �� ������ �����̴�.
// �����ϸ� ���� �� ���̴�
// (�� �������� �����ϴ� �ٰ����� ���� ��ü ����) + 2PI*r �̴�.
// ICPC > Regionals > Northern Eurasia > Northern Eurasia Finals > NEERC 2001 D��
// ���ѽð� 1�� �� 0ms(2,132KB)�� �ҿ�Ǿ���. (���͸� �Ϲ� �迭�� ����ϸ� �޸� �� ����ǰ� ��ŷ�� �ö� ���̴�)
// ������� 60/96�� ���� 62.5%�� rank�Ǿ���.

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

const double PI = 3.14159265;

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

	int n, r;
	int size;
	vector<int> chull;
	double result = 0;
	
	cin >> n >> r;
	vpoints.resize(n, { 0, 0 });
	for (int i = 0; i < n; i++)
		cin >> vpoints[i].x >> vpoints[i].y;
	chull = graham_scan();
	size = chull.size();
	
	for (int i = 0; i < size; i++) { // �ܺ� ���� ������ ���� ���Ѵ�.
		result += (vpoints[chull[(i + 1) % size]] - vpoints[chull[i]]).distance();
	}   
	result += 2 * PI * r; // ��ȣ�� ������ ���� ���Ѵ�.
	cout << (int)round(result) << "\n";
}