// 3176.cpp
// 도로 네트워크
// LCA 구하는 과정에서 parent[x][i] 값에 해당 경로 중에서 min, max값을
// 같이 저장한다.
// 그러면 이후 LCA 구할 때 두 정점에서 LCA까지의 경로의 min, max값만 구하면 된다.
// 함 해보자!!!
// Olympiad > Croatian Highschool Competitions in Informatics > 2006 > Final Exam #2 2번
// 제한시간 1초 중 580ms(37,992KB)가 소요되었다.
// 맞은사람 896/1153로 상위 77.71%에 rank되었다.
// 도시의 최대 갯수(N)이 100,000이라 2^i에서 i의 최대값이 20이나 줄 필요는 없다. 17이 적당하다.(2^17=131,072)
// 17로 할 경우,
// 제한시간 1초 중 296ms(33,240KB)가 소요되었다.
// 맞은사람 808/1153로 상위 70.07%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs
#include <vector>
#include <algorithm> // sort, max, min, copy
//#include <climits> // INT_MAX
//#include <string> // string, stoi
//#include <utility> // pair, swap
//#include <stack>
//#include <set>
//#include <queue> // queue, priority_queue
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct city {
	int id;
	int min_;
	int max_;
	city() : id(0), min_(1000001), max_(0) {}
	city(int id, int mn, int mx) : id(id), min_(mn), max_(mx) {}
	~city() {}
};

int g_N;
vector<vector<city>> g_graph; // 양방향 그래프
vector<bool> g_visited; // 방문 여부 check
vector<int> g_depth; // 각 노드별 깊이 level
vector<vector<city>> g_parent; // 각 노드별 2^20까지의 parent 정보
const int g_max_level = 17; // 20;

void lca_dfs(int current, int level)
{
	g_depth[current] = level;
	g_visited[current] = true;
	for (const city& next : g_graph[current]) {
		if (g_visited[next.id]) continue;		
		g_parent[next.id][0].id = current;
		g_parent[next.id][0].min_ = next.min_;
		g_parent[next.id][0].max_ = next.max_;			   
		lca_dfs(next.id, level + 1);
	}
}

void find_parent()
{
	for (int i = 1; i <= g_max_level; i++) {
		for (int j = 1; j <= g_N; j++) {			
			g_parent[j][i].id = g_parent[g_parent[j][i - 1].id][i - 1].id;
			g_parent[j][i].min_ = min(g_parent[j][i - 1].min_, g_parent[g_parent[j][i - 1].id][i - 1].min_);
			g_parent[j][i].max_ = max(g_parent[j][i - 1].max_, g_parent[g_parent[j][i - 1].id][i - 1].max_);
		}
	}
}

const city lca(int x, int y)
{
	city result;
	int minval = 1000001, maxval = 0;

	if (g_depth[x] > g_depth[y])
		swap(x, y);
	// adjust the y depth level to x
	for (int i = g_max_level; i >= 0; i--) {
		if (g_depth[y] - g_depth[x] >= (1 << i)) {			
			minval = min(minval, g_parent[y][i].min_);
			maxval = max(maxval, g_parent[y][i].max_);
			y = g_parent[y][i].id;
		}
	}

	if (y == x) { // y의 조상이 x일 경우
		result = city(y, minval, maxval);		
		return result; 
	}

	// find the lca (x, y의 2^i번째 조상이 다르면 그 위치로 올린다, LCA까지 올린다)
	for (int i = g_max_level; i >= 0; i--) {
		if (g_parent[x][i].id != g_parent[y][i].id) {
			minval = min(minval, g_parent[x][i].min_);
			maxval = max(maxval, g_parent[x][i].max_);
			x = g_parent[x][i].id;			
			minval = min(minval, g_parent[y][i].min_);
			maxval = max(maxval, g_parent[y][i].max_);
			y = g_parent[y][i].id;
		}
	}

	minval = min(minval, g_parent[x][0].min_);
	maxval = max(maxval, g_parent[x][0].max_);
	minval = min(minval, g_parent[y][0].min_);
	maxval = max(maxval, g_parent[y][0].max_);

	return city(g_parent[x][0].id, minval, maxval);
}

int main()
{
	FAST;

	int a, b, c, k, d, e;	
	cin >> g_N;
	g_graph.resize(g_N + 1);
	g_visited.resize(g_N + 1, false);
	g_depth.resize(g_N + 1, 0);
	g_parent.resize(g_N + 1, vector<city>(g_max_level + 1, city()));
	for (int i = 0; i < g_N - 1; i++) {
		cin >> a >> b >> c;
		g_graph[a].push_back(city(b, c, c));
		g_graph[b].push_back(city(a, c, c));
	}
	lca_dfs(1, 0); // 1을 root로 잡는다.
	find_parent();
	
	cin >> k;
	city answer;
	for (int i = 0; i < k; i++) {
		cin >> d >> e;
		answer = lca(d, e);
		cout << answer.min_ << " " << answer.max_ << "\n";
	}
}