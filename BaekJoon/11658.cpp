// 11658.cpp
// ���� �� ���ϱ� 3
// �ռ� Ǭ 11660(���� �� ���ϱ�) �� �߰��� ���� �ٲ��� �ʴ�
// �����̹Ƿ� ���� ���α׷����� �̿��ؼ� ���� ���� Ǯ �� �־���.
// �̹� ������ �߰����� ����ϰ� �ٲ�Ƿ� ����  ���α׷����� �̿��ؼ���
// ������  Ǯ �� ����(Ǯ ���� ������ �ð� �ʰ��� �߻��Ѵ�!), ���׸�Ʈ Ʈ���� �̿��ؾ� �Ѵ�.
// �׷��� �������� �ƴ� ������ �迭���� ó���ؾ� �ϹǷ� ���׸�Ʈ ó����
// �ϳ� ������ ����.
// �Ϸ� ���� ����ص� ������ ���̵� �������� �ʾƼ� ��Ʈ�� �����ߴµ�,
// �� �׷����� ���ݸ� �� â������ ���̵� �������� Ǯ ���� �ִµ� �װ� �غ����� ���ߴ�.
// ���̵��� �˰��� �����ϴ�.
// �� row �Ǵ� �� column�� ������ �迭�� ���׸�Ʈ Ʈ�� �ϳ��ϳ��� �ٽ� ���׸�Ʈ Ʈ���� �����
// ������Ʈ �ϰ�, �� ���� ���� ���ϸ� �ȴ�!!!!! (�� ���׸�Ʈ Ʈ���� �� ��尡 ���׸�Ʈ Ʈ���� �ȴ�)
// ������ �°� �Ȱ� ������, �̷��� Ǯ�� �ð� �ʰ��� �߻��Ѵ�!

// �ٸ� ����� ����ϴ� �Ͱ� ���� Ʈ���� �����ؼ� Ǫ�� ����� �ִ�.
// ���� Ʈ���� �׳� Ǯ��� �ڴ�!!!
// -> �� ã�� ����, N�� �۾Ƽ� �ܼ��� ������ ��İ� ���� Ʈ�� ����� �ִ�.
//    ������ ���� Ǯ���� ����!

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
#include <cmath> // pow, sqrt, fabs, ceil, log2
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

void update_row(int cnode, int start, int end, int rnode, int column, int diff)
{
	int mid;
	if (column < start || end < column) return; // update�� ������� ����
	g_tree[rnode][cnode] += diff;
	if (start != end) { // leaf node�� �ƴ� ���
		mid = (start + end) / 2;
		update_row(2 * cnode, start, mid, rnode, column, diff); // update left child node
		update_row(2 * cnode + 1, mid + 1, end, rnode, column, diff); // update right child node
	}
}

void update(int rnode, int start, int end, int row, int column, int diff)
{
	int mid;
	if (row < start || end < row) return;
	update_row(1, 1, g_N, rnode, column, diff);
	if (start != end) {
		mid = (start + end) / 2;
		update(2 * rnode, start, mid, row, column, diff);
		update(2 * rnode + 1, mid + 1, end, row, column, diff);
	}
}

int sum_row(int cnode, int start, int end, int rnode, int left, int right)
{
	int mid;
	if (left > end || right < start) return 0; // L-R not match with the node
	else if (left <= start && end <= right) return g_tree[rnode][cnode]; // L-R match totaly with the node
	else { // L-R match partialy with the node
		mid = (start + end) / 2;
		return sum_row(2 * cnode, start, mid, rnode, left, right) + sum_row(2 * cnode + 1, mid + 1, end, rnode, left, right);
	}
}

int sum(int rnode, int start, int end, int r1, int r2, int c1, int c2)
{
	int mid;
	if (r1 > end || r2 < start) return 0;
	else if (r1 <= start && end <= r2) return sum_row(1, 1, g_N, rnode, c1, c2);
	else {
		mid = (start + end) / 2;
		return sum(2 * rnode, start, mid, r1, r2, c1, c2) + sum(2 * rnode + 1, mid + 1, end, r1, r2, c1, c2);
	}
}

int main()
{
	FAST;

	int n, m, num, diff, a, b, c, d, e;
	int h, treeSize;
	cin >> n >> m;
	g_N = n;
	g_nums.resize(n + 1, vector<int>(n + 1, 0));

	h = (int)ceil(log2(n));
	treeSize = 1 << (h + 1);
	g_tree.resize(treeSize, vector<int>(treeSize, 0));

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> num;
			g_nums[i][j] = num;
			update(1, 1, n, i, j, num);
		}
	}

	for (int i = 0; i < m; i++) {
		cin >> a;
		if (a == 0) {
			cin >> b >> c >> d;
			diff = d - g_nums[b][c];
			update(1, 1, n, b, c, diff);
		}
		else if (a == 1) {
			cin >> b >> c >> d >> e;
			cout << sum(1, 1, n, b, d, c, e) << "\n";
		}
	}
}