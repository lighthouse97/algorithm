// 10254.cpp
// 고속도로
// *) 더 빠른 최적화된 방법 사용
// convex hull과 rotating calipers를 동시에 사용하는 문제이다.
// 종만북에 있는 rotating calipers 방법을 사용하면 시간 초과가 발생해서 다른 방법으로 rotating calipers를 사용하여 수행 시간을 
// 더 빠르게 하려고 한다. 이 방법은 unit vector를 안써니 double 연산도 하지 않고 모두 정수 연산만으로 끝난다.
// 간단한 원리는 한 변에서 시작하여 시계 반대 방향으로 각 변을 이동하면서 두 변사이의 방향이 CCW -> CW로 바뀌는 지점이
// 가장 먼 지점이다.(원과 접선을 생각해 보면 이해가 쉽다.) 이를 모든 변에 대해서 반복해서 최대값을 찾는다.
// ICPC > Regionals > Asia Pacific > Korea > Nationwide Internet Competition > Daejeon Nationalwide Internet Competition 2014 E번
// main()에 FAST를 빼먹는 실수가 있었다. 이거 빼면 제한 시간 2초에 겨우 들어맞게 된다.
// 제한시간 2초 중 668ms(5,116KB)가 소요되었다. (순위를 보니 배열을 벡터 사용하지 않고 단순 배열쓰면 좀 더 빠를 것이다)
// 맞은사람 81/342로 상위 23.68%에 rank되었다.

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
	long long cross = (1LL*p1.x*p2.y + 1LL*p2.x*p3.y + 1LL*p3.x*p1.y) - (1LL*p2.x*p1.y + 1LL*p3.x*p2.y + 1LL*p1.x*p3.y);
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

void rotating_calipers(const vector<int>& chull) // 종만북보다 더 빠르고 간단한 방법으로 해 보자!
{
	int size = chull.size(), next;
	point p1 = { 0, 0 }, p2, p3, max_a, max_b;
	double maxval = 0, temp;
	next = 1;
	for (int i = 0; i < size; i++) {				
		while (true) {
			p2 = vpoints[chull[(i + 1) % size]] - vpoints[chull[i]];
			p3 = vpoints[chull[(next + 1) % size]] - vpoints[chull[next]];
			if (ccw(p1, p2, p3) > 0) next = (next + 1) % size; // ccw 방향이면 다음 next로 넘어간다.
			else break;
		}
		
		temp = (vpoints[chull[next]] - vpoints[chull[i]]).distance(); // 다음 꼭지점으로 진행하다가 ccw -> cw로 바뀌는 지점이 현 기준에서 최대 거리이다.		
		if (temp > maxval) {
			maxval = temp;
			max_a = vpoints[chull[i]];
			max_b = vpoints[chull[next]];
		}
	}
	cout << max_a.x << " " << max_a.y << " " << max_b.x << " " << max_b.y << "\n";
}

void do_test()
{
	int n;
	vector<int> chull;
	
	cin >> n;
	vpoints.resize(n, { 0, 0 });
	for (int i = 0; i < n; i++)
		cin >> vpoints[i].x >> vpoints[i].y;

	chull = graham_scan();
	rotating_calipers(chull);	
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