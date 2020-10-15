// 2162.cpp
// 선분 그룹
// 앞에서 했던 선분 교차와 유니온 파인드 두가지를
// 응용하는 문제이다.
// N!번의 모든 경우를 탐색하면서 교차가 발생하는 경우 같은 루트로 묶는다.
// 탐색이 다 끝나면 전체 루트의 수, 가장 많은 자식의 수를 찾아서 report한다.
// 제한시간 2초 중 92ms(2344KB)가 소요되었다.
// 맞은사람 820 중 452로 상위 55.12%에 rank되었다.
// 함수에 inline을 사용하거나 소스를 더 최적화 시키면 수행시간이 더 빨라지기는 하나 대신 가독성이 떨이지고 크게 의미는 없다.
// inline만 사용해서 88ms(2344KB)로 줄였다. 431/821로 상위 52.49%에 rank 되었다.

#include "pch.h"
#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue

using namespace std;

typedef pair<int, int> point;
#define x first
#define y second

int N;
vector<vector<int>> DJS; // [][0] : root, [][1] : child count

int ccw(const point& p1, const point& p2, const point& p3)
{
	int result = p1.x*p2.y + p2.x*p3.y + p3.x*p1.y - (p2.x*p1.y + p3.x*p2.y + p1.x*p3.y);
	return (result > 0 ? 1 : result < 0 ? -1 : 0);
}

bool intersection(point& a, point& b, point& c, point& d)
{
	int ab, cd;
	bool result;
	ab = ccw(a, b, c)*ccw(a, b, d);
	cd = ccw(c, d, a)*ccw(c, d, b);
	if (ab == 0 && cd == 0) {
		if (a > b) swap(a, b);
		if (c > d) swap(c, d);
		result = (c <= b && a <= d);
	}
	else result = (ab <= 0 && cd <= 0);
	return result;
}

int find_djs(int item)
{
	if (DJS[item][0] == item) return item;
	else
		return DJS[item][0] = find_djs(DJS[item][0]);
}

bool union_djs(int s1, int s2)
{
	int r1, r2;
	r1 = find_djs(s1);
	r2 = find_djs(s2);
	if (r1 == r2) return false; // already same set!
	else {
		DJS[r2][0] = r1;
		DJS[r1][1] += DJS[r2][1];
	}
	return true;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	vector<vector<point>> coord;
	int cnt = 0, maxval = 0;
	cin >> N;
	DJS.resize(N + 1, vector<int>(2));
	coord.resize(N + 1, vector<point>(2));
	for (int i = 1; i <= N; i++) {
		DJS[i] = { i, 1 };
		cin >> coord[i][0].x >> coord[i][0].y >> coord[i][1].x >> coord[i][1].y;
	}
	for (int i = 1; i <= N; i++) {
		for (int j = i + 1; j <= N; j++) {
			if (intersection(coord[i][0], coord[i][1], coord[j][0], coord[j][1]))
				union_djs(i, j);
		}
	}

	// print result
	for (int i = 1; i <= N; i++) {
		if (DJS[i][0] == i) cnt++;
		if (DJS[i][1] > maxval) maxval = DJS[i][1];
	}
	cout << cnt << "\n";
	cout << maxval << "\n";
}