// 5398.cpp
// ICPC > Regionals > Europe > Northwestern European Regional Contest > Benelux Algorithm Programming Contest > BAPC 2010 J번
// 틀렸읍니다.
// 이것도 이분 매칭 문제이다. 또한 minimum vertex cover 개념을 파악하는 문제이기도 하다.
// 가로 단어와 세로 단어의 겹치는 위치에 문자가 다를 경우 충돌이 발생하고 충돌 위치의 좌표의 인덱스로 이분 그래프를 만든다.
// 만들어진 이분 그래프로 이분 매칭을 하고 이분 매칭의 수만큼 충돌을 야기하는 단어이므로 전체 단어 수에서 이 단어수만 빼면
// 정답이 된다.
// 이 때 이분 매칭의 결과가 minimum vertex cover가 된다.(매칭된 간선만큼의 단어로 모든 충돌의 경우의 수를 만들어 낼 수 있다)
// 실수한 점)
// 가로 단어의 y좌표가 같고 x 좌표가 다를 경우 서로 다른 단어로 처리해야 하는데 이를 같은 한 단어로 처리해서 틀렸다!!!
// (세로 단어의 경우도 마찬가지로 잘 못 하였다.) 서로 다른 단어를 같은 단어로 묶어버리면 이분매칭 결과 자체가 다르게 나온다!!!
// 단어의 시작 좌표를 자체를 가지고 이분 그래프를 만들면 이런 실수를 하게 되고, 단어마다 모두 서로 다르게 index값을 두어서,
// 이 가로단어의 index값, 세로단어의 index값으로 이분 매칭을 실시해야 한다.
// 제한시간 1초 중 120ms(22,116KB)가 소요되었다.
// 맞은사람 46/113로 상위 40.70%에 rank되었다.

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
#include <algorithm> // sort, max, min, copy, swap, unique, fill
//#include <climits> // INT_MAX, LLONG_MIN
#include <string> // string, stoi
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
char g_tbl[2001][2001];
int g_index[2001][2001];

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

void doTest()
{
	int H, V;
	cin >> H >> V;
	int range = max(H, V);
	fill(&g_tbl[0][0], &g_tbl[2000][2001], 0);
	fill(&g_index[0][0], &g_index[2000][2001], 0);
	int x, y;
	string str;
	for (int i = 1; i < H + 1; i++) { // 가로 word 입력
		cin >> x >> y;
		cin >> str;
		for (int j = 0; j < str.length(); j++) {
			g_tbl[y][x + j] = str[j];
			g_index[y][x + j] = i;
		}
	}
	g_graph.resize(range + 1);
	for (int i = 1; i < V + 1; i++) { // 세로 word 입력
		cin >> x >> y;
		cin >> str;
		for (int j = 0; j < str.length(); j++) {
			if (!g_tbl[y + j][x]) g_tbl[y + j][x] = str[j];
			else { // 충돌 발생!
				if (g_tbl[y + j][x] != str[j]) g_graph[g_index[y + j][x]].push_back(i);
			}
		}
	}
	int count = 0;
	g_matched.assign(range + 1, -1);
	for (int i = 0; i < range + 1; i++) {
		g_visited.assign(range + 1, false);
		if (dfs(i)) count++;
	}
	cout << (H + V) - count << "\n"; // Minumum Vertex Cover
	g_graph.clear();
}

int main()
{
	FAST;
	int T;
	cin >> T;
	while (T--) doTest();
}