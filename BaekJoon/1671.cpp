// 1671.cpp
// 상어의 저녁 식사
// 이 문제는 '이분 매칭이 아닌 것 같지만 이분 매칭이 되는 문제'라고 힌트를 주었다.
// 그렇다! 이 문제는 엄밀히 이분 매칭의 이분 그래프 형태는 아니다.
// 그러나 이분 매칭의 방법을 사용해서 풀 수 있는 문제이다!
// 1번 상어의 크기, 지능, 속도 모두가 2번 상어의 크기, 지능, 속도보다 같거나 크다면
// 1번 상어는 2번 상어를 잡아 먹을 수 있고 이를 1 -> 2로 표현한다.
// 이런 방식으로 그래프를 만들어 이분 매칭을 하는데 같은 상어가 최대 2마리까지 잡아먹을 수 있으므로
// 이분 매칭을 두 번 돌린다.
// 이분 매칭이 가능한 카운트의 갯수가 잡아먹는 횟수이므로 전체 상어 개체수에서 이 값을 빼면
// 살아남는 상어의 수가 나온다.
// 단, 두 상어의 크기, 지능, 속도가 모두 같을 경우 두 상어가 서로 잡아 먹어 문제의 조건에 위배 되므로
// 이 때에는 두 상어중에서 인덱스가 작은 혹은 큰 상어만 잡아먹을 수 있도록 조건을 더 붙이면 된다.
// 그럼 함 풀어보자!!!
// 상어끼리 먹히기 전에 비교 조건을 잘 따져봐야 하는데 이거 때문에 2번이나 틀렸다!!!
// 제한시간 2초 중 0ms(2,120KB)가 소요되었다.
// 맞은사람 541/902로 상위 59.97%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs, hypot, round
#include <vector>
//#include <algorithm> // sort, max, min
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct ability {
	int size;
	int speed;
	int intelligence;	
	bool operator >= (const ability& rhs) const
	{
		return (size >= rhs.size && speed >= rhs.speed && intelligence >= rhs.intelligence);
	}
	bool operator <= (const ability& rhs) const
	{
		return (size <= rhs.size && speed <= rhs.speed && intelligence <= rhs.intelligence);
	}
	bool operator == (const ability& rhs) const
	{
		return (size == rhs.size && speed == rhs.speed && intelligence == rhs.intelligence);
	}
};

vector<vector<int>> g_graph;
vector<bool> g_visited;
vector<int> g_matched;
vector<ability> g_shark;

bool dfs(int from)
{	
	for (int to : g_graph[from]) {
		if (!g_visited[to] && !g_matched[to]) {
			g_visited[to] = true;
			g_matched[to] = from;
			return true;
		}
	}
	for (int to : g_graph[from]) {
		if (!g_visited[to]) {
			g_visited[to] = true;
			if (!g_matched[to] || dfs(g_matched[to])) {
				g_matched[to] = from;
				return true;
			}
		}
	}
	return false;
}

int main()
{
	FAST;

	int n, result = 0;
	cin >> n;
	g_shark.resize(n + 1, { 0, 0, 0 });
	g_graph.resize(n + 1);
	g_visited.resize(n + 1, false);
	g_matched.resize(n + 1, 0);

	int sz, spd, intel;
	for (int i = 1; i < n + 1; i++) {
		cin >> sz >> spd >> intel;
		g_shark[i] = { sz, spd, intel };
	}
	for (int i = 1; i < n + 1; i++) {
		for (int j = i; j < n + 1; j++) {
			// 아래 비교 조건을 잘 따져봐야 한다.
			if (!(i < j)) continue;
			if(g_shark[i] == g_shark[j])
				g_graph[i].push_back(j);
			else if (g_shark[i] >= g_shark[j])
				g_graph[i].push_back(j);
			else if (g_shark[i] <= g_shark[j])
				g_graph[j].push_back(i);
		}
	}
	// 이분 매칭
	for (int h = 0; h < 2; h++) {
		for (int i = 1; i < n + 1; i++) {
			g_visited = vector<bool>(n + 1, false);
			if (dfs(i)) result++;			
		}		
	}
	cout << (n - result) << "\n";
}