// 14751.cpp
// Leftmost Segment
// ICPC > Regionals > Asia Pacific > Korea > Nationwide Internet Competition > Daejeon Nationalwide Internet Competition 2017 F��
// �̰͵� CHT(Convex Hull Trick) �����̴�.
// CHT ������ �� �� ������ �ʿ��Ѱ� ������ Ǭ ������ �ϳ��� ����. �� ������ ��Ʈ�� ������ Ǯ�� ������ �˰� �Ǿ���.
// DP�� ������� �ʰ� CHT�� ����Ѵ�.
// �� ������ x, y ��ǥ�� �ٲ㼭 �ٶ󺸾ƾ߸� ������ Ǯ �� �ִ�.
// x, y �ٲ� �������� n���� segment�� ���� ���� ������ CHT ������ �� �ּҰ��� ���ϰ�
// m���� Query�� x��(X[i])�� �Ǿ� CHT line���� x�� �ش��ϴ� �ּҰ��� ���� line�� ã���� �ȴ�.
// �̰� �����̰� ���� �� �� ���� ���� �̻��� technique�� �ʿ��ϴ�.
// �Ǽ��� �κ�(����� ���� ���� ã����)
// �ٺ���) X, Y �ٲپ� �Է��� �� x, y�� ��� ���� �� -> ū ������ ���� ��ƾ� �ϴµ� �ݴ�� ��Ҵ�.
// Solve()���� �Է¹��� �� minX, maxX�� ������ �ݴ�� �Է¹���. yr, yl�� ���� �ݴ�� �Է¹޾���.
// MakeLine()���� yi ����� �� x1 ���ϴ� ���� ���Ծ���!
// CanMoveRight()���� -1���� �� s, y ��� ���ؾ� �ϴµ� {}�� ���԰� s�� ������. return�� <= �ε� < �� �Ͽ���.
// �߰��� �߰�(�߿�, ���� ������ ã����)
// CanMoveRight()���� ������ �ʰ� ������ �״�� ���ؾ� ��. ���ϸ� ������ x�� EPS �̸��� ���� �Ǵ����� ����
// insert()���� ���� ���� �� y������ �� ������ top--�� �ؾ���. y������ ���ų� ū ���� �ٷ� ����
// ll�� ch[top]�� copy�ϰ� �ٷ� �����ϴ� ������ �� �ϸ� �ȵ�! �̰� ������ �Ǽ��� ���� �� �ݺ� �Ǽ��ϰ� ����!
// ���ѽð� 1�� �� 96ms(7,100KB)�� �ҿ�Ǿ���.
// ������� 14/44�� ���� 31.81%�� rank�Ǿ���.

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
//#include <utility> // pair, swap
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
		double sl, yi; // ����(slope), y ����(y-intercept)
		int i; // segment ��ȣ
		line() : sl(0.), yi(0.), i(0) {}
		line(double a, double b, int i) : sl(a), yi(b), i(i) {}
	};
	
	vector<line> ch; // line�� convex hull�� �̷�� ����	
	int top; // ch���� top�� ��ġ
	int minX, maxX, n, m;

	ConvexHull_Trick() : top(-1), minX(0), maxX(0), n(0), m(0) {}

	~ConvexHull_Trick() { ch.clear(); }

	// ������ ���ϴ� �����⸦ ������� �ʰ� ��ġ �񱳸� �Ͽ���.
	bool CanRemoveLastOne(const line& t_1, const line& t, const line& nb)
	{
		double sl1, sl2, yi1, yi2;
		sl1 = t_1.sl - t.sl;
		sl2 = t.sl - nb.sl;
		yi1 = t.yi - t_1.yi;
		yi2 = nb.yi - t.yi;
		return (yi1 * sl2 >= yi2 * sl1); // < �̸� ���������� �߰�, >= �̸� �����̶� ch[top] ����
	}

	bool CanMoveRight(const int& l1, const int& l2, const double& x)
	{
		double y = (ch[l2].yi - ch[l1].yi);
		double s = (ch[l1].sl - ch[l2].sl);
		return (fabs(y / s - x) < EPSILON || y / s < x);		
	}

	void insert(const line& ll)
	{
		if (top >= 0 && fabs(ch[top].sl - ll.sl) < EPSILON) { // ���Ⱑ ���� ��,
			if (ll.yi < ch[top].yi) top--;
			else return;
		}
		while (top >= 1 && CanRemoveLastOne(ch[top - 1], ch[top], ll))
			top--;		
		ch[++top] = ll;		
	}

	int FindSegment(const double& x)
	{
		int lo, hi, mid;
		lo = 0; hi = top;
		while (lo < hi) { // �̺� Ž��			
			mid = (lo + hi) / 2;			
			if (CanMoveRight(mid, mid + 1, x)) lo = mid + 1;
			else hi = mid;			
		}		
		return ch[lo].i;
	}

	line MakeLine(const int& x1, const int& y1, const int& x2, const int& y2, const int& index)
	{
		double sl = 1.0 * (y1 - y2) / (x1 - x2);
		double yi = -1.0 * x1 * (y1 - y2) / (x1 - x2) + y1;
		return { sl, yi, index };
	}

	void Solve()
	{
		// change x, y
		int yl, yr;
		vector<line> segment;
		cin >> maxX >> minX >> n;
		segment.resize(n + 1);
		ch.resize(n + 1);
		for (int i = 1; i < n + 1; i++) {
			cin >> yr >> yl;
			segment[i] = MakeLine(minX, yl, maxX, yr, i);
		}		
		auto cmp = [&](const line& i, const line& j) {
			return i.sl > j.sl;
		};
		sort(segment.begin() + 1, segment.end(), cmp);
		top = -1;
		for (int i = 1; i < n + 1; i++)
			insert(segment[i]); // ���� ������������ ���� �Ǿ����Ƿ� ch stack�� �ϳ��� �ִ´�.
		
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