// 1014.cpp
// 컨닝
// Contest > Google Code Jam > Google Code Jam 2008 > Round 3 C1번
// '11014 컨닝 2'와 동일한 문제이다. 단지 N 수만 더 적다.
// 따라서 이분 매칭 문제라 '11014 컨닝 2' 소스를 그대로 가져다 써도 풀리겠지만
// 이분 매칭 알고리즘으로 기존 알고리즘 대신 Hopcroft-Karp 알고리즘을 사용해서 풀어보겠다.
// 제한시간 2초 중 0ms(2,028KB)가 소요되었다.
// 맞은사람 333/1000로 상위 33.30%에 rank되었다.

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

struct info {
	int row, col;
	bool exist;
	info() : row(0), col(0), exist(false) {}
	info(int r, int c, bool e) : row(r), col(c), exist(e) {}
};

vector<vector<int>> g_graph;
vector<int> g_A, g_B;
vector<int> g_levA;
int g_N;
vector<info> g_seat;

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

int canCunning(int row, int col, int maxr, int maxc)
{
	int n = maxr, m = maxc;
	if (row < 1 || row > n || col < 1 || col > m) return -1;
	int loc = (row - 1) * m + col;
	return g_seat[loc].exist ? loc : -1;
}

void doTest()
{
	int n, m, count = 0, no_seat = 0;
	cin >> n >> m;
	g_N = n * m;
	g_graph.assign(g_N + 1, {});
	g_A.assign(g_N + 1, -1);
	g_B.assign(g_N + 1, -1);
	g_levA.assign(g_N + 1, -1);
	g_seat.resize(g_N + 1, { 0, 0, 0 });

	char s;
	for (int i = 1; i < n + 1; i++) { // 좌석 정보 입력
		for (int j = 1; j < m + 1; j++) {
			cin >> s;
			g_seat[(i - 1)*m + j] = { i, j, (s == '.' ? true : false) };
		}
	}
	vector<int> left;
	left.push_back(0); // 1부터 시작
	for (int i = 1; i < n * m + 1; i++) { // 전체 테이블에서 짝수열만 추출
		if (g_seat[i].exist) {
			if (!(g_seat[i].col % 2)) left.push_back(i);
		}
		else no_seat++;
	}
	int cn; // 각 자리마다 인접 좌석의 커닝 여부를 체크하여 이분 그래프 연결
	for (int i = 1; i < (int)left.size(); i++) { // left 각각의 원소에서 6개의 방향으로 cunning 여부 체크		
		cn = canCunning(g_seat[left[i]].row - 1, g_seat[left[i]].col - 1, n, m); // 왼쪽 위
		if (cn > 0) g_graph[left[i]].push_back(cn);
		cn = canCunning(g_seat[left[i]].row, g_seat[left[i]].col - 1, n, m); // 왼쪽
		if (cn > 0) g_graph[left[i]].push_back(cn);
		cn = canCunning(g_seat[left[i]].row - 1, g_seat[left[i]].col + 1, n, m); // 오른쪽 위
		if (cn > 0) g_graph[left[i]].push_back(cn);
		cn = canCunning(g_seat[left[i]].row, g_seat[left[i]].col + 1, n, m); // 오른쪽
		if (cn > 0) g_graph[left[i]].push_back(cn);
		cn = canCunning(g_seat[left[i]].row + 1, g_seat[left[i]].col + 1, n, m); // 오른쪽 아래
		if (cn > 0) g_graph[left[i]].push_back(cn);
		cn = canCunning(g_seat[left[i]].row + 1, g_seat[left[i]].col - 1, n, m); // 왼쪽 아래
		if (cn > 0) g_graph[left[i]].push_back(cn);
	}
	int maxMatch;
	maxMatch = hopcroft_karp(); // 이분 매칭
	cout << (g_N - no_seat - maxMatch) << "\n"; // 전체 자리 - 앉을 수 없는 자리 - 컨닝 할 수 있는 자리 = 최대 컨닝 할 수 없는 자리
}

int main()
{
	FAST;
	int c;
	cin >> c;
	for (int i = 0; i < c; i++) doTest();
}