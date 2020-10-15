// 2166.cpp
// �ٰ����� ����
// �� ������ ������ ���� ����, �ٰ����� ���� �˰���, CCW �˰��� �� ��θ�
// �˾ƾ� Ǯ �� �ִ�.
// �� ��� ��� ������ ã�Ƽ� �����ϰ� �����ϱ� ���� 6���� �ҿ�Ǿ���!!!
// �ٰ����� ������ �������� �߽����� ���� �ﰢ������ ������ �� �ﰢ����
// ������ ���ؼ� ���Ѵ�. �ﰢ���� ������ CCW �˰����� �̿��ϰ� CCW���� ������ ����
// �ﰢ�� ������ 2���̹Ƿ� �ջ�� ������ ���밪�� 1/2�� ���ؼ� ���Ѵ�.
// ������ ������ ��ǥ�� ���밪�� �ִ� 100,000�̱� ������ 100,000*100,000�� int ������ �Ѿ��.
// ���� x, y ��ǥ�� type�� int�� �ƴ϶� long long type���� �ؾ� ���� �����ؾ� �Ѵ�!!!
// �̰Ͷ����� 2�����̳� ������ Ʋ�ȴ�!!!
// ���ѽð� 2�� �� 0ms(2144KB)�� �ҿ�Ǿ���.
// ������� 1304 �� 528�� ���� 40.49%�� rank�Ǿ���.

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