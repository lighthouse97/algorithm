// 7420.cpp
// 맹독 방벽(Wall)
// 이 문제 어찌보면 간단한 문제인데 방향 잡는데 하루종일 걸렸다.
// 예제에 나와있는 그림이 바로 문제 풀이 방법이다.
// convex hull을 구한다음 이를 가지고 벽의 길이를 구한다.
// 처음 생각했던게 다 틀렸다! 다시 하자!
// 1) 각 꼭지점을 연결하는 다각형의 변의 전체 길이를 구한다.
// 2) 각 꼭지점에서 가장 가까운 벽의 끝점과 끝점을 이어주는 원호의 길이를 구한다.
// 1) + 2) = 구하는 벽의 전체 길이 이다.
// 2)를 구하기 위해서 그림을 그려 잘 관찰하면 각 꼭지점에서 도형의 내각은 (180도-원호의 각) 이다.
// 꼭지점이 n개 있으면 내각의 합은 n*PI - (theta1 + ... thetan) = (n-2)PI 이다. (다각형의 내각의 합은 (n-2)PI 이다)
// 풀어서 정리하면 (theta1 + ... thetan) = 2PI 이다
// 다각형에서 꼭지점이 2개(1개는 문제 제약에서 나올 수가 없다) 일 때는 위 식에 넣어도 되지만 직관적으로도 양 끝의 180도를 더해 2PI이다.
// 모든 꼭지점의 원호의 길이 총합은 (theta1 + ... thetan)/2PI * 2PI*r = (theta1 + ... thetan)*r = 2PI*r이다. 즉 원주의 길이이다.
// 정리하면 벽의 총 길이는
// (각 꼭지점을 연결하는 다각형의 변의 전체 길이) + 2PI*r 이다.
// ICPC > Regionals > Northern Eurasia > Northern Eurasia Finals > NEERC 2001 D번
// 제한시간 1초 중 0ms(2,132KB)가 소요되었다. (벡터를 일반 배열로 사용하면 메모리 더 절약되고 랭킹도 올라갈 것이다)
// 맞은사람 60/96로 상위 62.5%에 rank되었다.

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

const double PI = 3.14159265;

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

	int n, r;
	int size;
	vector<int> chull;
	double result = 0;
	
	cin >> n >> r;
	vpoints.resize(n, { 0, 0 });
	for (int i = 0; i < n; i++)
		cin >> vpoints[i].x >> vpoints[i].y;
	chull = graham_scan();
	size = chull.size();
	
	for (int i = 0; i < size; i++) { // 외벽 변의 길이의 합을 구한다.
		result += (vpoints[chull[(i + 1) % size]] - vpoints[chull[i]]).distance();
	}   
	result += 2 * PI * r; // 원호의 길이의 합을 구한다.
	cout << (int)round(result) << "\n";
}