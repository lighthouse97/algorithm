// 17387.cpp
// 선분 교차 2
// 17386 선분 교차 1에서 제대로 풀었기 때문에 17386과 소스는 동일하다.
// 제한시간 0.25초 중 0ms(1984KB)가 소요되었다.
// 맞은사람 82 중 23로 상위 28.04%에 rank되었다.

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
//#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue

using namespace std;

struct point {
	long long x;
	long long y;
};

bool operator<  (const point& lhs, const point& rhs)
{
	return lhs.x < rhs.x || (!(rhs.x < lhs.x) && lhs.y < rhs.y);
}

bool operator>  (const point& lhs, const point& rhs)
{
	return lhs.x > rhs.x || (!(rhs.x > lhs.x) && lhs.y > rhs.y);
}

bool operator<=  (const point& lhs, const point& rhs)
{
	return !(lhs > rhs);
}

bool operator>=  (const point& lhs, const point& rhs)
{
	return !(lhs < rhs);
}

int ccw(const point& p1, const point& p2, const point& p3)
{
	long long result = p1.x*p2.y + p2.x*p3.y + p3.x*p1.y - (p2.x*p1.y + p3.x*p2.y + p1.x*p3.y);
	return (result > 0 ? 1 : result < 0 ? -1 : 0);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int ab, cd;
	bool result;
	point line[4];
	// A B : 0 1
	// C D : 2 3
	for (int i = 0; i < 4; i++)
		cin >> line[i].x >> line[i].y;
	ab = ccw(line[0], line[1], line[2])*ccw(line[0], line[1], line[3]);
	cd = ccw(line[2], line[3], line[0])*ccw(line[2], line[3], line[1]);
	if (ab == 0 && cd == 0) {
		if (line[0] > line[1]) swap(line[0], line[1]);
		if (line[2] > line[3]) swap(line[2], line[3]);
		result = (line[2] <= line[1] && line[0] <= line[3]);
	}
	else result = (ab <= 0 && cd <= 0);
	cout << result << "\n";
}