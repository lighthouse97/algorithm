// 13547.cpp
// ������ ���� 5
// Mo's algorithm���� Ǯ��� �Ѵ�.
// ���������� ���� �ٸ� ���� ������ ����ϴ� ������
// ���� �Է� ������ 1,000,000�̹Ƿ� 1 ~ 1,000,000���� �迭�� �����
// �Է� ���� ���� count�� ����� �д�. ������ ���� +1,
// �������� ������ -1, +1���� �� 0���� 1 �ö󰡸� �ٸ� ���� ���� +1,
// -1���� �� 0�� �Ǹ� �ٸ� ���� ���� -1�� �ȴ�.
// �� �غ���!
// ������ ��ŷ�� ���� �� �˰���(�Ϻ�) + ���� Ʈ���� ����ϰ� Ǯ������,
// ���̵� �ѹ� ������ ���� �ڴ�.(���� �ʰ���!!!)
// ���ѽð� 2�� �� 236ms(9,124KB)�� �ҿ�Ǿ���.
// ������� 254/303�� ���� 83.82%�� rank�Ǿ���.

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

int g_diffcnt = 0;
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
vector<int> g_results; // 1 ~ m

void qplus(int x)
{
	if (g_counts[x]++ == 0) g_diffcnt++;
}

void qminus(int x)
{
	if(--g_counts[x] == 0) g_diffcnt--;
}

int main()
{
	FAST;
	int n, m, s, e;
	cin >> n;
	g_nums.resize(n + 1, 0);
	g_counts.resize(maxlimit + 1, 0);	
	g_sqrtn = (int)sqrt(n);
	for (int i = 1; i <= n; i++)
		cin >> g_nums[i];
	cin >> m;
	g_results.resize(m, 0);
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
		g_results[g_queries[i].index] = g_diffcnt;
	}
	for (int x : g_results)
		cout << x << "\n";
}