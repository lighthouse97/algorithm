// 3878.cpp
// 점 분리
// 3878의 isInside() 함수를 접점의 x좌표를 구하지 않고 안의 점과 모든 변과 CCW돌려서 CCW > 0인가를
// 체크하는 더 간단한 함수로 수정하였다.
// isInside() 함수는 더 직관적으로 간단하게 만들었지만 전체 수행시간은 8ms(1,988KB)로 3878의 결과와 동일하다!!
// 음... 이 문제는 검은점과 흰점의 convex hull을 각각 구한다음 각 convex hull이 서로 겹치는지
// 확인해 보면 된다.
// 겹치는지에 대한 확인은
// 1) 바깥쪽 도형(y, x가 더 작은 도형)의 각변에 대해 순회하면서 반대편 도형의 각 변과 선분 교차가 있는지 체크한다.
// 2) 반대편 도형이 바깥쪽 도형의 완전히 안쪽에 있는지 체크한다.
// 1), 2) 중 하나라도 만족하면 도형이 겹침.
// 1), 2) 모두 만족하지 않으면 도형이 겹치지 않는다.
// 2)는 기하 알고리즘 기반 지식이 부족하여 종만북 isInside() 함수 구현 및 이론을 참고하였다.
// 2)는 접점의 x좌표를 구해도 되지만, 바깥 도형의 모든 변과 도현 안의 점과 CCW를 돌리면 결과가 항상 > 0이 나온다.(이게 더 간편하겠다)
// ICPC > Regionals > Asia Pacific > Japan > Asia Regional Contest 2009 in Tokyo D번
// 제한시간 1초 중 8ms(1,988KB)가 소요되었다.
// 맞은사람 11/143로 상위 7.69%에 rank되었다.

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
		return (x != rhs.x) ? x < rhs.x : y < rhs.y; // x 기준 오름차순 정렬
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

	swap(vpoints[0], *min_element(vpoints.begin(), vpoints.end(), comp_y)); // 가장 작은 y point가 0번으로
	sort(vpoints.begin() + 1, vpoints.end(), comp_c); // 1번부터 끝까지 시계반대방향으로 정렬
	for (int i = 0; i < n; i++) {
		while (chull.size() >= 2 && ccw(chull[chull.size() - 2], chull[chull.size() - 1], vpoints[i]) <= 0) {
			chull.pop_back();
		}
		chull.push_back(vpoints[i]);
	}
	return chull;
}

bool isInside(const point& p, const vector<point>& ch) // 점 p가 도형 ch(convex hull)에 포함되어 있는지 여부 체크
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

bool intersect(const vector<point>& ch_b, const vector<point>& ch_w) // 도형 교차 판별
{
	int size_b, size_w;
	bool result = false; // 교차하면 true, 교차하지 않으면 false

	// 하나의 다각형이 다른 다각형의 안쪽에 들어가 있는지 여부 체크
	if (isInside(ch_b[0], ch_w) || isInside(ch_w[0], ch_b)) return true; // 안에 있으면 교차하는 것으로 봄

	// 두 도형의 선분 교차 여부 체크
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