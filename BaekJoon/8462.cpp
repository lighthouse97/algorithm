// 8462.cpp
// �迭�� ��
// �� ���� ���� Mo's Algorithm�� �����ϴ� �����̴�.
// 13547(������ ���� 5)�� Ǯ������, ���� �����ؼ� Ǯ �� �ִ�.
// ������ �� ���� ������ ���� �� �ִµ�, Ư�� �� k�� �ݺ� ȸ���� a��� �� ��,
// Ư�� �� k�� �������� �������� (2a+1)*k�� ���� ������ ���� �����ָ� �ǰ�,
// Ư�� �� k�� �������� ������ (2a-1)*k�� ���� ������ �տ��� ���ָ� �ȴ�.
// �׸��� �� ������ �հ谪�� int type ������ ��� �� �����Ƿ� long long type���� �����ؾ� �Ѵ�.
// �� �� Ǯ���!
// Camp > POI Training Camp > ONTAK 2011 6-2�� (������ ����)
// ���ѽð� 3�� �� 196ms(8,256KB)�� �ҿ�Ǿ���.
// ������� 18/147�� ���� 12.24%�� rank�Ǿ���.

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
