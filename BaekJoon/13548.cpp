// 13548.cpp
// 수열과 쿼리 6
// 이 문제는 Mo's Algorithm으로 풀어야 한다.
// 모스 알고리즘이 뭔지 모르고 그냥 단순하게 풀면 당연히
// 시간 초과가 발생한다.
// 모스 알고리즘 중 난이도가 제법 높은 문제이다.
// 아이디어는 남이 푼 것을 참고했다.
// 세그먼트 트리로 풀 수도 있지만 최적화 못하면 시간초과 발생할 수 있다.
// 기본 아이디어는 입력 수의 빈도수를 기록하는 count[] 배열과
// 카운트 배열의 반복 횟수의 카운트를 기록하는 ref_count[] 배열을 가지고
// (예를 들어 구간에서 1이 3번, 3이 3번 있으면 ref_count[3] = 2가 된다)
// 모스 알고리즘에 응용해서 푼다.
// 자세한 것은 소스를 봐야만 이해가 가능하다.
// qplus()함수 구현하면서 마지막에 maxcnt값 구할 때, cnt[]값하고 비교를 해야 맞는데,
// cnt[]값의 카운트 값인 ref_cnt[cnt[]]값의 엉뚱한 값하고 비교해서 출력초과가 계속 났었다!!!
// 정신차리자!!!
// vector 말고 베열로 풀면 좀 더 빨리 처리되지 않을 까 싶다.
// 제한시간 2초 중 304ms(6,000KB)가 소요되었다.
// 맞은사람 147/186로 상위 79.03%에 rank되었다.

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

vector<int> g_nums; // 1 ~ n
vector<int> g_counts; // 1 ~ 100,000
vector<int> g_ref_counts; // 1 ~ 100,000, 내부 값도 1 ~ 100,000
vector<query> g_queries; // 1 ~ m
vector<int> g_results; // 1 ~ m

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
	g_nums.resize(n + 1, 0);
	g_counts.resize(maxlimit + 1, 0);
	g_ref_counts.resize(maxlimit + 1, 0);
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
		g_results[g_queries[i].index] = g_maxcnt;
	}
	for (int i = 0; i < m; i++)
		cout << g_results[i] << "\n";	
}