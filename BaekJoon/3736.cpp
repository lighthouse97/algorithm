// 3736.cpp
// System Engineer
// ICPC > Regionals > Europe > Southeastern European Regional Contest > SEERC 2009 C번
// 이것도 이분 매칭 문제이다. 문제가 영어라서 해석에 시간이 좀 걸렸는데 결국은 단순한 이분 매칭 문제일 뿐이다.
// 단 입력처리할 때 formatted 문 형식으로 입력을 받아야 해서, cin보다 scanf를 사용하였다.
// scanf입력에서 특정 조건이 아닌 EOF가 입력될 때까지 입력을 받으므로, 이 부분에 대한 구현도 중요하다.
// Visual Studio에서는 scanf_s를 권장하고 scanf는 컴파일시 warning을 유발하므로 미리 프로젝트 설정의 전처리기에서 "_CRT_SECURE_NO_WARNINGS"를 선언해 둔다.
// 입력 데이터가 10,000개까지 주어지기 때문에 일반적인 이분 매칭으로 풀면 시간이 많이 매우 걸리고 구현 방식에 따라 TLE가 나올 수도 있다.
// 이 문제와 같이 입력 데이터가 아주 많을 경우는, Hopcroft-Karp 알고리즘을 사용해서 풀어야 한다. 
// 제한시간 1초 중 604ms(3,228KB)가 소요되었다.
// 맞은사람 109/117로 상위 93.16%에 rank되었다.

#include "pch.h"
#include <cstdio> // NULL, printf, scanf
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil, hypot
#include <vector>
//#include <list>
//#include <algorithm> // sort, max, min, copy, swap, unique, fill
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
		if (g_matched[to] == -1 || dfs(g_matched[to])) {
			g_matched[to] = from;
			return true;
		}
	}
	return false;
}

int main()
{
	FAST;
	int n;
	while (scanf("%d", &n) != EOF) {
		g_graph.assign(n, vector<int>(0));
		g_matched.assign(2 * n, -1);
		int j, scnt, s;
		for (int i = 0; i < n; i++) {
			scanf("%d: (%d)", &j, &scnt);
			for (int k = 0; k < scnt; k++) {
				scanf("%d", &s);
				g_graph[j].push_back(s);
			}
		}
		int count = 0;
		for (int i = 0; i < n; i++) {
			g_visited.assign(2 * n, false);
			if (dfs(i)) count++;
		}
		cout << count << "\n";
	}
}