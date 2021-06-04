// 14433.cpp
// 한조 대기 중
// High School > 선린인터넷고등학교 > 머그컵 F번
// 이것도 이분 매칭 문제이다. 이분 매칭의 결과가 2개가 나오는데, 각각의 최대 매칭 수를 비교해서 우리팀의 매칭 수가
// 상대팀의 매칭 수보다 작으면 승리, 같거나 크면 실패가 된다.
// 제한시간 2초 중 0ms(2,160KB)가 소요되었다.
// 맞은사람 122/188로 상위 64.89%에 rank되었다.

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
//#include <algorithm> // sort, max, min, copy, swap, unique
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

vector<vector<int>> g_graph;
vector<bool> g_visited;
vector<int> g_matched;

bool dfs(int from)
{
	for (int to : g_graph[from]) {
		if (g_visited[to]) continue;
		else g_visited[to] = true;
		if (g_matched[to] == 0 || dfs(g_matched[to])) {
			g_matched[to] = from;
			return true;
		}
	}
	return false;
}

int main()
{
	FAST;
	int N, M, K1, K2;
	cin >> N >> M >> K1 >> K2;
	g_graph.resize(N + 1);
	g_visited.resize(M + 1, false);
	g_matched.resize(M + 1, 0);

	int a, b;
	for (int i = 0; i < K1; i++) { // 우리편 트롤픽 연결
		cin >> a >> b;
		g_graph[a].push_back(b);
	}
	int cnt1 = 0;
	for (int i = 1; i < N + 1; i++) { // 우리편 트롤픽 최대 매칭
		g_visited.assign(M + 1, false);
		if (dfs(i)) cnt1++;
	}

	g_graph.assign(N + 1, vector<int>(0));
	g_matched.assign(M + 1, false);
	for (int i = 0; i < K2; i++) { // 상대편 트롤픽 연결
		cin >> a >> b;
		g_graph[a].push_back(b);
	}
	int cnt2 = 0;
	for (int i = 1; i < N + 1; i++) { // 상대편 트롤픽 최대 매칭
		g_visited.assign(M + 1, false);
		if (dfs(i)) cnt2++;
	}

	cout << (cnt1 < cnt2 ? "네 다음 힐딱이" : "그만 알아보자") << "\n";
}