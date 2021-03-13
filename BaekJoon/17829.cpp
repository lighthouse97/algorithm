// 17829.cpp
// 222-풀링
// 이 문제도 분할정복으로 가로,세로 절반씩 나누어 쪼개다 보면 문제를 풀 수 있다.
// University > 홍익대학교 > 2019 홍익대학교 프로그래밍 경진대회 E번
// 제한시간 1초 중 156ms(6,264KB)가 소요되었다.
// 맞은사람 75/250로 상위 30%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_matrix;

int func(int rs, int re, int cs, int ce)
{
	int cnt = 0;
	vector<int> ord(4, 0);
	if (rs == re) { // 최소 unit				
		return g_matrix[rs][cs];
	}
	int mid_r, mid_c;
	mid_r = (rs + re) / 2;
	mid_c = (cs + ce) / 2;
	ord[cnt++] = func(rs, mid_r, cs, mid_c); // 1 / 4(좌상단부터 시계방향으로)
	ord[cnt++] = func(rs, mid_r, mid_c + 1, ce); // 2 / 4
	ord[cnt++] = func(mid_r + 1, re, cs, mid_c); // 3 / 4
	ord[cnt++] = func(mid_r + 1, re, mid_c + 1, ce); // 4 / 4
	sort(ord.begin(), ord.end());
	return ord[2]; // 두 번째로 큰 수 return
}

int main()
{
	FAST;

	int N;
	cin >> N;
	g_matrix.resize(N + 1, vector<int>(N + 1, 0));
	for (int i = 1; i < N + 1; i++)
		for (int j = 1; j < N + 1; j++)
			cin >> g_matrix[i][j];
	cout << func(1, N, 1, N) << "\n";
}