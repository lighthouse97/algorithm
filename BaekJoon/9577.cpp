// 9577.cpp
// 토렌트
// 역시 이분 매칭은 이분 그래프 구성하는 것이 핵심이라는 것을 다시 한번 더 느꼈다. 한참을 고민했다.
// 조각과 시간(초)를 매핑하면 된다. 그리고 매핑된 시간 중 가장 큰 값을 찾으면 된다.
// 모든 조각에 대해 매칭이 안되면 -1을 출력한다.
// PS 방향은 명확한데, 구현에서 자잘한 여러가지를 고려하지 못하고 간과해서 여러번 틀렸다!
// 간과했던 점은 다음과 같다.
// 1) 조각의 번호는 n번까지만 있다. 이것을 n번 벗어난다 했다가 아니라고 했다가 문제해석 제대로 못해서 엄청 시간 잡아먹었다.
// 2) 그래프 구성할 때 '조각 - 시간'으로 이미 매핑된것은 또 매핑하지 않는다. 또 매핑하면 이분 그래프 자체가 안되어 더 이상 진행이
//    전혀 의미가 없다. 당연히 정답이 나올리가 없다.
//    이 부분 고려하지 못하고 소흘이 넘어가다가 이거 때문에 낭비 시간 중 80%를 잡아먹었다!!!
// 3) 이분 그래프 매핑할 때 시간은 오름차순으로 정렬해야 한다. 입력을 다 모아서 오름차순으로 다시 매핑해야지 입력하면서
//    바로 매핑시키면 시간 오름차순 정렬이 안되어 나중에 이분 매칭후에 조건 만족하는 최소 시간이 나올 수 없게 된다.
//    역시 이거 간과해서 전체 낭비 시간의 15% 잡아먹었다.
// 4) g_matched는 조각번호(1부터 시작)가 할당이 되기 때문에 0으로 초기화해도 된다. 이걸 -1로 하느니 0으로 하느니
//    쓸데없는 고민하다가 시간을 많이 낭비했다.
// 5) 이분 그래프에 시간 매핑할 때, (t1, t2]이렇게 해도 된다. 참고자료는 [t1, t2) 이렇게 많이들 잡았는데, 차이가 있는 것인지 아닌지
//    한참을 시간 낭비하면서 고민했는데 역시 부질없는 짓이었다.
// 6) 이분 그래프를 '조각 - 시간'으로 잡고 풀었는데 이렇게 풀어도 전혀 문제없다.
//    참고 자료들이 대부분 '시간 - 조각'으로 매핑을 해서 이게 맞는 건지 햇갈려 또 한참 시간 낭비했는데 역시 부질없는 짓이었다!!
// 제한시간 2초 중 4ms(2,156KB)가 소요되었다.
// 맞은사람 89/310로 상위 28.70%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil, hypot
#include <vector>
//#include <list>
#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
//#include <string> // string, stoi
//#include <utility> // pair
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const int MAXN = 101;
vector<vector<int>> g_graph;
bool g_visited[MAXN] = { false, };
int g_matched[MAXN] = { 0, };
int g_maxtime = -1;

bool dfs(int from)
{
	for (int to : g_graph[from]) {
		if (g_visited[to]) continue;
		else g_visited[to] = true;
		if (g_matched[to] == 0 || dfs(g_matched[to])) {
			g_matched[to] = from;
			if (to > g_maxtime) g_maxtime = to;
			return true;
		}
	}
	return false;
}

void doTest()
{
	int n, m;
	cin >> n >> m;
	g_graph.resize(n + 1);
	int t1, t2, a, b;
	bool connected[MAXN][MAXN];
	fill(&connected[0][0], &connected[MAXN - 1][MAXN], false);
	for (int i = 0; i < m; i++) { // 각 사람
		cin >> t1 >> t2; // 오픈 시간, 클로즈 시간
		cin >> a; // 조각수
		for (int j = 0; j < a; j++) {
			cin >> b; // 조각 입력						
			for (int k = t1 + 1; k <= t2; k++)
				connected[b][k] = true; // 여기서 바로 graph mapping하면 오름차순으로 시간 mapping하지 않아서 만족하는 최소 시간이 나오지 않는다.
		}
	}

	for (int i = 1; i < n + 1; i++) // 조각에 시간을 오름차순으로 mapping.
		for (int j = 0; j < MAXN; j++)
			if (connected[i][j]) g_graph[i].push_back(j); // '조각 <-> 시간' mapping(시간 오름차순)

	fill(g_matched, g_matched + MAXN, 0);
	g_maxtime = -1;
	int count = 0;
	for (int i = 1; i < n + 1; i++) {
		fill(g_visited, g_visited + MAXN, false);
		if (dfs(i)) count++;
	}
	cout << (count == n ? g_maxtime : -1) << "\n";
	g_graph.clear();
}

int main()
{
	FAST;
	int T;
	cin >> T;
	for (int i = 0; i < T; i++)
		doTest();
}