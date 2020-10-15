// 11658_2.cpp
// ���� �� ���ϱ� 3
// "���� �� ���ϱ� 3"�� ���� Ʈ���� Ǯ� �ð����� Ǯ�������� Ȯ���� ����.
// ������ ���� Ʈ�� ó���� �� loop�� 2�� ������. (ū loop�� row ó��, ���� loop�� column ó��)
// ���� Ʈ���� Ǫ�ϱ� ���׸�Ʈ Ʈ���� Ǯ ���� ���� �ð����� Ǯ ���� �־��� �տ��� Ǭ �����պ��ٵ�
// �� ���� Ǯ �� �ְ� �Ǿ���.
// ���� ���͸� ������� �ʰ� �Ϲ����� �迭�� ����ϸ� �� ���� ������ �� �־��� ���̴�.
// ������(328ms(10,324KB)) --> ����Ʈ��(204ms(10,324KB))
// ���ѽð� 1�� �� 204ms(10,324KB)�� �ҿ�Ǿ���.
// ������� 61/534�� ���� 11.42%�� rank�Ǿ���.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs, ceil, log2
#include <vector>
//#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <functional> // less, greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_tree;
vector<vector<int>> g_nums;
int g_N;

void update(int row, int col, int diff)
{
	int i = row, j = col;
	while (i <= g_N) { // row
		while (j <= g_N) { // column
			g_tree[i][j] += diff;
			j += (j & -j);
		}
		i += (i & -i);
		j = col;
	}
}

int sum(int row, int col)
{
	int i = row, j = col;
	int ret = 0;
   // row
	while (i > 0) { // row
		while (j > 0) { // column
			ret += g_tree[i][j];
			j -= (j & -j);
		}
		i -= (i & -i);
		j = col;
	}
	return ret;
}

int main()
{
	FAST;
	int n, m, num;
	int type, a, b, c, d, diff;
	cin >> n >> m;

	g_tree.resize(n + 1, vector<int>(n + 1, 0));
	g_nums.resize(n + 1, vector<int>(n + 1, 0));
	g_N = n;
	for(int i=1; i<=n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> num;
			g_nums[i][j] = num;
			update(i, j, num);
		}
	}

	for (int i = 0; i < m; i++) {
		cin >> type;
		if (type == 0) { // update
			cin >> a >> b >> c;
			diff = c - g_nums[a][b];
			g_nums[a][b] = c;
			update(a, b, diff);
		}
		else if (type == 1) { // sum
			cin >> a >> b >> c >> d;
			cout << (sum(c, d) - sum(a - 1, d) - sum(c, b - 1) + sum(a - 1, b - 1)) << "\n";
		}
	}
}