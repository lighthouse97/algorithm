// 2261.cpp
// ���� ����� �� ��
// �� ������ �ܼ������ϰ� Ǯ�� O(N^2)���� �ð��ʰ��� �߻��ϰ�,
// line sweeping �˰����� ����ؾ� �Ѵ�.
// �̰� ���� ���� �ڷḦ ã�Ƽ� �Ϸ� ���� �ɷ� �����ߴ�.
// �ڷ��� ��ġ�� https://www.acmicpc.net/blog/view/25 �� �ִ�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
#include <set>
#include <cmath> // sqrt

using namespace std;

struct point {
	int x;
	int y;
	point() : x(0), y(0) {}
	point(int x, int y) : x(x), y(y) {}
	bool operator < (const point& A) const {
		if (y == A.y) return x < A.x;
		else return y < A.y;
	}
};

bool comp(const point& A, const point& B) {
	return A.x < B.x;
}

int distance(const point& A, const point& B) {
	return ((A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y));
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, min_d, diff;
	point now;
	cin >> n;
	vector<point> arr(n+1);
	for (int i = 1; i <= n; i++)
		cin >> arr[i].x >> arr[i].y;
	// x�� �������� ����
	sort(arr.begin()+1, arr.end(), comp);
	min_d = distance(arr[1], arr[2]);
	set<point> candidate = {arr[1], arr[2]};
	// �Էµ� ��� ���� ���� ���� ���� �� ���� �Ÿ��� ã�´�.
	for (int i = 3; i <= n; i++) {
		now = arr[i];
		// candidate x �Ÿ��� ���� min distance���� ū �͵��� ���͸��Ѵ�.
		for (auto a  = candidate.begin(); a != candidate.end();) {
			diff = now.x - (*a).x;
			if (diff*diff > min_d) {
				a = candidate.erase(a);
			}
			else {
				a++;
			}
		}
		// candidate y �Ÿ��� ���� min distance���� ū �͵��� ���͸��Ѵ�.
		int yd = (int)sqrt(min_d) + 1;
		auto lower_point = point(-100001, now.y - yd); // y�� ������  �������� x�� ���� �� �켱������ �ϱ� ����
		auto upper_point = point(100001, now.y + yd); // y�� ū��  �������� x�� ū �� �켱������ �ϱ� ����
		auto lower = candidate.lower_bound(lower_point);
		auto upper = candidate.upper_bound(upper_point);
		int temp;
		for (auto it = lower; it != upper; it++) {
			temp = distance(now, *it);
			min_d = min(min_d, temp);
		}
		candidate.insert(now);
	}

	cout << min_d << "\n";
}
