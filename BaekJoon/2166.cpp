// 2166.cpp
// 다각형의 면적
// 이 문제는 벡터의 외적 개념, 다각형의 면적 알고리즘, CCW 알고리즘 이 모두를
// 알아야 풀 수 있다.
// 이 모든 기반 지식을 찾아서 공부하고 정리하기 까지 6일이 소요되었다!!!
// 다각형의 면적은 시작점을 중심으로 여러 삼각형으로 나누고 각 삼각형의
// 면적을 합해서 구한다. 삼각형의 면적은 CCW 알고리즘을 이용하고 CCW에서 리턴한 값은
// 삼각형 면적의 2배이므로 합산된 면적의 절대값에 1/2을 곱해서 구한다.
// 문제의 조건이 좌표의 절대값이 최대 100,000이기 때문에 100,000*100,000은 int 범위를 넘어간다.
// 따라서 x, y 좌표의 type을 int가 아니라 long long type으로 해야 함을 유의해야 한다!!!
// 이것때문에 2번씩이나 문제를 틀렸다!!!
// 제한시간 2초 중 0ms(2144KB)가 소요되었다.
// 맞은사람 1304 중 528로 상위 40.49%에 rank되었다.

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue

using namespace std;

struct point {
	long long x;
	long long y;
	point() {}
	point(long long x, long long y) : x(x), y(y) {}
};

int N;
vector<point> LOC;

long long ccw(const point& p1, const point& p2, const point& p3)
{
	return (p1.x*p2.y + p2.x*p3.y + p3.x*p1.y - (p2.x*p1.y + p3.x*p2.y + p1.x*p3.y));
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	long long area = 0;
	cin >> N;
	LOC.resize(N + 1);
	for (int i = 1; i <= N; i++) {
		cin >> LOC[i].x >> LOC[i].y;
	}
	for (int i = 2; i < N; i++) {
		area += ccw(LOC[1], LOC[i], LOC[i + 1]);
	}
	cout << fixed;
	cout.precision(1);
	cout << fabs(area*0.5) << "\n";
}