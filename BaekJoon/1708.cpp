// 1708.cpp
// *) Graham's Scan 사용
// 블록 껍질(Convex Hull)
// 기본적인 convex hull을 구하는 문제이다.
// 알고리즘은 따로 정리하였고,
// 주어진 점을 시계 반대 방향으로 정렬해야 하는데 이를 위해 벡터의 외적을 이용한 CCW를 사용한다.
// 보통 CCW는 기준점 포함 점 3개를 입력받는데, 아래와 같이 점 2개로도 구할수 있다.
// 이차원 평면상에서 벡터의 외적 A(a1,b1) X B(a2,b2) = (0, 0, a1b2 - a2b1) = (0, 0, (x2-x1)(y3-y1)-(x3-x1)(y2-y1))
// = (0, 0, x1y2 + x2y3 + x3y1 - x2y1 - x3y2 - x1y3)
// 위에서 모든 점에 대해 (x2-x1), (y3-y1), (x3-x1), (y2-y1)를 미리 구해 놓으면 이 값만 가지고 외적을 구해서
// 외적이 0보다 크면 시계반대방향(+각도)의 위치에 있다고 볼 수 있으므로 이를 기준으로 정렬한다.
// ---> 개정판!!!
//      comp를 이렇게 구현하면 복잡하니 sort할 때 최초 기준점(point[0])과 두 점으로 반시계 방향을 따지니깐
//      기준점, 비교할 두 점 의 세점을 가지고 CCW돌리면 된다. CCW가 0이면 같은 라인에 있으므로 이 때는 y, x순으로 오름차순 비교한다.
// x, y 좌표 범위의 절대값이 40,000이므로 실제 범위는 80,000이다. int(32bit) 범위를 넘을 수 있으므로 계산시 long long 사용하자.
// 제한시간 2초 중 44ms(3,552KB)가 소요되었다.
// 개정된 버전으로 돌리면 36ms(2772KB)가 소요된다.(Graham's Scan 개정한 버전 사용해도 시간은 같다.)
// 맞은사람 430/1561로 상위 27.54%에 rank되었다.

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
		return (y != rhs.y) ? y < rhs.y : x < rhs.x; // y 기준 오름차순 정렬
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

	swap(vpoints[0], *min_element(vpoints.begin(), vpoints.end())); // 가장 작은 y point가 0번으로
	sort(vpoints.begin() + 1, vpoints.end(), comp); // 1번부터 끝까지 시계반대방향으로 정렬
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