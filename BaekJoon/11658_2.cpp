// 11658_2.cpp
// 구간 합 구하기 3
// "구간 합 구하기 3"를 펜윅 트리로 풀어서 시간내에 풀어지는지 확인해 본다.
// 원리는 펜윅 트리 처리할 때 loop를 2번 돌린다. (큰 loop는 row 처리, 작은 loop는 column 처리)
// 펜윅 트리로 푸니깐 세그먼트 트리로 풀 때에 비해 시간내에 풀 수가 있었고 앞에서 푼 구간합보다도
// 더 빨리 풀 수 있게 되었다.
// 만일 벡터를 사용하지 않고 일반적인 배열을 사용하면 더 빨리 수행할 수 있었을 것이다.
// 구간합(328ms(10,324KB)) --> 펜윅트리(204ms(10,324KB))
// 제한시간 1초 중 204ms(10,324KB)가 소요되었다.
// 맞은사람 61/534로 상위 11.42%에 rank되었다.

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