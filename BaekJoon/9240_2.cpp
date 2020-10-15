// 9240_2.cpp
// 로버트 후드 PART III
// *) 이번에는 Graham's Scan + O(N^2)으로 비교해 본다!
// 이참에 Graham's Scan 구현도 업그레이드 해 보기로 한다.
// 역시 Graham's Scan + O(N^2)으로 하니 28ms로 시간이 많이 줄었다.
// 시간을 비교하면 다음과 같다.
// 1. Graham's Scan + O(N^2) ->            28ms(2,784KB) (32ms(2,784KB) : 소스 개정 후)
// 2. Graham's Scan + Rotating Calipers -> 32ms(2,784KB)
// 3. Gift Wrapping + O(N^2) ->           208ms(2,784KB)
// 이 문제는 테스트 데이터의 샘플 갯수가 많아서인지 Gift Wrapping이 시간이 가장 많이 걸린다.
// 문제에서 처럼 좌표의 범위가 작을 때는 O(N^2)이 더 유리할 수 있지만 범위가 커지면 연산 시간이 많이 걸려
// 연산 횟수가 적은 Rotating Calipers가 더 유리하다.(내가 내린 결론이다)
// 제한시간 1초 중 28ms(2,784KB)가 소요되었다. (소스 개정 후 : 32ms, 2,784KB)
// 맞은사람 23/633로 상위 3.63%에 rank되었다. (257/640, 상위 40.15% --> 23/633, 상위 3.63%)

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

int main()
{
	FAST;

	int n, size;
	vector<int> chull;
	double ret = 0;

	cin >> n;
	vpoints.resize(n, { 0, 0 });
	for (int i = 0; i < n; i++)
		cin >> vpoints[i].x >> vpoints[i].y;
	
	chull = graham_scan();
	size = chull.size();
	// O(N^2)
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == j) continue;
			ret = max(ret, (vpoints[chull[j]] - vpoints[chull[i]]).distance());
		}
	}
	cout << fixed;
	cout.precision(8);
	cout << ret << "\n";
}