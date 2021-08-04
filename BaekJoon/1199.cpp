// 1199.cpp
// 오일러 회로(Euler Circuit)
// 오일로 회로의 경로를 구하는 문제이다.
// 오일러 회로 탐색할 때 현재 정점에서 다음번 탐색할 간선의 정보를 저장하지 않으면,
// TLE가 발생한다.
// 이 점 주의해야 한다!!!
// 제한시간 3초 중 724ms(367,324KB)가 소요되었다.
// 맞은사람 19/130로 상위 14.61%에 rank되었다.

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
//#include <queue> // queue, priority_queue
//#include <deque>
//#include <functional> // greater
//#include <map>
//#include <unordered_map> // unordered_map
#define FAST ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector<vector<int>> g_graph;
vector<int> g_record; // 다음 시작 간선 정보 저장
///
vector<int> g_ecpath; // euler circuit path

void eulerc(int curr) // 오일러 회로 탐색
{
	for (int& i = g_record[curr]; i < (int)g_graph[curr].size(); i++) { // TLE로 인해 다음 시작 간선정보 미리 저장
		int& cnt = g_graph[curr][i];
		if (cnt > 0) {
			cnt--;
			g_graph[i][curr]--;
			eulerc(i);
		}
	}
	g_ecpath.push_back(curr); // 경로 저장
}

int main()
{
	FAST;
	int N;
	cin >> N;
	g_graph.resize(N + 1, vector<int>(N + 1, 0));
	g_record.resize(N + 1, 1);
	int degree = 0;
	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < N + 1; j++) {
			cin >> g_graph[i][j];
			degree += g_graph[i][j];
		}
		if (degree % 2) { // 정점의 차수가 짝수이어야 함
			cout << -1 << "\n";
			return 0;
		}
		degree = 0;
	}
	eulerc(1);
	for (int x : g_ecpath) cout << x << " ";
	cout << "\n";
}