// 11658.cpp
// 구간 합 구하기 3
// 앞서 푼 11660(구간 합 구하기) 는 중간이 값이 바뀌지 않는
// 조건이므로 동적 프로그래밍을 이용해서 구간 합을 풀 수 있었다.
// 이번 문제는 중간값이 빈번하게 바뀌므로 동적  프로그래밍을 이용해서는
// 문제를  풀 수 없고(풀 수는 있지만 시간 초과가 발생한다!), 세그먼트 트리를 이용해야 한다.
// 그런데 일차원이 아닌 이차원 배열에서 처리해야 하므로 세그먼트 처리가
// 꽤나 복잡해 진다.
// 하루 종일 고민해도 도저히 아이디어가 떠오르지 않아서 힌트를 참고했는데,
// 늘 그렇듯이 조금만 더 창의적인 아이디어가 떠오르면 풀 수가 있는데 그걸 극복하지 못했다.
// 아이디어는 알고보면 간단하다.
// 각 row 또는 각 column별 일차원 배열의 세그먼트 트리 하나하나를 다시 세그먼트 트리로 만들어
// 업데이트 하고, 또 구간 합을 구하면 된다!!!!! (즉 세그먼트 트리의 각 노드가 세그먼트 트리가 된다)
// 구현은 맞게 된거 같은데, 이렇게 풀면 시간 초과가 발생한다!

// 다른 방법을 고민하는 것과 팬윅 트리를 공부해서 푸는 방법이 있다.
// 팬윅 트리로 그냥 풀어야 겠다!!!
// -> 더 찾아 보니, N이 작아서 단순한 누적합 방식과 팬윅 트리 방식이 있다.
//    각각에 대해 풀어보기로 하자!

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
	if (column < start || end < column) return; // update와 상관없는 구간
	g_tree[rnode][cnode] += diff;
	if (start != end) { // leaf node가 아닌 경우
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