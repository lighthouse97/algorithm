// 10254_1.cpp
// 고속도로
// *) 종만북 해법 사용(시간초과)
// convex hull과 rotating calipers를 동시에 사용하는 문제이다.
// 음... 종만북에 있는 rotating calipers 방법을 사용하면 여기서 시간 초과가 발생한다!!! (여기서는 이 방법 사용!)
// 찾아보니 unit vector 안쓰고 따라서 부동소수점 연산도 안하고 정수형만으로 더 빠르게 할 수 있는 방법이 있는데 이 방법을
// 사용해야 겠다!!!
// 이전(9240)에 푼 것을 응용하여 함 풀어보자!
// ICPC > Regionals > Asia Pacific > Korea > Nationwide Internet Competition > Daejeon Nationalwide Internet Competition 2014 E번
// 시간 초과 발생함!!!

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

	swap(vpoints[0], *min_element(vpoints.begin(), vpoints.end())); // 가장 작은 y point가 0번으로
	sort(vpoints.begin() + 1, vpoints.end(), comp); // 1번부터 끝까지 시계반대방향으로 정렬

	chull.push_back(0); // first
	chull.push_back(1); // second
	next = 2; // next
	while (next < n) {
		while (chull.size() >= 2) {
			second = chull.back();
			chull.pop_back();
			first = chull.back();
			if (ccw(vpoints[first], vpoints[second], vpoints[next]) > 0) { // 시계 반대 방향. 블록껍질 OK
				chull.push_back(second); // second 다시 넣고(다음에 first가 됨)
				break;
			}
		}
		chull.push_back(next++); // next push(다음에 second가 됨)
	}
	reverse(chull.begin(), chull.end()); // 뒤집어야 시계 방향 순으로 배치된다
	return chull;
}

twopoint rotating_calipers(const vector<int>& chull)
{
	int left, right, size;
	point calipers_a;
	vector<point> unitv; // 각 꼭지점에서 다음 꼭지점까지의 unit vector(최적화위해 미리 구해둔다)

	size = chull.size();
	unitv.resize(size, { 0, 0 });
	left = right = 0;
	double tmpl, tmpr, current;
	tmpl = tmpr = vpoints[chull[0]].x;
	for (int i = 0; i < size; i++) { // convex hull 배열에서 가장 왼쪽과 가장 오른쪽 지점을 찾는다.
		current = vpoints[chull[i]].x;
		if (current < tmpl) { tmpl = current; left = i; }
		if (current > tmpr) { tmpr = current; right = i; }
		// unit vector를 구한다
		unitv[i] = (vpoints[chull[(i + 1) % size]] - vpoints[chull[i]]).normalize();
	}

	double maxval = (vpoints[chull[right]] - vpoints[chull[left]]).distance(); // 초기 max value	
	calipers_a = { 0, 1 }; // calipers 초기값 설정(||)
	int movel = left, mover = right;	
	double cosL, cosR;
	int maxl = left, maxr = right; // for 2 point where max distance
	double maxdist;
	while (movel != right || mover != left) {
		cosL = calipers_a.dot(unitv[movel]); // caliper a와 다음 지점의 각도를 벡터 내적이용(내적에 cos값이 있음)
		cosR = -calipers_a.dot(unitv[mover]);
		if (cosL >= cosR) { // 180도 이내에서 cos값이 더 큰 것은 각이 더 작은 것이다. 왼쪽 calipers A가 작은 경우
			calipers_a = unitv[movel]; // 더 작은 각이 다음 calipers가 된다.			
			movel = (movel + 1) % size; // 다음 기준 지점으로 이동			
		}
		else { // 오른쪽 calipers B가 작은 경우			
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