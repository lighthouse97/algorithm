// 1655.cpp
// ����� ���ؿ�
// �켱���� ť 1��, ���� 1���� �̿��ؼ� �����Ѵ�.
// �Ʒ��� ���� �����ϸ� ���� �������� �ð��ʰ��� �߻��Ѵ�.
// �� �� ����ȭ ���Ѿ� �ڴ�!
// �ƿ� ����� �ٲپ���!
// ���� ť�� ��������, ������ ť�� �������� ���ķ� �Ͽ�
// ������ ť�� top���� ���� ���� ���� ť�� �׷��� ������ ������ ť�� �ִ´�.
// ��� ������ ũ�Ⱑ 1�� �Ѿ�� ������ �뷱���� �����.
// ������ ũ�Ⱑ ������ left�� top �ƴϸ� ū ���� top�� ����ϸ� �ȴ�.
// ó������ 2820KB, 28ms �̰� �Ʒ� ����ȭ��Ű�� 2804KB, 24ms �̴�.

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
#include <queue>

using namespace std;

#if 0
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, num, tmp;
	priority_queue<int> left;
	priority_queue<int, vector<int>, greater<int>> right;

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> num;
		if (i == 0) {
			cout << num << "\n";
			tmp = num;
		}
		else if (i == 1) {
			if (tmp < num) {
				left.push(tmp);
				right.push(num);
			}
			else {
				left.push(num);
				right.push(tmp);
			}
			cout << left.top() << "\n";
		}
		else {
			if (num < right.top()) left.push(num);
			else right.push(num);
			if ((int)(left.size() - right.size()) >= 2) {
				right.push(left.top());
				left.pop();
			}
			else if ((int)(right.size() - left.size()) >= 2) {
				left.push(right.top());
				right.pop();
			}
			//cout << "left = " << left.top() << ", right = " << right.top() << "\n";
			if (left.size() >= right.size()) cout << left.top() << "\n";
			else cout << right.top() << "\n";
		}
	}
}
#else // �� ��Ŀ��� �� �� ����ȭ ���Ѻ��Ҵ�.
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, num;
	priority_queue<int> left;
	priority_queue<int, vector<int>, greater<int>> right;

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> num;
		if (left.empty() || left.top() >= num) left.push(num);
		else right.push(num);
		if (left.size() >= right.size() + 2) { right.push(left.top()); left.pop(); }
		else if (right.size() >= left.size() + 1) { left.push(right.top()); right.pop(); }
		cout << left.top() << "\n";
	}
}

#endif