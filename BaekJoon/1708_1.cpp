// 1708_1.cpp
// *) gift wrapping ���
// 1708(convex hull)������ graham's scan���� Ǯ���µ�,
// ���� ���� �˰�����(gift wrapping algorithm)���ε� Ǯ �� �ֱ� ������
// �̹����� �� �˰��������� Ǯ��� ���� �ð��� ���� ����� �Ѵ�.
// ����� ���� ��ü ���� ������ ���� ������ graham's scan ������� gift wrapping algorithm�� ����ð��� �� ª�Ҵ�.
// 44ms(3,552KB) -> 28ms(2,780KB) �� ����ð��� �پ� �����!
// ���ѽð� 2�� �� 28ms(2,780KB)�� �ҿ�Ǿ���.
// ������� 7/1562�� ���� 0.44%�� rank�Ǿ���. (430/1561, 27.54% -> 7/1562, 0.44%)

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
#include <cmath> // pow, sqrt, fabs, hypot
#include <vector>
#include <algorithm> // sort, max, min, min_element
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
	point() {}
	point(int x, int y) : x(x), y(y) {}
	bool operator < (const point& rhs) const
	{		
		return (x != rhs.x) ? x < rhs.x : y < rhs.y;
	}
	bool operator == (const point& rhs) const
	{
		return (x == rhs.x && y == rhs.y);
	}
	point operator - (const point& rhs) const
	{
		return point(x - rhs.x, y - rhs.y);
	}
	double distance() const
	{
		return hypot(x, y);
	}
};

vector<point> vpoints; // point array

int ccw(const point& p1, const point& p2, const point& p3)
{
	long long cross = (1LL * p1.x*p2.y + p2.x*p3.y + p3.x*p1.y) - (1LL * p2.x*p1.y + p3.x*p2.y + p1.x*p3.y);
	return (cross > 0) ? 1 : (cross == 0) ? 0 : -1;
}

int gift_wrapping()
{
	vector<point> chulls;
	point start, pivot, next;
	int n = vpoints.size();

	start = *min_element(vpoints.begin(), vpoints.end()); // left most & low most
	chulls.push_back(start);
	bool ok = false; int cross;
	while (true) {
		pivot = chulls.back();
		next = vpoints[0]; // ó������ {pivot, point[0]} ���� ����
		for (int i = 1; i < n; i++) {
			ok = false;
			cross = ccw(pivot, next, vpoints[i]);
			if (cross > 0) ok = true; // �ð� �ݴ� ����
			else if(cross == 0) { // ��ħ
				if (((next - pivot).distance() - (vpoints[i] - pivot).distance()) < 0) ok = true; // ��ġ�� �ָ� �ִ� �� ����
			}
			if (ok) next = vpoints[i];
		}
		if (next == start) break;
		chulls.push_back(next);
	}

	return  chulls.size();
}

int main()
{
	FAST;	

	int n;	

	cin >> n;
	vpoints.resize(n, { 0, 0 });
	for (int i = 0; i < n; i++)
		cin >> vpoints[i].x >> vpoints[i].y;

	cout << gift_wrapping() << "\n";
}