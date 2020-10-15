// 11658_1.cpp
// ���� �� ���ϱ� 3
// "���� �� ���ϱ� 3"�� �ϴ� ���������� �����ϰ� Ǯ���� ����.
// �ϴ� �̷��� �����ϰ� �ص� �±�� �¾Ҵ�. �Ƹ� N���� �۾Ƽ� �׷� ����̴�.
// ������ �� �� Ʈ���� Ǯ� �󸶳� ���� �������� ���캸��!
// 2���� ���׸�Ʈ Ʈ���� �ؼ� �ٸ� ����� Ǭ ���� �����غ��� 316ms ������ �� ���̰� ����.
// (https://blog.naver.com/rdd573/221134152363)
// ���ѽð� 1�� �� 328ms(10,324KB)�� �ҿ�Ǿ���.
// ������� 363/531�� ���� 68.36%�� rank�Ǿ���.

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

vector<vector<int>> g_nums;
vector<vector<int>> g_sums;

int main()
{
	FAST;

	int n, m, num, diff, type, a, b, c, d, sum;	
	cin >> n >> m;
	g_nums.resize(n + 1, vector<int>(n + 1, 0));
	g_sums.resize(n + 1, vector<int>(n + 1, 0));

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> num;
			g_nums[i][j] = num;
			g_sums[i][j] = g_sums[i][j - 1] + num;
		}
	}

	for (int i = 0; i < m; i++) {
		cin >> type;
		// update
		if (type == 0) {
			cin >> a >> b >> c;
			diff = c - g_nums[a][b];
			g_nums[a][b] = c;
			for (int j = b; j <= n; j++) {
				g_sums[a][j] += diff;
			}
		}
		// sum
		else if (type == 1) {
			cin >> a >> b >> c >> d;
			sum = 0;
			for (int i = a; i <= c; i++) {
				sum += (g_sums[i][d] - g_sums[i][b - 1]);
			}
			cout << sum << "\n";
		}
	}
}