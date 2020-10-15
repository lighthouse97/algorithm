// 11014.cpp
// 컨닝 2
// "이분 그래프에서 최대 매칭 + 최대 독립 집합 = 정점 개수" 정리를 사용하여 푸는 문제
// 라고 한다.
// 구하는 방법은 다음과 같다.
// 1) 전체 좌석의 배열을 만든다(각 좌석에는 row, column, exist의 정보가 들어간다)
// 2) 전체 좌석에서 존재하는 좌석(.표시) 중 짝수열(혹은 홀수열)만을 이분 그래프의 left 배열에 넣는다.
//    (홀수열끼리 혹은 짝수열끼리는 절대로 커닝을 할 수 없기 때문이다)
// 3) left 배열의 각 원소에서 6방향으로 커닝 여부를 체크하여 커닝이 가능한 자리를 그래프의 해당 인덱스에 추가한다.
// 4) 이분 그래프가 완성되면 그래프 전체에 대해서 이분 그래프의 최대 매칭(dfs)를 돌린다.
// 5) 여기서 나온 카운트값이 최대로 컨닝할 수 있는 최소의 인원수이고 즉 최소 버텍스 커버의 수가 된다.
// 6) 전체 학생 수에서 앉을 수 없는 자리를 제외하고 나머지 자리에서 5)의 카운트를 빼면 커닝을 할 수 없는 최대한의 학생수가 구해진다.
//    즉 이 수는 쾨닉의 정리에서 최대 독립 집합의 수가 된다.
// 어떻게든 방법을 만들어 이분 그래프를 만든다. 최대 매칭이 최소로 전체 컨닝할 수 있는 자리이므로
// 이 자리를 뺀 나머지가 최대 독립 집합이고 이 최대 독립 집합의 갯수를 구하면 된다.
// Contest > Google Code Jam > Google Code Jam 2008 > Round 3 C2번
// 제한시간 2초 중 16ms(2,504KB)가 소요되었다.
// 맞은사람 25/275로 상위 9.09%에 rank되었다.

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

struct info {
	int row, col;
	bool exist;
};

vector<vector<int>> g_graph;
vector<bool> g_visited;
vector<int> g_matched;
int g_n, g_m;
vector<info> g_seat;

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

int canCunning(int row, int col)
{
	if (row < 1 || row > g_n || col < 1 || col > g_m) return -1;
	int loc = (row - 1) * g_m + col;
	return g_seat[loc].exist ? loc : -1;	
}

void do_test()
{	
	int n, m, count = 0, no_seat = 0;	

	cin >> g_n >> g_m;
	n = g_n; m = g_m;
	
	g_seat.resize(n * m + 1, { 0, 0, 0 }); // row에서 col증가 방향으로 1 ~ n*m 번호 매긴다.
	char s;	
	// 좌석 정보 입력
	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < m + 1; j++) {
			cin >> s;			
			g_seat[(i - 1)*m + j] = { i, j, (s == '.' ? true : false) };
		}
	}
	vector<int> left;
	// 좌석이 있고 짝수열이면 left에 넣는다.
	for (int i = 1; i < n * m + 1; i++) {
		if (g_seat[i].exist) {
			if (!(g_seat[i].col % 2)) left.push_back(i);			
		}
		else no_seat++;
	}
	left.insert(left.begin(), 0); // index 1 부터 시작	
	g_graph.resize(n * m + 1);
	g_visited.resize(n * m + 1, false);
	g_matched.resize(n * m + 1, 0);
	// 각 자리마다 인접 좌석의 커닝 여부를 체크하여 이분 그래프 연결
	int cn;
	for (int i = 1; i < (int)left.size(); i++) { // left 각각의 원소에서 6개의 방향으로 cunning 여부 체크		
		cn = canCunning(g_seat[left[i]].row - 1, g_seat[left[i]].col - 1); // 왼쪽 위
		if (cn > 0) g_graph[left[i]].push_back(cn);
		cn = canCunning(g_seat[left[i]].row, g_seat[left[i]].col - 1); // 왼쪽
		if (cn > 0) g_graph[left[i]].push_back(cn);
		cn = canCunning(g_seat[left[i]].row - 1, g_seat[left[i]].col + 1); // 오른쪽 위
		if (cn > 0) g_graph[left[i]].push_back(cn);
		cn = canCunning(g_seat[left[i]].row, g_seat[left[i]].col + 1); // 오른쪽
		if (cn > 0) g_graph[left[i]].push_back(cn);
		cn = canCunning(g_seat[left[i]].row + 1, g_seat[left[i]].col + 1); // 오른쪽 아래
		if (cn > 0) g_graph[left[i]].push_back(cn);
		cn = canCunning(g_seat[left[i]].row + 1, g_seat[left[i]].col - 1); // 왼쪽 아래
		if (cn > 0) g_graph[left[i]].push_back(cn);
	}
	// 이분 매칭
	for (int i = 1; i < (int)g_graph.size(); i++) {
		g_visited = vector<bool>(g_visited.size(), false);
		if (dfs(i)) count++;
	}
	// "전체 학생 수에서 - 앉을 수 없는 자리 - 이분 매칭의 수"가 (최대 독립 집합)으로 컨닝할 수 없는 최대 학생 수이다.
	cout << (n * m - no_seat - count) << "\n";
	// clear all the global vector
	g_graph.clear();
	g_visited.clear();
	g_matched.clear();
	g_seat.clear();
	g_n = g_m = 0;
}

int main()
{
	FAST;

	int c;
	cin >> c;
	for (int i = 0; i < c; i++) {
		do_test();
	}
}