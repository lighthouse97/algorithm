// 3679.cpp
// 단순 다각형
// convex hull을 응용하는 문제이다. Graham Scan의 전처리로 y가 가장 낮은 점에서 반시계 방향으로
// 정렬만 하면 풀릴 것으로 예상된다.
// 이렇게만 풀면 틀린다!
// 마지막에 출발점과 연결되는 점들이 일직선일 때 순서가 멀리있는 순으로 배치되어야 한다.
// 처음 생각대로 풀되 마지막 일직선인 점들에 대해서만 조치를 취해주면 된다.
// 역발상 + 창의적이 접근이 필요한데 이게 부족해서 하루를 낭비하고도 풀지를 못했다!!!
// 또한 한 직선에 꼭지점이 2개 이상 있는 것도 정답이고 예제에도 분명히 나와있는데, 이게 꼭지점이 아니라고 판단해서
// 너무 많은 시간을 허비하였다. 문제를 제대로 이해하지 못하는 것도 크나큰 문제이다!!!
// 직선에도 도형의 꼭지점은 존재한다! 이때의 꼭지점의 각도는 180도 이다!!!
// ICPC > Regionals > Europe > Northwestern European Regional Contest > NWERC 2009 I번
// 제한시간 1초 중 12ms(2,124KB)가 소요되었다.
// 맞은사람 16/112로 상위 14.28%에 rank되었다.

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

void draw_polygon()
{
	vector<point> chull;	
	int n = vpoints.size();
	
	swap(vpoints[0], *min_element(vpoints.begin(), vpoints.end(), comp_y)); // 가장 작은 y point가 0번으로
	sort(vpoints.begin() + 1, vpoints.end(), comp_c); // 1번부터 끝까지 시계반대방향으로 정렬
	// 마지막 점들이 일직선일 때 처리
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