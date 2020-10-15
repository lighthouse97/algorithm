// 13548_1.cpp
// ������ ���� 6
// �� ������ Mo's Algorithm���� Ǯ��� �Ѵ�.
// �տ��� ���� �ð��� �ƹ����� ���� �ɸ� �� ���� �� ������ ���� ����� �� ����
// �迭�� �ٲ㼭 ������ ������ �Ѵ�.
// ���� element�� ������ ���� ������ ���ͺ��� �迭�� ����ϴ� ���� ���� �ð��� �ξ� �� �پ���.
// 304ms(6,000KB) -> 236ms(5,996KB) �� ���� �ð� �� ���� �޸𸮰� �پ�����!
// ���ѽð� 2�� �� 236ms(5,996KB)�� �ҿ�Ǿ���.
// ������� 99/186�� ���� 53.22%�� rank�Ǿ���.

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

int g_maxcnt = 0;
int g_sqrtn;
const int maxlimit = 100000;

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

int g_nums[maxlimit + 1] = { 0, }; // 1 ~ n
int g_counts[maxlimit + 1] = { 0, }; // 1 ~ 100,000
int g_ref_counts[maxlimit + 1] = { 0, }; // 1 ~ 100,000, ���� ���� 1 ~ 100,000
int g_results[maxlimit + 1] = { 0, }; // 1 ~ m
vector<query> g_queries; // 1 ~ m

void qplus(int x)
{
	if (g_ref_counts[g_counts[x]] > 0) g_ref_counts[g_counts[x]]--; // �������� ����
	g_counts[x]++;
	g_ref_counts[g_counts[x]]++; // ������ ���ο� ���� ���Ѵ�
	g_maxcnt = max(g_maxcnt, g_counts[x]);
}

void qminus(int x)
{
	if (x == 0) return; // 0 index�� ���⿡�� ����!
	g_ref_counts[g_counts[x]]--; // �������� ����
	if (g_counts[x] == g_maxcnt && g_ref_counts[g_counts[x]] == 0) g_maxcnt--;
	g_counts[x]--;
	g_ref_counts[g_counts[x]]++; // ���� ���ο� ���� ���Ѵ�
}

int main()
{
	FAST;
	int n, m, s, e;
	cin >> n;	
	g_sqrtn = (int)sqrt(n);
	for (int i = 1; i <= n; i++)
		cin >> g_nums[i];
	cin >> m;	
	for (int i = 0; i < m; i++) {
		cin >> s >> e;
		g_queries.push_back(query(s, e, i));
	}
	sort(g_queries.begin(), g_queries.end());

	s = e = 0;
	for (int i = 0; i < m; i++) {
		while (g_queries[i].s < s) qplus(g_nums[--s]); // �������� Ȯ��. �ڱ�� ����
		while (g_queries[i].e > e) qplus(g_nums[++e]); // ���������� Ȯ��. �ڱ�� ����
		while (g_queries[i].s > s) qminus(g_nums[s++]); // ���������� ���. �ڱ� ����
		while (g_queries[i].e < e) qminus(g_nums[e--]); // �������� ���. �ڱ� ����
		g_results[g_queries[i].index] = g_maxcnt;
	}
	for (int i = 0; i < m; i++)
		cout << g_results[i] << "\n";
}