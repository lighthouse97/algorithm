// 1507.cpp
// 궁금한 민호
// Floyd-Warshsll 응용문제이다.
// 이미 Floyd-Warshsll로 돌려진 결과를 한번 더 Floyd-Warshsll로 돌리면서 각 정점마다 거쳐온 간선의 갯수를 업데이트 한다.
// 어느 한 정점에서 정점까지 도달 시간이 같을 경우 간선이 더 긴 것을 우선으로 업데이트한다.
// 왜냐? 도로의 갯수가 최소가 되어야 하는 조건이 붙기 때문에, 1->3으로 갈 때 1->3의 시간과 1->2, 2->3의 시간이 같으면 1->3 도로는 필요없기 때문이다.
// 이를 위해 간선의 길이를 저장하는 테이블을 하나 더 만든다.
// 1) 도달 시간이 같으면 간선이 긴 것을 선택
// 2) 도달 시간이 더 긴 것은 최단 경로가 아니므로 통과
// 3) 도달 시간이 더 짧은 경로가 나오면 모든 도시간에 최소 이동 경로를 구해두었다는 문제의 조건에 위배 되므로, 불가능(-1) 출력!
// 경로의 수 테이블에서 경로의 수가 1인 모든 경로의 이동 시간의 합을 구하면 된다.
// 제한시간 2초 중 0ms(2,020KB)가 소요되었다.
// 맞은사람 1057/1599로 상위 66.10%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
//#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil
#include <vector>
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

vector<vector<int>> g_graph; // 최단 시간
vector<vector<int>> g_path; // 경로수
int g_N;
bool g_failure = false;

void floyd_warshall()
{
	for (int k = 1; k < g_N + 1; k++) {
		for (int i = 1; i < g_N + 1; i++) {
			for (int j = 1; j < g_N + 1; j++) {
				if (g_graph[i][k] + g_graph[k][j] == g_graph[i][j]) {
					if (g_path[i][k] + g_path[k][j] > g_path[i][j]) g_path[i][j] = g_path[i][k] + g_path[k][j];
				}
				else if (g_graph[i][k] + g_graph[k][j] < g_graph[i][j]) {
					g_failure = true;
					return;
				}
			}
		}
	}
}

int main()
{
	FAST;
	cin >> g_N;
	g_graph.resize(g_N + 1, vector<int>(g_N + 1, 0));
	g_path.resize(g_N + 1, vector<int>(g_N + 1, 1));
	for (int i = 1; i < g_N + 1; i++) {
		for (int j = 1; j < g_N + 1; j++) {
			cin >> g_graph[i][j];
			if (i == j) g_path[i][j] = 0;
		}
	}
	floyd_warshall();
	int sum = 0;
	if (g_failure) cout << -1 << "\n";
	else {
		for (int i = 1; i < g_N + 1; i++)
			for (int j = i + 1; j < g_N + 1; j++) // 중복제거, i+1부터 시작
				sum += (g_path[i][j] == 1 ? g_graph[i][j] : 0);
		cout << sum << "\n";
	}
}