// 11658_1.cpp
// 구간 합 구하기 3
// "구간 합 구하기 3"를 일단 누적합으로 간단하게 풀어보기로 하자.
// 일단 이렇게 무식하게 해도 맞기는 맞았다. 아마 N값이 작아서 그런 모양이다.
// 다음은 팬 윅 트리로 풀어서 얼마나 빨리 나오는지 살펴보자!
// 2차원 세그먼트 트리로 해서 다른 사람이 푼 것을 참고해보니 316ms 정도로 별 차이가 없다.
// (https://blog.naver.com/rdd573/221134152363)
// 제한시간 1초 중 328ms(10,324KB)가 소요되었다.
// 맞은사람 363/531로 상위 68.36%에 rank되었다.

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