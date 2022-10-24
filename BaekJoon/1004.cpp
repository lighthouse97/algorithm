// 1004.cpp
// � ����
// ��� �༺�� ���� ������� �߽����� �༺�� �ݰ� ���� �ִ��� �����ϸ� �ȴ�.
// �༺�� �ݰ泻�� �ִ��� ���δ� �߽����� �����(�Ǵ� �߽���) ������ �Ÿ��� ��� �ȴ�.
// 2,020KB, 0ms �ҿ�Ǿ���.

#include "pch.h"
#include <iostream>
//#include <sstream>
//#include <string>
//#include <cstring> // strlen
//#include <cctype> // isdigit
//#include <vector>
//#include <list>
//#include <algorithm> // sort
//#include <unordered_map>
//#include <utility> // pair, make_pair()
//#include <set>
//#include <unordered_set>
//#include <cmath> // sqrt
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int distance(int x, int y)
{
	return (x * x + y * y);
}

void doTest()
{
	int x1, y1, x2, y2;
	int n;
	int cx, cy, r;
	int count = 0;

	cin >> x1 >> y1 >> x2 >> y2;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> cx >> cy >> r;
		// �����, �������� �� �༺�� ���Ե� ���(count���� �ʴ´�.)
		if (distance(cx - x1, cy - y1) < r * r && distance(cx - x2, cy - y2) < r * r)
			continue;
		else {
			if (distance(cx - x1, cy - y1) < r * r) count++;
			if (distance(cx - x2, cy - y2) < r * r) count++;
		}
	}
	cout << count << '\n';
}

int main()
{
	FAST;

	int T;
	cin >> T;
	while (T--) doTest();
}