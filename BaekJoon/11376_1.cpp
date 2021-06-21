// 11376_1.cpp
// 열혈강호 2
// 이분 매칭 문제인데, Hopcroft-Karp 알고리즘으로 풀어보았다.
// 수행시간은 확실히 개선이 되었다.
// N의 갯수가 대략 1000 이상으로 클수록 Hopcroft-Karp 알고리즘이 큰 효과를 발한다.
// 1,348ms(6,096KB) -> 84ms(6,128KB) 로 무려 16배 이상 개선되었다.
// 제한시간 4초 중 84ms(6,128KB)가 소요되었다.
// 맞은사람 6/1494로 상위 0.40%에 rank되었다.

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
#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_graph;
vector<int> g_A, g_B;
vector<int> g_levA;
int g_N;

void bfs()
{
	queue<int> myq;
	for (int i = 1; i < g_N + 1; i++) {
		if (g_A[i] == -1) { // matching안된 A정점부터 시작
			g_levA[i] = 0; // matching안된 A정점은 level 0이다.
			myq.push(i);
		}
		else g_levA[i] = -1; // matching 된 A 정점(), 후에 update위해 -1로 표시
	}
	while (!myq.empty()) { // matching된 정점의 level update
		int cur = myq.front(); myq.pop();
		for (int b : g_graph[cur]) {
			if (g_B[b] != -1 && g_levA[g_B[b]] == -1) {
				g_levA[g_B[b]] = g_levA[cur] + 1;
				myq.push(g_B[b]);
			}
		}
	}
}

bool dfs(int cur)
{
	for (int b : g_graph[cur]) {
		if (g_B[b] == -1 || (g_levA[g_B[b]] == g_levA[cur] + 1 && dfs(g_B[b]))) {
			g_A[cur] = b;
			g_B[b] = cur;
			return true;
		}
	}
	return false;
}

int hopcroft_karp()
{
	int maxMatch = 0; // 전체 매칭 수
	while (true) {
		bfs(); // A 집합에 level 생성
		int match = 0; // 현 level에서의 매칭 수
		for (int i = 1; i < g_N + 1; i++)
			if (g_A[i] == -1 && dfs(i)) match++; // A에서 match가 안된 정점에서 dfs 탐색
		if (match == 0) break; // dfs에서 match가 실패하면 더 탐색할 필요 없으므로 알고리즘 종료
		maxMatch += match;
	}
	return maxMatch;
}

int main()
{
	FAST;
	int n, m;
	cin >> n >> m;
	g_N = n;
	g_graph.resize(g_N + 1);
	g_A.resize(m + 1, -1);
	g_B.resize(m + 1, -1);
	g_levA.resize(g_N + 1, -1);
	int cnt, jn;
	for (int i = 1; i < g_N + 1; i++) {
		cin >> cnt;
		for (int j = 0; j < cnt; j++) {
			cin >> jn;
			g_graph[i].push_back(jn);
		}
	}
	int maxMatch = 0;
	maxMatch = hopcroft_karp();
	g_A.assign(g_N + 1, -1); // reset A set
	maxMatch += hopcroft_karp(); // A[]만 초기화 하고 한번 더 돌림.
	cout << maxMatch << "\n";
}