// 17386.cpp
// 선분 교차 1
// 대표적인 CCW 응용 문제이다.
// 선분 AB, CD가 있을 경우
// CCW(A,B,C)*CCW(A,B,D)와 CCW(C,D,A)*CCW(C,D,B)
// 두 값의 부호를 보고 두 선분이 교차하는지 판단한다.
// 17386과 17387을 묶어서 하나로 풀기로 한다.
// T1 = CCW(A,B,C)*CCW(A,B,D)
// T2 = CCW(C,D,A)*CCW(C,D,B)
// 라고 할 때,
// if(T1 == 0 && T2 == 0) --> A,B,C,D 위치 비교해서 판단
// else if(T1 <= 0 && T2 <= 0) --> true면 교차, 이외의 경우는 모두 false로 교차하지 않음
// (T1 ==0 && T2 > 0) 이거나 (T1 > 0 && T2 == 0)의 경우는 생길 수가 없다!!!
// 좌표를 pair로 잡으면 < 가지고 A, B 또는 C, D중 어느 것이 더 큰지 알 수 있다.
// (first부터 먼저 비교하고 다음에 second 비교한다)
// A < B일 경우 이 둘을 바꾸는 것은 std::swap()을 이용하면 된다.
// 주의사항!! --> ccw의 리턴값을 long long으로 잡아도 ccw*ccw과정에서 long long type의 overflow가 발생한다.
// 이런 경우는 ccw 리턴값에 부호만 체크하여 1, -1, 0 중에 하나만 리턴하도록 한다.
// 이걸 눈치채지 못해서 또 틀려버렸다!!!!!
// 제한시간 0.25초 중 0ms(1984KB)가 소요되었다.
// 맞은사람 97 중 31로 상위 31.95%에 rank되었다.

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