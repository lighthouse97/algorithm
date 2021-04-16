// 11780.cpp
// 일반적인 Floyd-Warshall 문제와 동일한데, 최단 경로까지 모두 출력하는 부분이 추가가 되었다.
// Floyd-Warshall 돌릴 때, 자신이 자신으로 오는 경로는 없는 것으로 전제하므로 i == j 일 때는 처리조건에서 빼줘야 한다.
// city 생성자에서 default 생성자 그대로 copy & paste해서 오류 발생했다. 주의하자!!!
// 최단 경로 경로생성은 i -> k -> j 일때 최단경로 이면 i -> j 에 최단경로 시간에다 k 값까지 추가로 저장한다.
// 다음 i -> j 경로에 k가 들어가 있으면 k가 안나올 때까지 계속 recursive로 쪼개 나간다.(i -> k, k -> j) (이때 list의 iterator를 이용한다.)
// 이렇게 하면 i -> j 경로에 k들이 순서에 맞게 쌓여들어간다.
// 제한시간 1초 중 36ms(2,152KB)가 소요되었다.
// 맞은사람 262/866로 상위 30.25%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
#include <list>
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

struct city {
	int t, k; // time, k(path)
	city() : t(0), k(0) {}
	city(int t, int k) : t(t), k(k) {}
};

const int INF = 987654321;
int g_N;
vector<vector<city>> g_graph;

void floyd_warshall()
{
	for (int k = 1; k < g_N + 1; k++) {
		for (int i = 1; i < g_N + 1; i++) {
			for (int j = 1; j < g_N + 1; j++) {
				if (i != j && g_graph[i][k].t + g_graph[k][j].t < g_graph[i][j].t) {
					g_graph[i][j].t = g_graph[i][k].t + g_graph[k][j].t;
					g_graph[i][j].k = k; // 중간 경로 저장
				}
			}
		}
	}
}

void find_path(list<int>& p, list<int>::iterator s, list<int>::iterator e)
{
	list<int>::iterator it;
	if (g_graph[*s][*e].k) {
		it = p.insert(e, g_graph[*s][*e].k);
		find_path(p, s, it);
		find_path(p, it, e);
	}
}

int main()
{
	FAST;
	cin >> g_N;
	g_graph.resize(g_N + 1, vector<city>(g_N + 1, { INF, 0 }));
	int m;
	cin >> m;
	int s, e, t;
	for (int i = 0; i < m; i++) {
		cin >> s >> e >> t;
		g_graph[s][e].t = min(g_graph[s][e].t, t);
	}
	floyd_warshall();
	for (int i = 1; i < g_N + 1; i++) { // 최단 경로의 시간 출력
		for (int j = 1; j < g_N + 1; j++) {
			cout << (g_graph[i][j].t < INF ? g_graph[i][j].t : 0) << " ";
		}
		cout << "\n";
	}
	for (int i = 1; i < g_N + 1; i++) { // 각 최단 거리의 경로 출력
		for (int j = 1; j < g_N + 1; j++) {
			if (i == j) cout << 0 << "\n";
			else {
				list<int> myl = { i, j };
				list<int>::iterator s, e;
				s = myl.begin(); e = myl.end(); e--;
				find_path(myl, s, e);
				cout << myl.size() << " ";
				for (int x : myl) { cout << x << " "; }
				cout << "\n";
			}
		}
	}
}