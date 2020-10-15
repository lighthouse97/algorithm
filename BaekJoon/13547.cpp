// 13547.cpp
// 수열과 쿼리 5
// Mo's algorithm으로 풀어야 한다.
// 구간내에서 서로 다른 수의 갯수를 출력하는 문제라
// 수의 입력 범위가 1,000,000이므로 1 ~ 1,000,000까지 배열을 만들고
// 입력 수에 대한 count를 기록해 둔다. 구간에 들어가면 +1,
// 구간에서 빠지면 -1, +1했을 때 0에서 1 올라가면 다른 수의 갯수 +1,
// -1했을 때 0이 되면 다른 수의 갯수 -1이 된다.
// 함 해보자!
// 상위권 랭킹을 보니 모스 알고리즘(일부) + 펜윅 트리로 깔끔하게 풀었던데,
// 아이디어를 한번 연구해 봐야 겠다.(쉽진 않겠지!!!)
// 제한시간 2초 중 236ms(9,124KB)가 소요되었다.
// 맞은사람 254/303로 상위 83.82%에 rank되었다.

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
		while (g_queries[i].s < s) qplus(g_nums[--s]); // 왼쪽으로 확장. 자기는 뺀다
		while (g_queries[i].e > e) qplus(g_nums[++e]); // 오른족으로 확장. 자기는 뺀다
		while (g_queries[i].s > s) qminus(g_nums[s++]); // 오른쪽으로 축소. 자기 포함
		while (g_queries[i].e < e) qminus(g_nums[e--]); // 왼쪽으로 축소. 자기 포함
		g_results[g_queries[i].index] = g_diffcnt;
	}
	for (int x : g_results)
		cout << x << "\n";
}