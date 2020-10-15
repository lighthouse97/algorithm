// 8462.cpp
// 배열의 힘
// 이 문제 역시 Mo's Algorithm을 응용하는 문제이다.
// 13547(수열과 쿼리 5)를 풀었으면, 쉽게 응용해서 풀 수 있다.
// 문제를 잘 보면 공식을 만들 수 있는데, 특정 수 k의 반복 회수를 a라고 할 때,
// 특정 수 k가 구간에서 더해지면 (2a+1)*k를 기존 구간의 값에 더해주면 되고,
// 특정 수 k가 구간에서 빠지면 (2a-1)*k를 기존 구간의 합에서 빼주면 된다.
// 그리고 각 구간의 합계값이 int type 범위를 벗어날 수 있으므로 long long type으로 선언해야 한다.
// 자 함 풀어보자!
// Camp > POI Training Camp > ONTAK 2011 6-2번 (폴란드 문제)
// 제한시간 3초 중 196ms(8,256KB)가 소요되었다.
// 맞은사람 18/147로 상위 12.24%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
#include <cmath> // pow, sqrt, fabs, ceil, log2
#include <vector>
#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <functional> // less, greater
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

long long g_sum = 0;
int g_sqrtn;
const int maxlimit = 1000000;

struct query {
	int s, e, index; // index : query index
	query() : s(0), e(0), index(0) {}
	query(int s, int e, int i) : s(s), e(e), index(i) {}
	bool operator < (const query& comp) const
	{
		if ((s - 1) / g_sqrtn != (comp.s - 1) / g_sqrtn) return ((s - 1) / g_sqrtn < (comp.s - 1) / g_sqrtn);
		return e < comp.e;
	}
};

vector<int> g_nums; // 1 ~ n
vector<int> g_counts; // 1 ~ 100,000
vector<query> g_queries; // 1 ~ m
vector<long long> g_results; // 1 ~ m

void qplus(int x)
{
	g_sum += (2 * (long long)g_counts[x] + 1)*x;
	g_counts[x]++;
}

void qminus(int x)
{
	g_sum -= (2 * (long long)g_counts[x] - 1)*x;
	g_counts[x]--;
}

int main()
{
	FAST;
	int n, m, s, e;
	cin >> n >> m;
	g_nums.resize(n + 1, 0);
	g_counts.resize(maxlimit + 1, 0);
	g_sqrtn = (int)sqrt(n);
	for (int i = 1; i <= n; i++)
		cin >> g_nums[i];
	g_results.resize(m, 0);
	g_queries.resize(m, { 0, 0, 0 });
	for (int i = 0; i < m; i++) {
		cin >> s >> e;
		g_queries[i] = { s, e, i };
	}
	sort(g_queries.begin(), g_queries.end());

	s = e = 0;
	for (int i = 0; i < m; i++) {
		while (g_queries[i].s < s) qplus(g_nums[--s]);
		while (g_queries[i].e > e) qplus(g_nums[++e]);
		while (g_queries[i].s > s) qminus(g_nums[s++]);
		while (g_queries[i].e < e) qminus(g_nums[e--]);
		g_results[g_queries[i].index] = g_sum;
	}
	for (long long x : g_results)
		cout << x << "\n";
}
