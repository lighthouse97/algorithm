// 9240_1.cpp
// 로버트 후드 PART II
// *) Gift Wrapping algorithm + O(n^2)
// 9240 로버트후드를 복잡하게 하지 않고 Gift Wrapping algorithm과 O(n^2)으로
// 풀어봐서 수행 시간을 비교해 본다.
// 즉, Graham's Scan & Rotating Calipers VS Gift Wrapping & O(n^2)의 비교이다.
// 헉! 40ms(3,700KB) -> 208ms(2,784KB)로 수행 시간이 5배 더 많이 걸린다!
// 채점 문제의 N갯수에 따라서 차이가 나는 것으로 보인다.

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
vector<point> chulls; // convex hull array

int ccw(const point& p1, const point& p2, const point& p3)
{
	long long cross = (1LL * p1.x*p2.y + p2.x*p3.y + p3.x*p1.y) - (1LL * p2.x*p1.y + p3.x*p2.y + p1.x*p3.y);
	return (cross > 0) ? 1 : (cross == 0) ? 0 : -1;
}

void gift_wrapping()
{	
	point start, pivot, next;
	int n = vpoints.size();

	start = *min_element(vpoints.begin(), vpoints.end()); // left most & low most
	chulls.push_back(start);
	bool ok = false; int cross;
	while (true) {
		pivot = chulls.back();
		next = vpoints[0]; // 처음에는 {pivot, point[0]} 으로 시작
		for (int i = 1; i < n; i++) {
			ok = false;
			cross = ccw(pivot, next, vpoints[i]);
			if (cross > 0) ok = true; // 시계 반대 방향
			else if (cross == 0) { // 겹침
				if (((next - pivot).distance() - (vpoints[i] - pivot).distance()) < 0) ok = true; // 겹치면 멀리 있는 점 선택
			}
			if (ok) next = vpoints[i];
		}
		if (next == start) break;
		chulls.push_back(next);
	}
}

int main()
{
	FAST;

	int n;
	double ret = 0;	

	cin >> n;
	vpoints.resize(n, { 0, 0 });
	for (int i = 0; i < n; i++)
		cin >> vpoints[i].x >> vpoints[i].y;

	gift_wrapping();
	int size = chulls.size();
	for (int i = 0; i < size; i++) { // O(N^2)
		for (int j = 0; j < size; j++) {
			if (i == j) continue;
			ret = max(ret, (chulls[j] - chulls[i]).distance());
		}
	}
	cout << fixed;
	cout.precision(8);
	cout << ret << "\n";
}