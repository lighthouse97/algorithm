// 2056.cpp
// 작업
// 공교롭게도 이 문제는 '1516 게임 개발'과 동일한 문제이다!
// 입력에 약간 차이가 있지만 거의 차이가 없는 거나 마찬가지이고,
// 출력은 정점 N의 시간으로 출력하면 된다.
// 자, 그럼 1516에서 푼 것을 거의 대부분 활용하여 문제를 함 풀어보자!!!
// 실수했던 점 -->
// 1) 작업의 마지막 정점이 한개가 아니라 여러 개 있을 수 있다.
// 2) 이들 마지막 정점의 누적 시간을 합하면 WA이고, 이들 중 가장 큰 값을 찾아야 한다!!!
// 제한시간 2초 중 84ms(5,984KB)가 소요되었다.
// 맞은사람 546/2321로 상위 23.52%에 rank되었다.
// 아주 약간 개선하여 80ms(5,984KB), 505/2321로 21.75% rank되었다.


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
#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_graph;
vector<int> g_degree;
int g_N = 0;
///
vector<int> g_time;
vector<int> g_answer;

void topological_sort()
{
	queue<int> myq;
	for (int i = 1; i < g_N + 1; i++)
		if (g_degree[i] == 0) { myq.push(i); g_answer[i] = g_time[i]; }
	int cur;
	while (!myq.empty()) {
		cur = myq.front(); myq.pop();
		for (int to : g_graph[cur]) {
			g_degree[to]--;
			g_answer[to] = max(g_answer[to], g_answer[cur] + g_time[to]);
			if (g_degree[to] == 0)
				myq.push(to);
		}
	}
}

int main() {
	FAST;
	int N;
	cin >> N;
	g_graph.resize(N + 1);
	g_degree.resize(N + 1, 0);
	g_N = N;
	int t, nj, jo;
	g_time.resize(g_N + 1, 0);
	g_answer.resize(g_N + 1, 0);
	for (int i = 1; i < g_N + 1; i++) {
		cin >> t >> nj;
		g_time[i] = t;
		for (int j = 0; j < nj; j++) {
			cin >> jo;
			g_graph[jo].push_back(i);
			g_degree[i]++;
		}
	}
	topological_sort();
	int answer = 0;
	for (int i = 1; i < g_N + 1; i++)
		answer = max(answer, g_answer[i]);
	cout << answer << "\n";
}