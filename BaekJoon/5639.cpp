// 5639.cpp
// ���� �˻� Ʈ��
// �̰� ���� ���� Ž�� Ʈ�� ���� ��ü�� ������ �߸� �����ϰ� �־
// ���� Ǫ�µ� �ð��� ���ϰ� ��ƸԾ���.
// ������ �ܾ� �ϳ��� ������ �ʰ� �Ĳ��� �� �о���� �Ѵٴ� ���� �������� ������.
// ��Ʈ����� ���ʿ� �ִ� ��� ����Ʈ���� ���� ��Ʈ��庸�� �۾ƾ� �ϴ� ������
// �и��� �ִµ��� �ұ��ϰ� ����Ʈ�� Ư�� ����� ������ ���� ��Ʈ���� �� Ŭ �� �ִٰ�
// �߸� �����ϴ� �ٶ��� ���� Ǫ�µ� �Ǹ����� ����� ������ �������ȴ�.
// ���������� ���� ù��°�� root�̰� root���� ū ���� ���ö����� Ž���ؼ� ū���� ������
// ���� ����Ʈ��, ū������ �������� ������ ����Ʈ���� �ؼ� ��͹������ Ǭ��.
// �ð����� 1�ʿ��� 36ms(2308KB) �ҿ�Ǿ���.

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
//#include <queue>

using namespace std;

vector<int> PRE_ORDER;

void post_order(int start, int end)
{
	int root, position;
	if (start > end) return;
	root = PRE_ORDER[start];
	position = start + 1;
	while ((position <= end) && (PRE_ORDER[position] < root)) {
		position++;
	}
	post_order(start + 1, position - 1); // LEFT
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
	post_order(1, (int)PRE_ORDER.size() - 1);
}