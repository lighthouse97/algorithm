// 5639_1.cpp
// ���� �˻� Ʈ��
// �տ��� Ǭ ���� �� �� ����ȭ���״�.
// post_order()������ while������ �ϳ��� ã�� ����
// std::lower_bound()�� �̿��Ͽ� ���� Ž���Ͽ� Ž���ð��� �ٿ���
// ��ü������ ���� �ð��� �ٿ���.
// ����� ����ð��� Ȯ���� �پ��µ�, 36ms(2308KB) -> 0ms(2312KB)�� �پ���.
// ��ü ���� ��� 1442�� �� 4������ ���� 0.27%�� �����. (�������� ���� 21.98% ���� �Ͽ���)

#include "pch.h"
#include <cstdio> // NULL
#include <iostream>
//#include <cstring> // memset
#include <vector>
#include <algorithm> // sort, max, min, lower_bound
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <cmath> // sqrt
//#include <queue>

using namespace std;

vector<int> PRE_ORDER;

void post_order(vector<int>::iterator start, vector<int>::iterator end)
{
	int root;
	vector<int>::iterator position;
	if (start >= end) return;
	root = *start;
	position = lower_bound(start + 1, end, root);
	post_order(start + 1, position); // LEFT
	post_order(position, end); // RIGHT
	cout << root << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int num;
	PRE_ORDER.push_back(0);
	while (cin >> num) PRE_ORDER.push_back(num);
	post_order(PRE_ORDER.begin() + 1, PRE_ORDER.end());
}