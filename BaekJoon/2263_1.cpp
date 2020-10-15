// 2263.cpp
// Ʈ���� ��ȸ
// Ʈ�� ���� �����ε� �� ����� ���� �ؾ� �Ѵ�.
// in order�ϰ� post order�ϰ� �� ���踦 �� �������ƾ� �Ѵ�.
// ���ѽð� 5�ʿ��� 1076ms(7592KB) �ҿ�Ǿ���.
// �տ��� Ǭ ���� �� �� ����ȭ ���״�.
// find_preorder() �Լ������� for loop�� ������ ���� �̸� index �迭�� ������ ���� �ٷ� ��������.
// index �迭�� ����Ͽ� ����ȭ�� �ϴ� �� �ҿ�ð��� 28ms(7856KB)�� �پ�����.

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

int N;
vector<int> IN_ORDER;
vector<int> POST_ORDER;
vector<int> INDEX;

void find_preorder(int in_start, int in_end, int post_start, int post_end)
{
	int value, position, temp;
	if ((in_start > in_end) || (post_start > post_end))
		return;
	value = POST_ORDER[post_end];
	cout << value << " ";
	if ((in_start == in_end) || (post_start == post_end)) return;
	
	position = INDEX[value];
	temp = position - in_start;
	find_preorder(in_start, position - 1, post_start, post_start + temp - 1); // LEFT
	find_preorder(position + 1, in_end, post_start + temp, post_end - 1); // RIGHT
	// post_start + position - in_start = post_start + (position - 1 - in_start) + 1
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;
	IN_ORDER.resize(N + 1, 0);
	POST_ORDER.resize(N + 1, 0);
	INDEX.resize(N + 1, 0);
	for (int i = 1; i <= N; i++) cin >> IN_ORDER[i];
	for (int i = 1; i <= N; i++) cin >> POST_ORDER[i];
	for (int i = 1; i <= N; i++) INDEX[IN_ORDER[i]] = i;
	find_preorder(1, N, 1, N);
	cout << "\n";
}