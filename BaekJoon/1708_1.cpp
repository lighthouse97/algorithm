// 1708_1.cpp
// *) gift wrapping 사용
// 1708(convex hull)문제를 graham's scan으로 풀었는데,
// 선물 포장 알고리즘(gift wrapping algorithm)으로도 풀 수 있기 때문에
// 이번에는 이 알고리즘으로 풀어보고 수행 시간을 비교해 보기로 한다.
// 결과를 보니 전체 점의 갯수가 작을 때에는 graham's scan 방법보다 gift wrapping algorithm이 수행시간이 더 짧았다.
// 44ms(3,552KB) -> 28ms(2,780KB) 로 수행시간이 줄어 들었다!
// 제한시간 2초 중 28ms(2,780KB)가 소요되었다.
// 맞은사람 7/1562로 상위 0.44%에 rank되었다. (430/1561, 27.54% -> 7/1562, 0.44%)

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
		next = vpoints[0]; // 처음에는 {pivot, point[0]} 으로 시작
		for (int i = 1; i < n; i++) {
			ok = false;
			cross = ccw(pivot, next, vpoints[i]);
			if (cross > 0) ok = true; // 시계 반대 방향
			else if(cross == 0) { // 겹침
				if (((next - pivot).distance() - (vpoints[i] - pivot).distance()) < 0) ok = true; // 겹치면 멀리 있는 점 선택
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