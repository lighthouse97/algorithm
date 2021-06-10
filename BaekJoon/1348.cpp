// 1348.cpp
// 주차장
// 이분 매칭인데 사전 작업이 많아서 어려운 문제에 속한다.
// <이분 매칭에 파라미터(거리제한) 추가된점>, <이분 매칭을 여러번 하는 점>, <거리를 BFS로 탐색해서 구한다는 점>.
// 1) 차의 좌표와 주차구역의 좌표 저장(각각의 좌표는 id를 가진다.)
// 2) 차의 좌표 하나하나에 대해 주차구역 좌표까지의 거리를 BFS로 구한다.
// 3) 2)의 거리를 차/주차구역 각각 id에 맞게 2차원 배열로 저장한다.
// 4) 차/주차구역 각각 id로 이분 그래프를 구성한다.
// 5) 2)에서 가장 긴 거리와 거리 0에 대해 이분 탐색을 실시하여 각각의 mid값에 대해서 이분매칭을 한다.
//    (이분 매칭시 연결 뿐만 아니라 거리제한도 고려되어야 한다.) 이 때 이분매칭의 결과에 따라 mid값이 조절된다.
// 6) 최종 mid값에 대해 이분 매칭을 한번 더 하여 car의 개수가 맞으면 그 값을 출력하고 끝이다.
//    (마지막에 한번 더 하는 것은 이분 탐색 끝까지 차의 갯수만큼 매칭 결과가 안나올 수도 있기 때문이다.)
// 7) 6)에서 차의 갯수만큼 안나오면 -1을 리턴하고 끝이다.
// 8) 차의 갯수가 없는 경우로 입력이 들어오면 입력 단계에서 0을 리턴하고 끝낸다.
// 제한시간 1초 중 8ms(2,216KB)가 소요되었다.
// 맞은사람 144/354로 상위 40.67%에 rank되었다.

#include "pch.h"
//#include <cstdio> // NULL
//#include <cstdlib> // abs
#include <iostream>
//#include <memory> // shared_ptr<>
//#include <iomanip>
#include <cstring> // memset
//#include <cmath> // pow, sqrt, fabs. ceil, hypot
#include <vector>
//#include <list>
#include <algorithm> // sort, max, min, copy, swap, unique
//#include <climits> // INT_MAX, LLONG_MIN
#include <string> // string, stoi
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

struct loc {
	int r, c, t; // row, column, time
	loc() : r(0), c(0), t(0) {}
	loc(int r, int c) : r(r), c(c), t(0) {}
	loc(int r, int c, int t) : r(r), c(c), t(t) {}
};

const int MAXCAR = 101;
const int MAXPARK = 101;
const int MAXNUM = 2501;
vector<vector<int>> g_graph;
bool g_visited[MAXPARK] = { false, };
int g_matched[MAXPARK] = { 0, };

int g_R = 0, g_C = 0; // 주차장 R, C값 입력
int g_carcnt = 0, g_parkcnt = 0, g_maxtime = 0; // 차의 갯수, 주차구역의 갯수, 가장 긴 주차 시간
char g_parking[51][51] = { {0, } }; // 주자창 입력
loc g_car[MAXCAR] = { {0, 0}, }; // 차 id에 좌표 저장
int g_park[MAXNUM] = { 0, }; // 주차구역 좌표((r-1)*C + c)에 주차구역 id 저장
int g_time[MAXCAR][MAXPARK] = { {0, } }; // '차id * 주차구역id'의 거리 저장

bool dfs_with_p(int from, int p)
{
	for (int to : g_graph[from]) {
		if (g_time[from][to] > p || g_visited[to]) continue;
		else g_visited[to] = true;
		if (g_matched[to] == 0 || dfs_with_p(g_matched[to], p)) {
			g_matched[to] = from;
			return true;
		}
	}
	return false;
}

int match(int t) // t 시간 내에 matching 되는 최대 매칭 수 구한다. (최대 매칭을 여러번 부르기 위한 용도)
{
	int answer = 0;
	memset(g_matched, 0, sizeof(g_matched));
	for (int i = 1; i < g_carcnt + 1; i++) {
		memset(g_visited, false, sizeof(g_visited));
		if (dfs_with_p(i, t)) answer++;
	}
	return answer;
}

void t_bfs(int start) // time bfs
{
	queue<loc> myq;
	bool visited[MAXNUM];
	memset(visited, false, sizeof(visited));
	myq.push({ g_car[start].r, g_car[start].c, 0 });
	visited[(g_car[start].r - 1) * g_C + g_car[start].c] = true;

	int dr[4] = { -1, 0, 1, 0 };
	int dc[4] = { 0, -1, 0, 1 };
	while (!myq.empty()) {
		loc cur = myq.front();
		myq.pop();
		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];
			int conv = (nr - 1) * g_C + nc;
			if (nr > 0 && nc > 0 && nr < g_R + 1 && nc < g_C + 1) {
				if (visited[conv] || g_parking[nr][nc] == 'X') continue; // 동서남북 탐색해서 visited 이거나 X이면 skip!
				else {
					visited[conv] = true;
					if (g_parking[nr][nc] == '.' || g_parking[nr][nc] == 'C') { // 빈공간 or car
						myq.push({ nr, nc, cur.t + 1 });
					}
					else { // 주차구역('P')					
						g_time[start][g_park[conv]] = cur.t + 1;
						g_maxtime = max(g_maxtime, cur.t + 1); // 주차할 때까지 가장 긴 시간을 구한다.
						myq.push({ nr, nc, cur.t + 1 });
					}
				}
			}
		}
	}
}

int main()
{
	FAST;
	cin >> g_R >> g_C;
	string ss;
	for (int i = 1; i < g_R + 1; i++) {
		cin >> ss;
		for (int j = 0; j < ss.length(); j++) {
			g_parking[i][j + 1] = ss[j]; // 주차장 데이터 입력
			if (ss[j] == 'C') g_car[++g_carcnt] = { i, j + 1 };
			else if (ss[j] == 'P') g_park[(i - 1) * g_C + j + 1] = ++g_parkcnt;
		}
	}
	if (!g_carcnt) { // 차가 없으면 0을 리턴하고 끝낸다.
		cout << 0 << "\n";
		return 0;
	}
	g_graph.resize(g_carcnt + 1);

	for (int i = 0; i < MAXCAR; i++) // 거리 차, 주차구역 시간 구함
		for (int j = 0; j < MAXPARK; j++)
			g_time[i][j] = MAXNUM + 100; // 초기화
	for (int i = 1; i < g_carcnt + 1; i++) t_bfs(i); // '차id * 주차구역id'의 거리 계산

	for (int i = 1; i < g_carcnt + 1; i++) { // 이분 그래프
		for (int j = 1; j < g_parkcnt + 1; j++)
			if (g_time[i][j] < MAXNUM + 100) g_graph[i].push_back(j);
	}

	int left = 0, right = g_maxtime, mid; // 이분 탐색(lower_bound) & 이분 Matching
	while (left < right) {
		mid = (left + right) / 2;
		if (match(mid) < g_carcnt) left = mid + 1; // 시간 늘림
		else right = mid; // 시간 줄임.
	}
	if (match(left) == g_carcnt) cout << right << "\n";
	else cout << -1 << "\n";
}