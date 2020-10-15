// 1991.cpp
// Ʈ�� ��ȸ ���� �����̴�.
// �ʵ��л��� �� Ǫ�� �����̴�. �ݹ� Ǯ��!!!
// ���ѽð� 2�ʿ��� 0ms(1984KB) �ҿ�Ǿ���.

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
vector<vector<char>> TREE; // [][0] : left. [][1] : right

void pre_order(char cur)
{
	if (cur == '.') return;
	cout << cur;
	pre_order(TREE[cur - 'A'][0]);
	pre_order(TREE[cur - 'A'][1]);
}

void in_order(char cur)
{
	if (cur == '.') return;
	in_order(TREE[cur - 'A'][0]);
	cout << cur;
	in_order(TREE[cur - 'A'][1]);
}

void post_order(char cur)
{
	if (cur == '.') return;
	post_order(TREE[cur - 'A'][0]);
	post_order(TREE[cur - 'A'][1]);
	cout << cur;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	char p, l, r;
	cin >> N;
	TREE.resize(26, vector<char>(2, 0));
	for (int i = 0; i < N; i++) {
		cin >> p >> l >> r;
		TREE[p - 'A'][0] = l;
		TREE[p - 'A'][1] = r;
	}
	pre_order('A');
	cout << "\n";
	in_order('A');
	cout << "\n";
	post_order('A');
	cout << "\n";
}