// 13548_1.cpp
// 수열과 쿼리 6
// 이 문제는 Mo's Algorithm으로 풀어야 한다.
// 앞에서 수행 시간이 아무래도 많이 걸린 거 같고 그 원인이 벡터 사용인 거 같아
// 배열로 바꿔서 수행해 보고자 한다.
// 역시 element의 갯수가 많을 때에는 벡터보다 배열을 사용하는 것이 수행 시간이 훨씬 더 줄어든다.
// 304ms(6,000KB) -> 236ms(5,996KB) 로 수행 시간 및 점유 메모리가 줄어들었다!
// 제한시간 2초 중 236ms(5,996KB)가 소요되었다.
// 맞은사람 99/186로 상위 53.22%에 rank되었다.

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
int g_ref_counts[maxlimit + 1] = { 0, }; // 1 ~ 100,000, 내부 값도 1 ~ 100,000
int g_results[maxlimit + 1] = { 0, }; // 1 ~ m
vector<query> g_queries; // 1 ~ m

void qplus(int x)
{
	if (g_ref_counts[g_counts[x]] > 0) g_ref_counts[g_counts[x]]--; // 기존것을 빼고
	g_counts[x]++;
	g_ref_counts[g_counts[x]]++; // 더해진 새로운 것을 더한다
	g_maxcnt = max(g_maxcnt, g_counts[x]);
}

void qminus(int x)
{
	if (x == 0) return; // 0 index는 빼기에서 제외!
	g_ref_counts[g_counts[x]]--; // 기존것을 빼고
	if (g_counts[x] == g_maxcnt && g_ref_counts[g_counts[x]] == 0) g_maxcnt--;
	g_counts[x]--;
	g_ref_counts[g_counts[x]]++; // 빼진 새로운 것을 더한다
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
		while (g_queries[i].s < s) qplus(g_nums[--s]); // 왼쪽으로 확장. 자기는 뺀다
		while (g_queries[i].e > e) qplus(g_nums[++e]); // 오른족으로 확장. 자기는 뺀다
		while (g_queries[i].s > s) qminus(g_nums[s++]); // 오른쪽으로 축소. 자기 포함
		while (g_queries[i].e < e) qminus(g_nums[e--]); // 왼쪽으로 축소. 자기 포함
		g_results[g_queries[i].index] = g_maxcnt;
	}
	for (int i = 0; i < m; i++)
		cout << g_results[i] << "\n";
}