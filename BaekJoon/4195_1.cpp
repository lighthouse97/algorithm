// 4195_1.cpp
// 친구 네트워크
// union-find 문제인데, 
// weighted union-find 를 이용하는 문제이다.
// 일반적인 union-find 해법에 level용 배열하나 더 만들어서 풀어도 되나 weighted union-find가
// 더 수행시간이 줄어들고 효율적이며 코드 읽기가 더 직관적이고 수월하다.
// weighted union-find는 root의 parent를 음수(절대값이 원소의 갯수)로 설정하는 것만 다르고 나머지는 일반적인 union-find와 동일하다.
// 이름과 숫자를 mapping시키기 위해 unordered_map<string, int> 을 사용한다.
// weighted union find를 사용하니 소요 시간이 160ms(29,660KB) -> 108ms(18,124KB)로 줄어들었다.
// 제한시간 3초 중 108ms(18,124KB)가 소요되었다.
// 맞은사람 156/3140로 상위 4.96%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
//#include <list>
//#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<int> g_parent; // disjoint set

int djs_find(int x) // find 함수
{
	if (g_parent[x] < 0) return x; // 자신이 root
	return g_parent[x] = djs_find(g_parent[x]);
}

void djs_union(int x, int y) // union 함수
{
	int r1 = djs_find(x);
	int r2 = djs_find(y);

	if (r1 == r2) return;
	g_parent[r1] += g_parent[r2];
	g_parent[r2] = r1;
}

void doTest()
{
	int f, count = 1;
	unordered_map<string, int> rel; // 이름 : 번호 mapping
	string s1, s2;
	cin >> f;
	g_parent.resize(2 * f + 1, -1); // 관계의 수가 f 이면 최대 f*2의 친구가 있을 수 있다. 최초 자신이 root, -1로 초기화
	for (int i = 0; i < f; i++) {
		cin >> s1 >> s2;
		if (rel.find(s1) == rel.end()) rel[s1] = count++;
		if (rel.find(s2) == rel.end()) rel[s2] = count++;
		djs_union(rel[s1], rel[s2]);
		int r = djs_find(rel[s1]);
		cout << -g_parent[r] << "\n"; // 관계의 root의 parent의 절대값이 전체 관계의 갯수이다.
	}
	g_parent.clear();
}

int main()
{
	FAST;
	int T;
	cin >> T;
	while (T--) doTest();
}