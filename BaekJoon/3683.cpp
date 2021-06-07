// 3683.cpp
// 고양이와 개
// ICPC > Regionals > Europe > Northwestern European Regional Contest > NWERC 2008 C번
// 내개는 아주 어려운 문제였다. 어떻게 푸는지 감조차 잡지 못했다. 결국 남의 풀이를 자세히 읽어보았다.
// 그래서 이 문제는 내가 푼 것이 아니다!
// 문제를 잘 읽어보고 예제를 잘 살펴보면 투표하는 사람 중에서 충돌이 발생하는 경우가 생긴다.
// 예를 들어 사람1이 C1을 선택했는데 사람2가 C1을 떨어뜨리는 경우이다.
// 또 사람1이 D1을 떨어뜨리는데 사람3이 D1을 선택하는 경우도 있다.
// 이렇게 충돌이 발생하는 사람들끼리 이분 그래프로 연결해 준다.
// 이 때 이분 그래프의 왼쪽은 고양이를 좋아하는 사람, 오른쪽은 개를 좋아하는 사람으로 분류한다.
// 고양이를 좋아하는 사람들까리 충돌이 발생할 리가 없고, 개를 좋아하는 사람들까리 충돌이 발생할리가 없기 때문에
// 이렇게 이분 그래프를 구성할 수가 있다.
// 다음에 이분 매칭을 통해 최대 매칭을 구한다.
// 이 때 최대 매칭의 값(갯수)만큼의 사람이 충돌을 일으키는 모든 경우를 포함하므로 전체 사람수에서 빼주면
// 투표가 반영되는 사람들의 최대값이 된다.
// 이 때  최대 매칭의 값(갯수)만큼의 사람 수가 Minimum Vertex Cover가 된다.
// 왜냐하면 Minimum Vertex Cover에 속하는 정점(사람)이 모든 간선(충돌을 일으키는 연결)에 연결되기 때문이다.
// 제한시간 1초 중 28ms(2,276KB)가 소요되었다.
// 맞은사람 93/144로 상위 64.58%에 rank되었다.

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
//#include <algorithm> // sort, max, min, copy, swap, unique, fill
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

void doTest()
{
	int c, d, v;
	cin >> c >> d >> v;
	g_graph.resize(v + 1);
	vector<vector<string>> vote(v + 1, vector<string>(2));
	for (int i = 1; i < v + 1; i++)
		cin >> vote[i][0] >> vote[i][1]; // 투표 입력

	for (int i = 1; i < v; i++) { // 이분 그래프 생성
		for (int j = i + 1; j < v + 1; j++) {
			if (!vote[i][0].compare(vote[j][1]) || !vote[i][1].compare(vote[j][0])) { // 충돌발생
				if (vote[i][0].at(0) == 'C') g_graph[i].push_back(j); // 이분 그래프 왼쪽은 고양이 선택, 오른쪽은 개 선택으로 묶는다.
				else g_graph[j].push_back(i);
			}
		}
	}
	int count = 0;
	g_matched.assign(v + 1, 0); // 이분 탐색
	for (int i = 1; i < v + 1; i++) {
		g_visited.assign(v + 1, false);
		if (dfs(i)) count++;
	}
	cout << (v - count) << "\n";
	g_graph.clear();
}

int main() {
	int T;
	cin >> T;
	while (T--) doTest();
}