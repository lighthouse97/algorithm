// 14751.cpp
// Leftmost Segment
// ICPC > Regionals > Asia Pacific > Korea > Nationwide Internet Competition > Daejeon Nationalwide Internet Competition 2017 F번
// 이것도 CHT(Convex Hull Trick) 문제이다.
// CHT 문제는 좀 더 연습이 필요한게 스스로 푼 문제가 하나도 없다. 이 문제도 힌트를 보고서야 풀이 방향을 알게 되었다.
// DP는 사용하지 않고 CHT만 사용한다.
// 이 문제는 x, y 좌표를 바꿔서 바라보아야만 문제를 풀 수 있다.
// x, y 바꾼 기준으로 n개의 segment가 기울기 감소 순으로 CHT 정렬할 때 최소값을 구하고
// m개의 Query가 x값(X[i])가 되어 CHT line에서 x에 해당하는 최소값을 가진 line을 찾으면 된다.
// 이게 전부이고 구현 할 때 일정 수준 이상의 technique이 필요하다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <iomanip>
//#include <cstring> // memset
#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const double EPSILON = 1e-06;

struct ConvexHull_Trick {
	struct line {
		double sl, yi; // 기울기(slope), y 절편(y-intercept)
		int i; // segment 번호
		line() : sl(0.), yi(0.), i(0) {}
		line(double a, double b, int i) : sl(a), yi(b), i(i) {}
	};
	
	vector<line> ch; // line이 convex hull을 이루는 집합	
	int top; // ch에서 top의 위치
	int minX, maxX, n, m;

	ConvexHull_Trick() : top(-1), minX(0), maxX(0), n(0), m(0) {}

	~ConvexHull_Trick() { ch.clear(); }

	// 교점을 구하는 나누기를 사용하지 않고 위치 비교만 하였다.
	bool CanRemoveLastOne(const line& t_1, const line& t, const line& nb)
	{
		double sl1, sl2, yi1, yi2;
		sl1 = t_1.sl - t.sl;
		sl2 = t.sl - nb.sl;
		yi1 = t.yi - t_1.yi;
		yi2 = nb.yi - t.yi;
		return yi1 * sl2 >= yi2 * sl1; // <= 이면 정상적으로 추가, >= 이면 왼쪽이라 제거
	}

	bool CanMoveRight(const int& l1, const int& l2, const double& x)
	{
		double y = (ch[l2].yi - ch[l1].yi);
		double s = (ch[l1].sl - ch[l2].sl);
		if(s < 0) s *= -1; y *= -1;
		return y < x * s;		
	}

	void insert(const line& ll)
	{
		///
		printf("sl = %f, yi = %f, index = %d\n", ll.sl, ll.yi, ll.i);
		if (top >= 0 && fabs(ch[top].sl - ll.sl) < EPSILON) { // 기울기가 같을 때,
			if (ll.yi < ch[top].yi) { ch[top].sl = ll.sl;  ch[top].yi = ll.yi; ch[top].i = ll.i; }
			return;
		}
		while (top >= 1 && CanRemoveLastOne(ch[top - 1], ch[top], ll))
			top--;		
		ch[++top] = ll;
		cout << "top = " << top << "\n"; ////
	}

	int FindSegment(const double& x)
	{
		int lo, hi, mid;
		lo = 0; hi = top;
		while (lo < hi) { // 이분 탐색
			mid = (lo + hi) / 2;
			if (CanMoveRight(mid, mid + 1, x)) lo = mid + 1;
			else hi = mid;
		}		
		return ch[lo].i;
	}

	line MakeLine(const int& x1, const int& y1, const int& x2, const int& y2, const int& index)
	{
		double sl = 1.0 * (y1 - y2) / (x1 - x2);
		double yi = -1.0 * (y1 - y2) / (x1 - x2) + y1;
		return { sl, yi, index };
	}

	void Solve()
	{
		// change x, y
		int yl, yr;
		vector<line> segment;
		cin >> minX >> maxX >> n;
		segment.resize(n + 1);
		ch.resize(n + 1);
		for (int i = 1; i < n + 1; i++) {
			cin >> yl >> yr;
			segment[i] = MakeLine(minX, yl, maxX, yr, i);			
		}		
		auto cmp = [&](const line& i, const line& j) {
			return i.sl > j.sl;
		};
		sort(segment.begin() + 1, segment.end(), cmp);		
		top = -1;
		for (int i = 1; i < n + 1; i++)
			insert(segment[i]); // 기울기 내림차순으로 정렬 되었으므로 ch stack에 하나씩 넣는다.
		
		cin >> m;
		double query;
		vector<int> qs;
		qs.resize(m, 0);
		for (int i = 0; i < m; i++) {
			cin >> query;
			qs[i] = FindSegment(query);
		}
		for (int x : qs)
			cout << x << "\n";		
	}
};

int main()
{
	FAST;

	ConvexHull_Trick answer;
	answer.Solve();
}
