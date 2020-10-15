// 9240.cpp
// 로버트 후드
// *) Graham's Scan + rotating calipers
// convex hull에서 더 나아가 convex hull 상의 점에서 가장 먼 거리를 구하는 문제이다.
// 이 문제는 Graham's Scan + rotating calipers 알고리즘을 이용한다.
// rotating calipers는 별도로 문서로 알고리즘을 정리하였다.(convex hull 문서에 정리하였다.)
// 일단 먼저 convex hull을 구해야 하므로 앞의 1708의 소스를 활용하였다.
// ICPC > Regionals > Europe > Northwestern European Regional Contest > Nordic Collegiate Programming Contest > NCPC 2013 D번
// 구현이 복잡해서 종만북 참조하였다.
// 그리고 문제에서 최대 점의 갯수가 많지가 않아서 rotating calipers 사용않하고 O(n^2)으로 푸는게 더 빠르다.
// 개정판 --> 소스 정리하고 구조 개선했는데, 실행시간이 40ms -> 64ms로 더 많이 걸렸다.
//            rotating calipers에서 각 점의 단위 벡터를 while문에서 실시간으로 구했는데, 이 것을 미리 구해야 겠다!
//            미리 구하고 하니 60ms 걸린다. (40ms나온 경우는 소스가 지저분해서 그냥 이걸루 써야 겠다)
//            Graham, rotating calipers함수 개정해서 32ms(2,784KB) 나온다.
// 제한시간 1초 중 40ms(3,700KB)가 소요되었다.(개정소스 : 32ms(2,784KB))
// 맞은사람 257/640로 상위 40.15%에 rank되었다. (52/637, 8.16%)

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
			if (ccw(p1, p2, p3) > 0) next = (next + 1) % size; // ccw 방향이면 다음 next로 넘어간다.
			else break;
		}
		temp = (vpoints[chull[next]] - vpoints[chull[i]]).distance(); // 다음 꼭지점으로 진행하다가 ccw -> cw로 바뀌는 지점이 현 기준에서 최대 거리이다.		
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