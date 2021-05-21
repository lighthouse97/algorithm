// 11377.cpp
// 열혈강호 3
// '11376 열혈강호 2'와 유사한 문제이나 약간 다르다. 전체가 아니라 K개의 인원만 2가지의 일을 할 수 있다.
// 11376과 유사하게 풀 되, 2개의 일이 가능한 인원이 생길때마다 count해서 이 count값이 K개가 되면 나머지 인원은 더 이상
// 2가지 일을 시키지 않는다.
// 이렇게 하면 최대 매칭이 안될 경우가 생긴다. 좀 더 나중에 K를 맞추는 것이 최대 매칭값이 나올 경우가 생기기 때문이다.
// 따라서 일단 1번씩 다 매칭을 하고 다음에 1번씩 더 매칭하면서 K를 카운트하는 방법으로 최대 매칭값을 찾아야 한다.
// 그리고 수행 시간에 관한 건인데,(뭐 중요하다면 중요할 수도 있다!)
// 11375의 dfs함수 수정 버전이 이 문제에서는 오히려 시간이 더 많이 걸린다. 그래서 dfs 수정 버전은 특정 경우에만 빠른 케이스로 판단이 되어,
// 이 문제 및 앞으로는 원래 dfs 함수를 사용하기로 한다.
// 그리고 recursive 호출이 많아서 그런지 vector로 배열을 사용하면 오히려 시간이 1초 정도 더 많이 소요되었다.
// 그래서 g_visited와 g_matched 배열은 그냥 일반적인 일차원 배열로 사용하였다. 이렇게 2가지를 수정하니, 수행시간이
// 1,756ms(4,152KB) --> 396ms(4,148KB)로 대폭 줄어들었다.
// 제한시간 3초 중 396ms(4,148KB)가 소요되었다.
// 맞은사람 312/1218로 상위 25.61%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
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

const int MAXN = 1001;
vector<vector<int>> g_graph;
bool g_visited[MAXN] = { false, };
int g_matched[MAXN] = { 0, };

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
	int N, M, K;
	cin >> N >> M >> K;
	g_graph.resize(N + 1);

	int c, w;
	for (int i = 1; i < N + 1; i++) {
		cin >> c;
		for (int j = 0; j < c; j++) {
			cin >> w;
			g_graph[i].push_back(w);
		}
	}

	int cnt = 0, answer = 0;
	for (int i = 1; i < N + 1; i++) {
		memset(g_visited, false, sizeof(g_visited));
		if (dfs(i)) answer++;
	}
	for (int i = 1; i < N + 1; i++) { // 한번 더 매칭
		memset(g_visited, false, sizeof(g_visited));
		if (dfs(i)) {
			cnt++;
			answer++;
		}
		if (cnt == K) break;
	}
	cout << answer << "\n";
}